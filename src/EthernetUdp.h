/*
 * src/EthernetUdp.h
 * -- COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 *
 *  Udp.cpp: Library to send/receive UDP packets with the Arduino ethernet shield.
 *  This version only offers minimal wrapping of socket.c/socket.h
 *  Drop Udp.h/.cpp into the Ethernet library directory at hardware/libraries/Ethernet/
 *
 * NOTE: UDP is fast, but has some important limitations (thanks to Warren Gray for mentioning these)
 * 1) UDP does not guarantee the order in which assembled UDP packets are received. This
 * might not happen often in practice, but in larger network topologies, a UDP
 * packet can be received out of sequence.
 * 2) UDP does not guard against lost packets - so packets *can* disappear without the sender being
 * aware of it. Again, this may not be a concern in practice on small local networks.
 * For more information, see http://www.cafeaulait.org/course/week12/35.html
 *
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * bjoern@cs.stanford.edu 12/30/2008
 */


#ifndef _ETHERNETUDP_H__
#define _ETHERNETUDP_H__

/* -----[ INCLUDES ]----- */
#include <Udp.h>


/**
 * \def UDP_TX_PACKET_MAX_SIZE
 * Defines the maximum size of a UDP packet to be transmitted.
 */
#define UDP_TX_PACKET_MAX_SIZE 24


class EthernetUDP : public UDP {
private:
	uint16_t  _port;			/*! local port to listen on */
	IPAddress _remoteIP;		/*! remote IP address for the incoming packet whilst it's being processed */
	uint16_t  _remotePort;		/*! remote port for the incoming packet whilst it's being processed */
	uint16_t  _offset;			/*! offset into the packet being sent */

protected:
	uint8_t  _sock;				/*! socket ID for W5100 */
	uint16_t _remaining;		/*! remaining bytes of incoming packet yet to be processed */

public:
	/**
	 * EthernetUDP object constructor
	 *
	 * \brief Instantiates a new EthernetUDP object
	 */
	EthernetUDP();

	/**
	 * Start a UDP listening socket on the specified UDP port.
	 *
	 * \brief Start listening on UDP port
	 *
	 * \param[in]	port	The UDP port number to open the listening socket on
	 *
	 * \return Indicates whether the operation was successful or not.
	 * \retval	1	Success
	 * \retval	0	No sockets are available to use on the W5100 device
	 */
	virtual uint8_t begin(uint16_t);

	/**
	 * Start multicast listener on specified multicast address and port.
	 *
	 * \brief Start multicast listener on UDP port.
	 *
	 * \param[in]	ip		The multicast IP address to open the listening socket on
	 * \param[in]	port	The UDP port number to open the multicast listening socket on
	 *
	 * \return Indicates whether the operation was successful or not.
	 * \retval	1	Success
	 * \retval	0	No sockets are available to use on the W5100 device
	 */
	virtual uint8_t beginMulticast(IPAddress, uint16_t);

	/**
	 * Finish with the UDP socket, releasing any resources being used by this EthernetUDP instance.
	 *
	 * \brief Close the UDP socket.
	 */
	virtual void stop();


	/* --- Sending UDP packets --- */

	/**
	 * \fn virtual int beginPacket(IPAddress ip, uint16_t port)
	 * Start building a packet to send to the remote host, specified by the given IP address and port.
	 *
	 * \brief Start building a UDP packet, with the destination specified by IP address.
	 *
	 * \param[in]	ip		IP address of host to send packet to
	 * \param[in]	port	UDP port number to send packet to
	 *
	 * \return Indicates whether the start of building the new packet was successful or not.
	 * \retval	1	Success
	 * \retval	0	There was an error with the supplied IP address and/or port
	 */
	virtual int beginPacket(IPAddress ip, uint16_t port);

	/**
	 * \overload virtual int beginPacket(const char *host, uint16_t port)
	 * Start building a packet to send to the remote host, specified by the given hostname and port. A DNS query will be
	 * be executed, attempting to resolve the hostname to an IP address.
	 *
	 * \brief Start building a UDP packet, with the destination specified by hostname.
	 *
	 * \param[in]	host	The hostname to send the packet to
	 * \param[in]	port	The UDP port number to send the packet to
	 *
	 * \return Indicates whether the start of building the new packet was successful or not.
	 * \retval	1	Success
	 * \retval	0	Error with DNS resolution
	 */
	virtual int beginPacket(const char *host, uint16_t port);


	/**
	 * Finish building the packet, and send it.
	 *
	 * \brief Finish building the UDP packet, and send it.
	 *
	 * \return Indicates whether the packet was successfully sent or not.
	 * \retval	1	Success
	 * \retval	0	An error occurred while sending the packet
	 */
	virtual int endPacket();


	/**
	 * \fn virtual size_t write(uint8_t byte)
	 * Write a single byte into the packet that is currently "under construction".
	 *
	 * \brief Write a single byte into the packet.
	 *
	 * \param[in] byte The single byte to write into the packet.
	 */
	virtual size_t write(uint8_t byte);

	/**
	 * \overload virtual size_t write(const uint8_t *buffer, size_t size)
	 * Write a specified amount of bytes from a buffer into the packet that is currently "under construction".
	 *
	 * \brief Write multiple bytes into the packet.
	 *
	 * \param[in] buffer The buffer containing the data bytes to be written into the packet.
	 * \param[in] size The size of the data to be written into the packet.
	 */
	virtual size_t write(const uint8_t *buffer, size_t size);


	using Print::write;


	/**
	 * Start processing the next available incoming packet.
	 *
	 * \brief Start processing the next incoming packet.
	 *
	 * \return Returns the size of the packet in bytes, or 0 if no (new) incoming packets are available.
	 * \retval 0 No (new) incoming packets are available
	 */
	virtual int parsePacket();

	/**
	 * Provides the number of bytes remaining in the current packet (that is being parsed via 'parsePacket()').
	 *
	 * \brief Provides the number of bytes remaining in the current packet.
	 *
	 * \return The number of bytes remaining in the packet that is currently being parsed.
	 */
	virtual int available();

	/**
	 * \fn virtual int read()
	 * \brief Read a single byte from the current packet
	 *
	 * \return	Returns the single byte that was read from the current packet
	 */
	virtual int read();

	// Read up to len bytes from the current packet and place them into buffer
	// Returns the number of bytes read, or 0 if none are available
	virtual int read(unsigned char* buffer, size_t len);

	// Read up to len characters from the current packet and place them into buffer
	// Returns the number of characters read, or 0 if none are available
	virtual int read(char* buffer, size_t len) { return read((unsigned char*)buffer, len); };

	// Return the next byte from the current packet without moving on to the next byte
	virtual int peek();

	virtual void flush();	// Finish reading the current packet

	// Return the IP address of the host who sent the current incoming packet
	virtual IPAddress remoteIP() {
		return _remoteIP;
	};

	// Return the port of the host who sent the current incoming packet
	virtual uint16_t remotePort() {
		return _remotePort;
	};
};

#endif	/* __ETHERNETUDP_H__ */
