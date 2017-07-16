/**
 * \file w5100.cpp
 * Contains the core functionality for communication with the W5100 Ethernet controller.
 *
 * \author		Gerad Munsch <gmunsch@unforgivendevelopment.com>
 * \author		Arduino LLC.
 * \date		2010-2017
 *
 * \copyright	This file is free software; you can redistribute it and/or modify
 *				it under the terms of either the GNU General Public License version 2
 *				or the GNU Lesser General Public License version 2.1, both as
 *				published by the Free Software Foundation.
 *
 * \todo Implement PPPoE functionality
 */

/* ------------------------------------------------------------------------------------------------------------------ */

#include <stdio.h>
#include <string.h>

#include "w5100.h"


/* ------------------------------------------------------------------------------------------------------------------ */


/* W5100 controller instance */
W5100Class W5100;


/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * \def TX_RX_MAX_BUF_SIZE
 * Defines the maximum size of the TX and RX buffers, combined, in bytes.
 *
 * \def TX_BUF
 * Defines the size of the TX buffer in bytes.
 *
 * \def RX_BUF
 * Defines the size of the RX buffer in bytes; determined by the difference of the maximum size of the TX and RX buffers
 * (combined), minus the defined size of the TX buffer.
 *
 * \def TXBUF_BASE
 * Defines the base address of the W5100's internal transmit buffers.
 *
 * \def RXBUF_BASE
 * Defines the base address of the W5100's internal receive buffers.
 */
#define TX_RX_MAX_BUF_SIZE	2048
#define TX_BUF				0x1100
#define RX_BUF				(TX_BUF + TX_RX_MAX_BUF_SIZE)
#define TXBUF_BASE			0x4000
#define RXBUF_BASE			0x6000


/* ------------------------------------------------------------------------------------------------------------------ */


void W5100Class::init(void) {
	delay(500);

	SPI.begin();
	initSS();
	SPI.beginTransaction(SPI_ETHERNET_SETTINGS);

	writeMR(1 << RST);
	writeTMSR(0x55);
	writeRMSR(0x55);

	SPI.endTransaction();

	for (int i = 0; i < MAX_SOCK_NUM; i++) {
		SBASE[i] = TXBUF_BASE + SSIZE * i;
		RBASE[i] = RXBUF_BASE + RSIZE * i;

#if (ETHERNET_USE_INTERRUPTS == 1) || defined(ETHERNET_USE_INTERRUPTS)
		_v_sock_int_status[i] = 0x00;
#endif

	}
}


uint16_t W5100Class::getTXFreeSize(SOCKET s) {
	uint16_t val = 0;
	uint16_t val1 = 0;

	do {
		val1 = readSnTX_FSR(s);
		if (val1 != 0) {
			val = readSnTX_FSR(s);
		}
	} while (val != val1);

	return val;
}


uint16_t W5100Class::getRXReceivedSize(SOCKET s) {
	uint16_t val = 0;
	uint16_t val1 = 0;

	do {
		val1 = readSnRX_RSR(s);
		if (val1 != 0) {
			val = readSnRX_RSR(s);
		}
	} while (val != val1);

	return val;
}


void W5100Class::send_data_processing(SOCKET s, const uint8_t *data, uint16_t len) {
	/* This is same as having no offset in a call to send_data_processing_offset */
	send_data_processing_offset(s, 0, data, len);
}


void W5100Class::send_data_processing_offset(SOCKET s, uint16_t data_offset, const uint8_t *data, uint16_t len) {
	uint16_t ptr = readSnTX_WR(s);
	ptr += data_offset;
	uint16_t offset = ptr & SMASK;
	uint16_t dstAddr = offset + SBASE[s];

	if (offset + len > SSIZE) {
		/* Wrap around circular buffer */
		uint16_t size = SSIZE - offset;
		write(dstAddr, data, size);
		write(SBASE[s], data + size, len - size);
	} else {
		write(dstAddr, data, len);
	}

	ptr += len;
	writeSnTX_WR(s, ptr);
}


void W5100Class::recv_data_processing(SOCKET s, uint8_t *data, uint16_t len, uint8_t peek) {
	uint16_t ptr;

	ptr = readSnRX_RD(s);
	read_data(s, ptr, data, len);
	if (!peek) {
		ptr += len;
		writeSnRX_RD(s, ptr);
	}
}


