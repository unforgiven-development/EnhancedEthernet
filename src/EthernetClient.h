/*
 * src/EthernetClient.h
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
	EthernetClient();
	EthernetClient(uint8_t sock);

	uint8_t status();

	/**
	 * \fn connect	Connect, as a client, to a server specified by IP address.
	 *				Attempts to connect to a remote server by specification of the server's IP address and port number.
	 *
	 * \param [in] ip	The IP address of the remote server.
	 * \param [in] port	The port number of the remote server to connect to.
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
	 * \fn connect	Connect, as a client, to a server specified by hostname.
	 *				Attempts to connect to a remote server by specification of the server's hostname and port number.
	 *				If the hostname is resolved, attempt connection with connect(IPAddress ip, uuint16_t port);
	 *
	 * \param [in] host	The DNS hostname of the remote server.
	 * \param [in] port	The port number of the remote server to connect to.
	 *
	 * \return	Indicates whether the DNS resolution was successful (or not).
	 * \retval 0	Indicates that there was an issue resolving the hostname.
	 * \retval 1	Indicates that the hostname resolution occurred without issue.
	 */
	virtual int connect(const char *host, uint16_t port);
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buf, size_t size);
	virtual int available();
	virtual int read();
	virtual int read(uint8_t *buf, size_t size);
	virtual int peek();
	virtual void flush();
	virtual void stop();
	virtual uint8_t connected();
	virtual operator bool();
	virtual bool operator==(const bool value) { return bool() == value; }
	virtual bool operator!=(const bool value) { return bool() != value; }
	virtual bool operator==(const EthernetClient&);
	virtual bool operator!=(const EthernetClient& rhs) { return !this->operator==(rhs); };
	uint8_t getSocketNumber();

	friend class EthernetServer;

	using Print::write;

private:
	static uint16_t _srcport;
	uint8_t _sock;
};

#endif	/* __ETHERNETCLIENT_H__ */
