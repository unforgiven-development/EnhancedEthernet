/*
 * \file w5100.h
 *
 * Copyright (c) 2017 Gerad Munsch <gmunsch@unforgivendevelopment.com>
 * Copyright (c) 2010 by Arduino LLC. All rights reserved.
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 */

#ifndef _UTILITY_W5100_H__
#define _UTILITY_W5100_H__


#include <SPI.h>


#define ETHERNET_SHIELD_SPI_CS		10		/*! Defines the default Arduino pin used by the Ethernet shield for !CS */
#define ETHERNET_SHIELD_SPI_IRQ		2		/*! Defines the default Arduino pin used by the Ethernet shield for IRQ */


#if defined(__AVR_ATmega8__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
/* Definitions specific to Arduino Uno and similar devices based on the ATmegaXX8 family */
#define ETHERNET_USE_AVR_INTERRUPT	0		/*! Defines the external interrupt number on the AVR microcontroller */
#elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
/* Definitions specific to Arduino Mega and similar devices based on the ATmega1280/2560 family */
#define ETHERNET_USE_AVR_INTERRUPT	4		/*! Defines the external interrupt number on the AVR microcontroller */
#endif

#define MAX_SOCK_NUM				4		/*! Defines the maximum amount of sockets supported by the W5100 */

/**
 * Defines the type \b SOCKET for use throughout the driver.
 */
typedef uint8_t SOCKET;


#define IDM_OR			0x8000
#define IDM_AR0			0x8001
#define IDM_AR1			0x8002
#define IDM_DR			0x8003


class MR {
public:
	static const uint8_t RST							= 0x80;
	static const uint8_t PB								= 0x10;
	static const uint8_t PPPOE							= 0x08;
	static const uint8_t LB								= 0x04;
	static const uint8_t AI								= 0x02;
	static const uint8_t IND							= 0x01;
};


class IR {
public:
	static const uint8_t CONFLICT						= 0x80;
	static const uint8_t UNREACH						= 0x40;
	static const uint8_t PPPoE							= 0x20;
	static const uint8_t SOCK0							= 0x01;
	static const uint8_t SOCK1							= 0x02;
	static const uint8_t SOCK2							= 0x04;
	static const uint8_t SOCK3							= 0x08;

	static inline uint8_t SOCK(SOCKET ch) {
		return (0x01 << ch);
	};
};


class SnMR {
public:
	static const uint8_t CLOSE							= 0x00;
	static const uint8_t TCP							= 0x01;
	static const uint8_t UDP							= 0x02;
	static const uint8_t IPRAW							= 0x03;
	static const uint8_t MACRAW							= 0x04;
	static const uint8_t PPPOE							= 0x05;
	static const uint8_t ND								= 0x20;
	static const uint8_t MULTI							= 0x80;
};



enum SockCMD {
	Sock_OPEN											= 0x01,
	Sock_LISTEN											= 0x02,
	Sock_CONNECT										= 0x04,
	Sock_DISCON											= 0x08,
	Sock_CLOSE											= 0x10,
	Sock_SEND											= 0x20,
	Sock_SEND_MAC										= 0x21,
	Sock_SEND_KEEP										= 0x22,
	Sock_RECV											= 0x40
};


/*
class SnCmd {
public:
	static const uint8_t OPEN							= 0x01;
	static const uint8_t LISTEN							= 0x02;
	static const uint8_t CONNECT						= 0x04;
	static const uint8_t DISCON							= 0x08;
	static const uint8_t CLOSE							= 0x10;
	static const uint8_t SEND							= 0x20;
	static const uint8_t SEND_MAC						= 0x21;
	static const uint8_t SEND_KEEP						= 0x22;
	static const uint8_t RECV							= 0x40;
};
*/


