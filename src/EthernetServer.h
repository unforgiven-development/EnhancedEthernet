/**
 * \file EthernetServer.h
 *
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */

#ifndef _ETHERNETSERVER_H__
#define _ETHERNETSERVER_H__

#include "Server.h"

class EthernetClient;

class EthernetServer : public Server {
private:
	uint16_t _port;
	void accept();

public:
	EthernetServer(uint16_t);
	EthernetClient available();

	virtual void begin();
	virtual size_t write(uint8_t);
	virtual size_t write(const uint8_t *buf, size_t size);
	using Print::write;

};

#endif	/* _ETHERNETSERVER_H__ */