void W5100Class::read_data(SOCKET s, volatile uint16_t src, volatile uint8_t *dst, uint16_t len) {
	uint16_t size;
	uint16_t src_mask;
	uint16_t src_ptr;

	src_mask = src & RMASK;
	src_ptr = RBASE[s] + src_mask;

	if ((src_mask + len) > RSIZE) {
		size = RSIZE - src_mask;
		read(src_ptr, (uint8_t *)dst, size);
		dst += size;
		read(RBASE[s], (uint8_t *)dst, len - size);
	} else {
		read(src_ptr, (uint8_t *)dst, len);
	}
}


uint8_t W5100Class::write(uint16_t _addr, uint8_t _data) {

	/*
	 * Seems to match function [uint16 wiz_write_buf(uint16 addr, uint8 *buf, uint16 len)] from WIZnet driver,
	 * but without a buffer/length (ie: a single byte)
	 */

	/* ---(DISABLE_ISR)--- */

	setSS();
	SPI.transfer(0xF0);
	SPI.transfer(_addr >> 8);
	SPI.transfer(_addr & 0xFF);
	SPI.transfer(_data);
	resetSS();

	/* ---(ENABLE_ISR)--- */

	return 1;
}


uint16_t W5100Class::write(uint16_t _addr, const uint8_t *_buf, uint16_t _len) {

	/*
	 * Seems to match function [uint16 wiz_write_buf(uint16 addr, uint8 *buf, uint16 len)] from WIZnet driver
	 */

	/* ---(DISABLE_ISR)--- */

	for (uint16_t i = 0; i < _len; i++) {
		setSS();

		SPI.transfer(0xF0);
		SPI.transfer(_addr >> 8);
		SPI.transfer(_addr & 0xFF);
		_addr++;
		SPI.transfer(_buf[i]);

		resetSS();
	}

	/* ---(ENABLE_ISR)--- */

	return _len;
}


uint8_t W5100Class::read(uint16_t _addr) {

	/*
	 * Seems to match function [uint16 wiz_read_buf(uint16 addr, uint8* buf,uint16 len)] from WIZnet driver,
	 * but without a buffer/length (ie: a single byte)
	 */

	/* ---(DISABLE_ISR)--- */

	setSS();

	SPI.transfer(0x0F);
	SPI.transfer(_addr >> 8);
	SPI.transfer(_addr & 0xFF);
	uint8_t _data = SPI.transfer(0);

	resetSS();

	/* ---(ENABLE_ISR)--- */

	return _data;
}


uint16_t W5100Class::read(uint16_t _addr, uint8_t *_buf, uint16_t _len) {

	/*
	 * Seems to match function [uint16 wiz_read_buf(uint16 addr, uint8* buf,uint16 len)] from WIZnet driver
	 */

	/* ---(DISABLE_ISR)--- */

	for (uint16_t i = 0; i < _len; i++) {
		setSS();

		SPI.transfer(0x0F);
		SPI.transfer(_addr >> 8);
		SPI.transfer(_addr & 0xFF);
		_addr++;
		_buf[i] = SPI.transfer(0);

		resetSS();
	}

	/* ---(ENABLE_ISR)--- */

	return _len;
}


void W5100Class::execCmdSn(SOCKET s, SockCMD _cmd) {
	/* Send command to socket */
	writeSnCR(s, _cmd);

	/* Wait for command to complete */
	while (readSnCR(s)) {
		/* (wait loop...) */
	}
}