/**
 * \class SnIR
 *
 *
 * \var SEND_OK	Triggers a hardware interrupt, and sets register value to '1' if send operation is completed.
 * \var TIMEOUT	Triggers a hardware interrupt, and sets register value to '1' if timeout occurs during connection
 *				establishment or termination, or during data transmission.
 * \var RECV	Triggers a hardware interrupt, and sets register value to '1' when W5100 receives data. The same action
 *				occurs if received data remains after executing the CMD_RECV command.
 * \var DISCON	Triggers a hardware interrupt, and sets register value to '1' if connection termination is requested or
 *				finished.
 * \var CON		Triggers a hardware interrupt, and sets register value to '1' if connection is established.
 */
class SnIR {
public:
	static const uint8_t SEND_OK						= 0x10;
	static const uint8_t TIMEOUT						= 0x08;
	static const uint8_t RECV							= 0x04;
	static const uint8_t DISCON							= 0x02;
	static const uint8_t CON							= 0x01;
};


/**
 * \class SnSR
 * This class defines the per-socket status register.
 * \brief Defines the per-socket status register.
 */
class SnSR {
public:
	static const uint8_t CLOSED							= 0x00;
	static const uint8_t INIT							= 0x13;
	static const uint8_t LISTEN							= 0x14;
	static const uint8_t SYNSENT						= 0x15;
	static const uint8_t SYNRECV						= 0x16;
	static const uint8_t ESTABLISHED					= 0x17;
	static const uint8_t FIN_WAIT						= 0x18;
	static const uint8_t CLOSING						= 0x1A;
	static const uint8_t TIME_WAIT						= 0x1B;
	static const uint8_t CLOSE_WAIT						= 0x1C;
	static const uint8_t LAST_ACK						= 0x1D;
	static const uint8_t UDP							= 0x22;
	static const uint8_t IPRAW							= 0x32;
	static const uint8_t MACRAW							= 0x42;
	static const uint8_t PPPOE							= 0x5F;
};


/**
 * \class IPPROTO
 * This class provides definitions of the various IP protocols available for use.
 * \brief Defines IP protocols
 */
class IPPROTO {
public:
	static const uint8_t IP								= 0;
	static const uint8_t ICMP							= 1;
	static const uint8_t IGMP							= 2;
	static const uint8_t GGP							= 3;
	static const uint8_t TCP							= 6;
	static const uint8_t PUP							= 12;
	static const uint8_t UDP							= 17;
	static const uint8_t IDP							= 22;
	static const uint8_t ND								= 77;
	static const uint8_t RAW							= 255;
};


/**
 * \class W5100Class
 * \brief Implements a driver for the W5100 Ethernet controller
 *
 * This class provides the core functionality for the W5100 driver, performing such functions as initializing the device
 * at startup, low-level reading and writing of device registers, etc..
 */
class W5100Class {
public:
	void init();

	/**
	 * \brief This function is being used for copy the data form Receive buffer of the chip to application buffer.
	 *
	 * It calculate the actual physical address where one has to read the data from Receive buffer. Here also take care
	 * of the condition while it exceed the Rx memory uper-bound of socket.
	 */
	void read_data(SOCKET s, volatile uint16_t src, volatile uint8_t *dst, uint16_t len);


	/**
	 * \brief This function is being called by send() and sendto() function also.
	 *
	 * This function read the Tx write pointer register and after copy the data in buffer update the Tx write pointer
	 * register. User should read upper byte first and lower byte later to get proper value.
	 */
	void send_data_processing(SOCKET s, const uint8_t *data, uint16_t len);


	/**
	 * \brief A copy of send_data_processing that uses the provided ptr for the write offset.
	 *
	 * Only needed for the "streaming" UDP API, where a single UDP packet is built up over a number of calls to
	 * send_data_processing_ptr, because TX_WR doesn't seem to get updated correctly in those scenarios.
	 *
	 * \todo fix doc for this function
	 *
	 * \param ptr value to use in place of TX_WR.  If 0, then the value is read in from TX_WR
	 *
	 * \return New value for ptr, to be used in the next call
	 */
	void send_data_processing_offset(SOCKET s, uint16_t data_offset, const uint8_t *data, uint16_t len);


