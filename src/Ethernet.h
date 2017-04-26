/*
 * src/Ethernet.h
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */

#ifndef __ETHERNET_H__
#define __ETHERNET_H__


#include <inttypes.h>
//#include "w5100.h"
#include "IPAddress.h"
#include "EthernetClient.h"
#include "EthernetServer.h"
#include "Dhcp.h"

#define MAX_SOCK_NUM 4

class EthernetClass {
private:
	IPAddress _dnsServerAddress;
	DhcpClass* _dhcp;

public:
	static uint8_t _state[MAX_SOCK_NUM];
	static uint16_t _server_port[MAX_SOCK_NUM];

	/**
	 * Initialize the Ethernet shield, with the provided MAC address, and attempt to configure the TCP/IP parameters via
	 * DHCP discovery.
	 *
	 * @brief Initialize the Ethernet shield with a specified MAC address, attempt to use DHCP
	 *
	 * @return Indicates whether DHCP configuration was successful, or not.
	 * @retval 0 DHCP configuration failed.
	 * @retval 1 DHCP configuration was successful.
	 *
	 */
	int begin(uint8_t *mac_address, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);

	void begin(uint8_t *mac_address, IPAddress local_ip);
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);

	int maintain();

	IPAddress localIP();
	IPAddress subnetMask();
	IPAddress gatewayIP();
	IPAddress dnsServerIP();

	friend class EthernetClient;
	friend class EthernetServer;
};

extern EthernetClass Ethernet;

#endif	/* __ETHERNET_H__ */