/* --------------------------------------------------------------------------------------------------------------- *//**
 * \fn void W5100Class::interruptHandler()
 * \note	The following function is the interrupt handler for hardware interrupts triggered by the W5100 hardware via
 *			a falling edge on the Arduino's digital pin \b 2. On a "typical" Arduino (ie: Arduino Uno), digital pin \b 2
 *			is the AVR's external interrupt \b 0.\n
 *			In the case of the Arduino Mega, while still being physically located on the Arduino's digital pin \b 2, the
 *			implementation of the Arduino Mega assigns the AVR ATmega2560's interrupts to different pins; as such,
 *			digital pin \b 2 ends up being the AVR's external interrupt \b 4.\n\n
 *			And then, just to make things that much more complicated, is the Arduino Leonardo (which utilizes an AVR
 *			ATmega32U4 -- which also happens to be used in quite a few other designs, including boards with other form
 *			factors, such as the Teensy 2.0).\n
 *			On the Leonardo, digital pin \b 2 is connected to the AVR's external interrupt \b 1. Not a big deal, until
 *			you consider that digital pins \b 2 and \b 3 are \b I²C pins \b SDA and \b SCL, respectively. As an added
 *			bonus, the pins are swapped in respect to the Uno; digital pin \b 2 is external interrupt \b 1, and digital
 *			pin \b 3 is external interrupt \b 0. Fortunately, the Leonardo has more external interrupts than many
 *			similarly-spec'ed AVRs, but again, not without some caveats.\n
 *			External interrupts \b 2 and \b 3 are on digital pins \b 0 and \b 1 -- the same pins that provide \b UART
 *			functionality. This \e might be OK, as the ATmega32U4 is a native \b USB device, and as such, a "virtual"
 *			\b UART is provided by the USB hardware, so the \b UART on pins \b 0 & \b 1 is considered to be \b UART1
 *			(an "extra" \b UART -- which can be used to interface with other serial devices, and is \b NOT used for the
 *			programming of the device). If this \b UART is not required in the design, the solder jumper on the bottom
 *			of the Ethernet shield (which is ordinarily just used to "bridge" the connection to digital pin \b 2 on the
 *			"pin" side) could be connected to one of the other pins with an available external interrupt with a short
 *			wire. However, additional logic will need to be implemented in this library to allow that functionality.\n
 *			Interestingly, the ATmega32U4 also provides an external interrupt \b 6 (but doesn't provide either external
 *			interrupt \b 4 or \b 5 -- an interesting situation). External interrupt \b 6 is located on digital pin \b 7
 *			and does not interfere with any "important" functionality. However, if using low-power modes on the Arduino,
 *			external interrupt \b 6 is \b NOT able to wake the device from the deeper sleep modes via a rising edge, a
 *			falling edge, or a change in level -- only a sustained period of the pin being pulled low. This is due to
 *			the fact that external interrupt \b 6 relies on the \b IO clock being active, which it is not in any of the
 *			low-power modes other than "IDLE".\n
 *			The Leonardo will not have selectable external interrupts in its initial implementation, and will use the
 *			interrupt which is associated with digital pin \b 2 -- as all of the other boards do. However, this function
 *			will likely be added at some point. Please provide feedback if there is any interest here.
 *			Interrupt logic on other boards, particularly non-AVR boards, is still TBD.
 * \warning The interrupt code is still a \b WIP and is \b NOT likely to work at this point.
 *//* --------------------------------------------------------------------------------------------------------------- */

void W5100Class::interruptHandler() {
	uint8_t int_val;

	/* ---(XXX: Disable ISR? Or disable global interrupts?)--- */

	int_val = readIR();

	do {
		if (int_val & IR::CONFLICT) {
			_v_ipconflict = true;
		}

		if (int_val & IR::UNREACH) {
			_v_ip_port_unreachable = true;
		}

		/* ---( Clear non-socket interrupts )--- */
		writeIR(0xF0);

		/* ---( Check socket interrupt flags, and if set, store them for later. )--- */

		/* SOCKET 0 */
		if (int_val & IR::SOCK0) {
			_v_sock_int_status[0] |= readSnIR(0);
			writeSnIR(0, _v_sock_int_status[0]);
		}

		/* SOCKET 1 */
		if (int_val & IR::SOCK1) {
			_v_sock_int_status[1] |= readSnIR(1);
			writeSnIR(1, _v_sock_int_status[1]);
		}

		/* SOCKET 2 */
		if (int_val & IR::SOCK2) {
			_v_sock_int_status[2] |= readSnIR(2);
			writeSnIR(2, _v_sock_int_status[2]);
		}

		/* SOCKET 3 */
		if (int_val & IR::SOCK3) {
			_v_sock_int_status[3] |= readSnIR(3);
			writeSnIR(3, _v_sock_int_status[3]);
		}

	} while (int_val != 0x00);

	/* ---(XXX: Re-enable ISR? Or re-enable global interrupts?)--- */
}