	/**
	 * \brief This function is being called by recv() also.
	 *
	 * This function read the Rx read pointer register and after copy the data from receive buffer update the Rx write
	 * pointer register. User should read upper byte first and lower byte later to get proper value.
	 */
	void recv_data_processing(SOCKET s, uint8_t *data, uint16_t len, uint8_t peek = 0);


	/**
	 * \brief Sets the gateway IP address
	 *
	 * \param[in]	_addr	A pointer to an array containing the gateway IP address
	 */
	inline void setGatewayIp(uint8_t *_addr);

	/**
	 * \brief Retreives the current gateway IP address
	 *
	 * \param[out]	_addr	A pointer to an array to which the gateway IP address will be stored in
	 */
	inline void getGatewayIp(uint8_t *_addr);

	/**
	 * \brief Sets the subnet mask
	 *
	 * \param[in]	_addr	A pointer to an array which contains the subnet mask to be set
	 */
	inline void setSubnetMask(uint8_t *_addr);

	/**
	 * \brief Read the subnet mask from hardware
	 *
	 * \param[out]	_addr	A pointer to an array to which the subnet mask will be stored in
	 */
	inline void getSubnetMask(uint8_t *_addr);

	/**
	 * \brief Set the MAC address for use by the Ethernet interface
	 *
	 * \param[in]	_hwaddr	Pointer to the array which the MAC address is held in
	 */
	inline void setMACAddress(uint8_t *_hwaddr);

	inline void getMACAddress(uint8_t *_hwaddr);

	inline void setIPAddress(uint8_t *_ipaddr);

	/**
	 * Retrieves the current IP address from the hardware registers, and places it into a buffer.
	 *
	 * \brief Read current IP from hardware
	 *
	 * \param[out]	_ipaddr	A pointer to the buffer which the retrieved IP address will be stored within
	 */
	inline void getIPAddress(uint8_t *_ipaddr);

	inline void setRetransmissionTime(uint16_t timeout);
	inline void setRetransmissionCount(uint8_t _retry);

	void execCmdSn(SOCKET s, SockCMD _cmd);

	/**
	 * \brief Retrieves the available TX buffer space for a given socket
	 *
	 * \param[in]	s	The socket for which to retrieve the free TX buffer space
	 *
	 * \return	Returns the amount of bytes available in the TX buffer
	 */
	uint16_t getTXFreeSize(SOCKET s);
	uint16_t getRXReceivedSize(SOCKET s);


	/* -------------------------------------------------------------------------------------------------------------- */
	/* --- W5100: Common Registers (summary located at section 3.1 of datasheet) ------------------------------------ */
	/* -------------------------------------------------------------------------------------------------------------- */
private:
	static uint8_t	write(uint16_t _addr, uint8_t _data);
	static uint16_t	write(uint16_t addr, const uint8_t *buf, uint16_t len);

	static uint8_t	read(uint16_t addr);
	static uint16_t	read(uint16_t addr, uint8_t *buf, uint16_t len);


#define __GP_REGISTER8(name, address)										\
	static inline void write##name(uint8_t _data) {							\
		write(address, _data);												\
	}																		\
	static inline uint8_t read##name() {									\
		return read(address);												\
	}

#define __GP_REGISTER16(name, address)										\
	static void write##name(uint16_t _data) {								\
		write(address,   _data >> 8);										\
		write(address+1, _data & 0xFF);										\
	}																		\
	static uint16_t read##name() {											\
		uint16_t res = read(address);										\
		res = (res << 8) + read(address + 1);								\
		return res;															\
	}

#define __GP_REGISTER_N(name, address, size)								\
	static uint16_t write##name(uint8_t *_buff) {							\
		return write(address, _buff, size);									\
	}																		\
	static uint16_t read##name(uint8_t *_buff) {							\
		return read(address, _buff, size);									\
	}


