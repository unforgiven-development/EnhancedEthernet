/**
 * \file EthernetClient.h
 *
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */


#ifndef __ETHERNETCLIENT_H__
#define __ETHERNETCLIENT_H__


#include "Arduino.h"
#include "Print.h"
#include "Client.h"
#include "IPAddress.h"



class EthernetClient : public Client {

public:
	/**
	 * \fn EthernetClient()
	 * The default (no-arg) constructor for EthernetClient. This constructor instantiates a new instance of a Client
	 * object (specifically a Client object which uses Ethernet as the physical layer), and it will (attempt to) use the
	 * first socket which is available for use on the W5100 hardware.
	 *
	 * \brief Constructor -- creates a new EthernetClient object
	 */
	EthernetClient();

	/**
	 * \overload EthernetClient(uint8_t sock)
	 * An alternative constructor for the EthernetClient class. This constructor attempts to instantiate the Client
	 * object (specifically, EthernetClient object) using the hardware socket number that is passed to it during the
	 * instantiation of the object.
	 *
	 * \note If the socket specified is in use, this is likely to fail.
	 *
	 * \brief Constructor -- creates a new EthernetClient object, having specified the desired socket
	 *
	 * \param[in]	sock	Specifies the hardware socket to use
	 */
	EthernetClient(uint8_t sock);

	uint8_t status();

	/**
	 * \fn virtual int connect(IPAddress ip, uint16_t port)
	 * Connect, as a client, to a server specified by IP address. Attempts to connect to a remote server by
	 * specification of the server's IP address and port number.
	 *
	 * \param[in]	ip		The IP address of the remote server.
	 * \param[in]	port	The port number of the remote server to connect to.
	 *
	 * \return	Indicates whether the connection was successfully established (or not).
	 * \retval 0	Indicates that there was an issue establishing the connection, for one of the following reasons:
	 *				- No sockets available on the W5100 hardware.
	 *				- The connection attempt timed out.
	 *				- The connection was (prematurely) closed.
	 * \retval 1	Indicates that the connection was successfully established.
	 */
	virtual int connect(IPAddress ip, uint16_t port);

	/**
	 * \overload virtual int connect(const char *host, uint16_t port)
	 * Connect, as a client, to a server specified by hostname. Attempts to connect to a remote server by specification
	 * of the server's hostname and port number. If the hostname is resolved, attempt connection with
	 * \c connect(IPAddressip, uuint16_t port);
	 *
	 * \param[in]	host	The DNS hostname of the remote server.
	 * \param[in]	port	The port number of the remote server to connect to.
	 *
	 * \return		Indicates whether the DNS resolution was successful (or not).
	 * \retval	0	Indicates that there was an issue resolving the hostname.
	 * \retval	1	Indicates that the hostname resolution occurred without issue.
	 */
	virtual int connect(const char *host, uint16_t port);


	/**
	 * \name Client Write Functions
	 * Functions that provide the ability to write data to an active connection.
	 */

	/**
	 * @{
	 */

	virtual size_t write(uint8_t);

	virtual size_t write(const uint8_t *buf, size_t size);

	/**
	 * @}
	 */


	virtual int available();


	virtual int read();

	virtual int read(uint8_t *buf, size_t size);


	virtual int peek();


	virtual void flush();


	virtual void stop();


	virtual uint8_t connected();


	virtual operator bool();


	virtual bool operator==(const bool value) {
		return bool() == value;
	}


	virtual bool operator!=(const bool value) {
		return bool() != value;
	}


	virtual bool operator==(const EthernetClient&);


	virtual bool operator!=(const EthernetClient& rhs) {
		return !this->operator == (rhs);
	};


	/**
	 * This function is solely to report which hardware socket is in use by this particular EthernetClient instance.
	 *
	 * \brief Reports which hardware socket is in use by this this client object
	 *
	 * \return Returns the socket number which is in use by this EthernetClient object
	 */
	uint8_t getSocketNumber();


	friend class EthernetServer;


	using Print::write;

private:
	static uint16_t _srcport;
	uint8_t _sock;
};


#endif	/* __ETHERNETCLIENT_H__ */
