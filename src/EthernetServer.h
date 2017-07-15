/**
 * \file EthernetServer.h
 * Defines the required class and functions to implement a "server"-type object on the Arduino, to be served by the
 * attached Ethernet shield.
 *
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 * \author		Gerad Munsch <gmunsch@unforgivendevelopment.com>
 * \author		The Arduino project
 * \date		?-2017
 *
 */

#ifndef _ETHERNETSERVER_H__
#define _ETHERNETSERVER_H__


#include "Server.h"


class EthernetClient;


/**
 * \class EthernetServer
 * \brief Implements server functionality via the Arduino Ethernet shield
 */
class EthernetServer : public Server {
private:
	/**
	 * A 16-bit unsigned integer value, in which we will store the local port that the \p Server object is listening on.
	 */
	uint16_t _port;

	void accept();

public:
	/**
	 * The constructor for the EthernetServer class. This creates a new instance of a "server" on the Ethernet hardware,
	 * listening for incoming connections from clients.
	 *
	 * \brief Constructor -- creates a new instance of a "server"
	 *
	 * \param[in]	port	The port on which to listen for incoming connections.
	 */
	EthernetServer(uint16_t port);

	/**
	 *
	 * \return
	 */
	EthernetClient available();

	/**
	 *
	 */
	virtual void begin();

	/**
	 *
	 * \return
	 */
	virtual size_t write(uint8_t);

	/**
	 *
	 * \param buf
	 * \param size
	 * \return
	 */
	virtual size_t write(const uint8_t *buf, size_t size);

	using Print::write;

};

#endif	/* _ETHERNETSERVER_H__ */