public:
	__GP_REGISTER8 (MR,		0x0000);				/*!< MR:		Mode */
	__GP_REGISTER_N(GAR,	0x0001, 4);				/*!< GAR:		Gateway IP address */
	__GP_REGISTER_N(SUBR,	0x0005, 4);				/*!< SUBR:		Subnet mask address */
	__GP_REGISTER_N(SHAR,	0x0009, 6);				/*!< SHAR:		Source MAC address */
	__GP_REGISTER_N(SIPR,	0x000F, 4);				/*!< SIPR:		Source IP address */
	__GP_REGISTER8 (IR,		0x0015);				/*!< IR:		Interrupt */
	__GP_REGISTER8 (IMR,	0x0016);				/*!< IMR:		Interrupt Mask */
	__GP_REGISTER16(RTR,	0x0017);				/*!< RTR:		Timeout address */
	__GP_REGISTER8 (RCR,	0x0019);				/*!< RCR:		Retry count */
	__GP_REGISTER8 (RMSR,	0x001A);				/*!< RMSR:		Receive memory size */
	__GP_REGISTER8 (TMSR,	0x001B);				/*!< TMSR:		Transmit memory size */
	__GP_REGISTER8 (PATR,	0x001C);				/*!< PATR:		Authentication type address in PPPoE mode */
	__GP_REGISTER8 (PTIMER,	0x0028);				/*!< PTIMER:	PPP LCP Request Timer */
	__GP_REGISTER8 (PMAGIC,	0x0029);				/*!< PMAGIC:	PPP LCP Magic Number */
	__GP_REGISTER_N(UIPR,	0x002A, 4);				/*!< UIPR:		Unreachable IP address in UDP mode */
	__GP_REGISTER16(UPORT,	0x002E);				/*!< UPORT:		Unreachable Port address in UDP mode */

#undef __GP_REGISTER8
#undef __GP_REGISTER16
#undef __GP_REGISTER_N

	/* -------------------------------------------------------------------------------------------------------------- */
	/* --- W5100: Socket registers (summary located at section 3.2 of datasheet) ------------------------------------ */
	/* -------------------------------------------------------------------------------------------------------------- */
private:
	static inline uint8_t	readSn(SOCKET _s, uint16_t _addr);
	static inline uint8_t	writeSn(SOCKET _s, uint16_t _addr, uint8_t _data);

	static inline uint16_t	readSn(SOCKET _s, uint16_t _addr, uint8_t *_buf, uint16_t len);
	static inline uint16_t	writeSn(SOCKET _s, uint16_t _addr, uint8_t *_buf, uint16_t len);

	static const uint16_t	CH_BASE = 0x0400;
	static const uint16_t	CH_SIZE = 0x0100;


#define __SOCKET_REGISTER8(name, address)									\
	static inline void write##name(SOCKET _s, uint8_t _data) {				\
		writeSn(_s, address, _data);										\
	}																		\
	static inline uint8_t read##name(SOCKET _s) {							\
		return readSn(_s, address);											\
	}

#define __SOCKET_REGISTER16(name, address)									\
	static void write##name(SOCKET _s, uint16_t _data) {					\
		writeSn(_s, address,   _data >> 8);									\
		writeSn(_s, address+1, _data & 0xFF);								\
	}																		\
	static uint16_t read##name(SOCKET _s) {									\
		uint16_t res = readSn(_s, address);									\
		uint16_t res2 = readSn(_s,address + 1);								\
		res = res << 8;														\
		res2 = res2 & 0xFF;													\
		res = res | res2;													\
		return res;															\
	}

