/*
 * src/Ethernet.h
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */

#ifndef _ETHERNET_H__
#define _ETHERNET_H__


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
	/**
	 * An array to hold the state of each socket, across all usage of the EthermetClass members and its children.
	 *
	 * \brief Holds the state of each socket
	 */
	static uint8_t _state[MAX_SOCK_NUM];

	/**
	 * An array to hold the port number which a socket is listening on, if the socket is listening (ie: functioning as a
	 * "server")
	 *
	 * \brief Holds the listening port number for each (listening) socket
	 */
	static uint16_t _server_port[MAX_SOCK_NUM];

	/**
	 * \fn int begin(uint8_t *mac_address, unsigned long timeout = 60000, unsigned long responseTimeout = 4000)
	 * Initialize the Ethernet shield, with the provided MAC address, and attempt to configure the TCP/IP parameters via
	 * DHCP.
	 *
	 * \brief Initialize the Ethernet shield with a specified MAC address, attempting to use DHCP.
	 *
	 * \param[in]	mac_address		An array of 6 bytes (uint8_t, specifically) containing the assigned MAC address.
	 * \param[in]	timeout			An optional parameter, specifying the timeout.
	 * \param[in]	responseTimeout	An optional parameter, specifying the response timeout.
	 *
	 * \return		Indicates whether initialization of the Ethernet controller via DHCP was successful (or not).
	 * \retval	0	DHCP configuration failed.
	 * \retval	1	DHCP configuration was successful.
	 */
	int begin(uint8_t *mac_address, unsigned long timeout = 60000, unsigned long responseTimeout = 4000);

	/**
	 * \overload void begin(uint8_t *mac_address, IPAddress local_ip)
	 * Initialize the Ethernet shield, with the provided MAC address, and the provided static IP address.
	 *
	 * \note	The subnet mask is assumed to be 255.255.255.0; and the gateway and DNS server IP addresses are assumed
	 *			to be the \p local_ip -- with the last octet changed to \b 1
	 *
	 * \brief Initialize the Ethernet shield with a static IP
	 *
	 * \param[in]	mac_address	A pointer to an array which contains the MAC address to be set
	 * \param[in]	local_ip	The IP address to assign to the Ethernet shield
	 */
	void begin(uint8_t *mac_address, IPAddress local_ip);


	/**
	 * \overload void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server)
	 * Initialize the Ethernet shield, with the provided MAC address, the provided static IP address, and the provided
	 * DNS server IP address
	 *
	 * \note	The subnet mask is assumed to be 255.255.255.0; and the gateway is assumed to be the specified static IP
	 *			address with the last octet chabged to \b .1
	 *
	 * \brief Initialize the Ethernet shield with a static IP and DNS server IP
	 *
	 * \param[in]	mac_address	A pointer to an array which contains the MAC address to be set
	 * \param[in]	local_ip	The IP address to assign to the Ethernet shield
	 * \param[in]	dns_server	The IP address to assign as the DNS server used for all name resolution
	 */
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server);

	/**
	 * \overload void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway)
	 * Initialize the Ethernet shield, with the provided MAC address, the provided static IP address, the provided DNS
	 * server IP address, and the provided gateway IP address.
	 *
	 * \note	The subnet mask is assumed to be 255.255.255.0
	 *
	 * \brief Initialize the Ethernet shield with a static IP, DNS server IP, and gateway IP
	 *
	 * \param[in]	mac_address	A pointer to an array which contains the MAC address to be set
	 * \param[in]	local_ip	The IP address to assign to the Ethernet shield
	 * \param[in]	dns_server	The IP address to assign as the DNS server used for all name resolution
	 * \param[in]	gateway		The IP address to assign as the default gateway
	 */
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway);

	/**
	 * \overload void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet)
	 * Initialize the Ethernet shield, with the provided MAC address, the provided static IP address, the provided DNS
	 * server IP address, the provided gateway IP address, and the provided subnet mask.
	 *
	 * \brief Initialize the Ethernet shield with a static IP, DNS server, gateway, and subnet mask
	 *
	 * \param[in]	mac_address	A pointer to an array which contains the MAC address to be set
	 * \param[in]	local_ip	The IP address to assign to the Ethernet shield
	 * \param[in]	dns_server	The IP address to assign as the DNS server used for all name resolution
	 * \param[in]	gateway		The IP address to assign as the default gateway
	 * \param[in]	subnet		The subnet mask to assign to the network interface, for networks that are not of the
	 *							\e common "255.255.255.0" arrangement.
	 */
	void begin(uint8_t *mac_address, IPAddress local_ip, IPAddress dns_server, IPAddress gateway, IPAddress subnet);

	int maintain();

	/**
	 * Reads the current local IP address from the W5100 hardware, and returns it as an  \c IPAddress object.
	 *
	 * \brief Reads the currently set IP address
	 *
	 * \return Returns the current local IP address as an \c IPAddress object
	 */
	IPAddress localIP();

	/**
	 * Reads the current subnet mask from the W5100 hardware, and returns it as an \c IPAddress object.
	 *
	 * \brief Reads the current subnet mask
	 *
	 * \return Returns the current subnet mask as an \c IPAddress object
	 */
	IPAddress subnetMask();
	IPAddress gatewayIP();
	IPAddress dnsServerIP();

	friend class EthernetClient;
	friend class EthernetServer;
};

extern EthernetClass Ethernet;

#endif	/* _ETHERNET_H__ */