#define __SOCKET_REGISTER_N(name, address, size)							\
	static uint16_t write##name(SOCKET _s, uint8_t *_buff) {				\
	`	return writeSn(_s, address, _buff, size);							\
	}																		\
	static uint16_t read##name(SOCKET _s, uint8_t *_buff) {					\
		return readSn(_s, address, _buff, size);							\
	}


public:
	__SOCKET_REGISTER8(SnMR,		0x0000)			/*!< SnMR:		Socket "n" Mode */
	__SOCKET_REGISTER8(SnCR,		0x0001)			/*!< SnCR:		Socket "n" Command */
	__SOCKET_REGISTER8(SnIR,		0x0002)			/*!< SnIR:		Socket "n" Interrupt */
	__SOCKET_REGISTER8(SnSR,		0x0003)			/*!< SnSR:		Socket "n" Status */
	__SOCKET_REGISTER16(SnPORT,		0x0004)			/*!< SnPORT:	Socket "n" Source Port */
	__SOCKET_REGISTER_N(SnDHAR,		0x0006, 6)		/*!< SnDHAR:	Socket "n" Destination Hardware Address */
	__SOCKET_REGISTER_N(SnDIPR,		0x000C, 4)		/*!< SnDIPR:	Socket "n" Destination IP Address */
	__SOCKET_REGISTER16(SnDPORT,	0x0010)			/*!< SnDPORT:	Socket "n" Destination Port */
	__SOCKET_REGISTER16(SnMSSR,		0x0012)			/*!< SnMSSR:	Socket "n" Maximum Segment Size */
	__SOCKET_REGISTER8(SnPROTO,		0x0014)			/*!< SnPROTO:	Socket "n" Protocol in IP Raw Mode */
	__SOCKET_REGISTER8(SnTOS,		0x0015)			/*!< SnTOS:		Socket "n" IP TOS */
	__SOCKET_REGISTER8(SnTTL,		0x0016)			/*!< SnTTL:		Socket "n" IP TTL */
	__SOCKET_REGISTER16(SnTX_FSR,	0x0020)			/*!< SnTX_FSR:	Socket "n" TX Free Size */
	__SOCKET_REGISTER16(SnTX_RD,	0x0022)			/*!< SnTX_RD:	Socket "n" TX Read Pointer */
	__SOCKET_REGISTER16(SnTX_WR,	0x0024)			/*!< SnTX_WR:	Socket "n" TX Write Pointer */
	__SOCKET_REGISTER16(SnRX_RSR,	0x0026)			/*!< SnRX_RSR:	Socket "n" RX Received Size */
	__SOCKET_REGISTER16(SnRX_RD,	0x0028)			/*!< SnRX_RD:	Socket "n" RX Read Pointer */
	__SOCKET_REGISTER16(SnRX_WR,	0x002A)			/*!< SnRX_WR:	(RX Write Pointer?) [DATASHEET: "Reserved"] */

#undef __SOCKET_REGISTER8
#undef __SOCKET_REGISTER16
#undef __SOCKET_REGISTER_N


private:
	static const uint8_t	RST = 7;			/*!< Reset BIT */

	static const int		SOCKETS = 4;		/*!< W5100 supports 4 active sockets */

	static const uint16_t	SMASK = 0x07FF;		/*!< TX buffer MASK */
	static const uint16_t	RMASK = 0x07FF;		/*!< RX buffer MASK */

public:
	static const uint16_t	SSIZE = 2048;		/*!< Maximum TX buffer size */

private:
	static const uint16_t	RSIZE = 2048;		/*!< Maximum RX buffer size */

	uint16_t SBASE[SOCKETS];					/*!< TX buffer base address */
	uint16_t RBASE[SOCKETS];					/*!< RX buffer base address */

private:


/**
 * \def SPI_ETHERNET_SETTINGS
 * Define the SPISettings object for SPI Transaction Mode, with the following settings:
 * \li <B>SPI Clock:</B> 8 MHz
 * \li <B>Data Order:</B> Most-Significant Bit first (MSBFIRST)
 * \li <B>SPI Mode:</B> Mode 0
 */
#define SPI_ETHERNET_SETTINGS SPISettings(8000000, MSBFIRST, SPI_MODE0)


/* SPI SS/CS (slave select/chip select) functions, as well as interrupt-related functions. */

/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * \name SPIFunctions
 * Functions related to the managment of SPI and slave-select.
 */

/**
 * @{
 */

/**
 * \fn inline static void initSS()
 * Initialize the \b SS (slave select) pin, using the "lowest-level" technique available for our hardware platform.
 * \brief Initialize the SS pin
 *
 * \fn inline static void setSS()
 * Set the \b SS (slave select) pin to the \b active (low) state, which selects the Ethernet controller for \b SPI
 * communication, using the "lowest-level" technique available for our hardware platform.
 * \brief Set the SS pin to active (low)
 *
 * \fn inline static void resetSS()
 * Resets the \b SS (slave select) pin to the \b inactive (HIGH) state, which \e deselects the Ethernet controller, and
 * allows the \b SPI bus to be used by other devices.\n
 * This is performed using the "lowest-level" technique available for our hardware platform.
 * \brief Reset the SS pin to inactive (high)
 */

/**
 * @}
 */

/* ------------------------------------------------------------------------------------------------------------------ */

/**
 * \def ETHERNET_USE_INTERRUPTS
 * Enables use of interrupt-based communcation with the W5100 when defined (optionally, with a value of \b 1 -- though
 * just defining it should be adequate).
 *
 * ---------------------------------------------------------------------------------------------------------------------
 * Interrupt-related functions:
 *
 * \fn inline static void atchInt()	Activates the appropriate external interrupt for digital pin 2 on the device.
 * \fn inline static void dtchInt()	Disables activation of the ISR by means of the external interrupt on pin 2.
 */

/* SPI CS pin handling for AVR devices */
#ifdef ARDUINO_ARCH_AVR

/* Arduino Mega and Arduino Mega 2560 */
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
private:
	inline static void initSS()		{ DDRB  |=  _BV(4); };
	inline static void setSS()		{ PORTB &= ~_BV(4); };
	inline static void resetSS()	{ PORTB |=  _BV(4); };
#if (ETHERNET_USE_INTERRUPTS == 1)
	inline static void atchInt()	(EIMSK |=   0x10)
	inline static void dtchInt()	(EIMSK &= ~(0x10))
	inline static void enInts()		{};
	inline static void disInts()	{};
#endif	/* ETHERNET_USE_INTERRUPTS == 1 */

/* Arduino Leonardo; possibly Teensy 2.0 and other ATmega32U4-based boards? */
#elif defined(__AVR_ATmega32U4__)
private:
	inline static void initSS()		{ DDRB  |=  _BV(6); };
	inline static void setSS()		{ PORTB &= ~_BV(6); };
	inline static void resetSS()	{ PORTB |=  _BV(6); };

/* Teensy++ 2.0 ?? */
#elif defined(__AVR_AT90USB1286__) || defined(__AVR_AT90USB646__) || defined(__AVR_AT90USB162__)
private:
	inline static void initSS()		{ DDRB  |=  _BV(0); };
	inline static void setSS()		{ PORTB &= ~_BV(0); };
	inline static void resetSS()	{ PORTB |=  _BV(0); };

/* "Generic" Arduino devices (ie: Arduino Uno (ATmega328P), etc.) */
#elif defined(__AVR_ATmega8__) || defined(__AVR_ATmega88__) || defined(__AVR_ATmega168__) || defined(__AVR_ATmega328__) || defined(__AVR_ATmega328P__)
private:
	inline static void initSS()		{ DDRB  |=  _BV(2); };
	inline static void setSS()		{ PORTB &= ~_BV(2); };
	inline static void resetSS()	{ PORTB |=  _BV(2); };
#if (ETHERNET_USE_INTERRUPTS == 1)
	inline static void atchInt()	(EIMSK |=   0x01)
	inline static void dtchInt()	(EIMSK &= ~(0x01))
	inline static void enInts()		{};
	inline static void disInts()	{};
#endif	/* ETHERNET_USE_INTERRUPTS == 1 */

/* Any other "Generic" Arduino devices */
#else
private:
	inline static void initSS()		{ pinMode(10, OUTPUT);		};
	inline static void setSS()		{ digitalWrite(10, LOW);	};
	inline static void resetSS()	{ digitalWrite(10, HIGH);	};
#endif

/* SPI CS pin handling for ARC devices (Arduino 101) */
#elif defined(__ARDUINO_ARC__)
private:
	inline static void initSS()			{ pinMode(10, OUTPUT);		};
	inline static void setSS()			{ digitalWrite(10, LOW);	};
	inline static void resetSS()		{ digitalWrite(10, HIGH);	};

/* SPI CS pin handing for all other devices */
#else
private:
	inline static void initSS()		{
		*portModeRegister(digitalPinToPort(ETHERNET_SHIELD_SPI_CS))   |=  digitalPinToBitMask(ETHERNET_SHIELD_SPI_CS);
	}
	inline static void setSS()		{
		*portOutputRegister(digitalPinToPort(ETHERNET_SHIELD_SPI_CS)) &= ~digitalPinToBitMask(ETHERNET_SHIELD_SPI_CS);
	}
	inline static void resetSS()	{
		*portOutputRegister(digitalPinToPort(ETHERNET_SHIELD_SPI_CS)) |=  digitalPinToBitMask(ETHERNET_SHIELD_SPI_CS);
	}
#endif

/**
 * Declare "NULL" functions if ETHERNET_USE_INTERRUPTS == 0 or is undefined, as this will limit the need to use lots of
 * #ifdef statements throughout the code of the various functions.
 */
#if (ETHERNET_USE_INTERRUPTS == 0) || !defined(ETHERNET_USE_INTERRUPTS)
	inline static void atchInt()	{};
	inline static void dtchInt()	{};
	inline static void enInts()		{};
	inline static void disInts()	{};
#endif



};


extern W5100Class W5100;



uint8_t W5100Class::readSn(SOCKET _s, uint16_t _addr) {
	return read(CH_BASE + _s * CH_SIZE + _addr);
}


uint8_t W5100Class::writeSn(SOCKET _s, uint16_t _addr, uint8_t _data) {
	return write(CH_BASE + _s * CH_SIZE + _addr, _data);
}


uint16_t W5100Class::readSn(SOCKET _s, uint16_t _addr, uint8_t *_buf, uint16_t _len) {
	return read(CH_BASE + _s * CH_SIZE + _addr, _buf, _len);
}


uint16_t W5100Class::writeSn(SOCKET _s, uint16_t _addr, uint8_t *_buf, uint16_t _len) {
	return write(CH_BASE + _s * CH_SIZE + _addr, _buf, _len);
}


void W5100Class::getGatewayIp(uint8_t *_addr) {
	readGAR(_addr);
}

void W5100Class::setGatewayIp(uint8_t *_addr) {
	writeGAR(_addr);
}

void W5100Class::getSubnetMask(uint8_t *_addr) {
	readSUBR(_addr);
}


void W5100Class::setSubnetMask(uint8_t *_addr) {
	writeSUBR(_addr);
}


void W5100Class::getMACAddress(uint8_t *_hwaddr) {
	readSHAR(_hwaddr);
}


void W5100Class::setMACAddress(uint8_t *_hwaddr) {
	writeSHAR(_hwaddr);
}


void W5100Class::getIPAddress(uint8_t *_ipaddr) {
	readSIPR(_ipaddr);
}


void W5100Class::setIPAddress(uint8_t *_ipaddr) {
	writeSIPR(_ipaddr);
}


void W5100Class::setRetransmissionTime(uint16_t _timeout) {
	writeRTR(_timeout);
}


void W5100Class::setRetransmissionCount(uint8_t _retry) {
	writeRCR(_retry);
}

#endif	/* _UTILITY_W5100_H__ */
