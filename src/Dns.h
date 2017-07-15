/**
 * Dns.h
 *
 * Arduino DNS client for WizNet5100-based Ethernet shield
 *
 * Portions (c) Copyright 2017 Gerad Munsch <gmunsch@unforgivendevelopment.com
 * (c) Copyright 2009-2010 MCQN Ltd.
 *
 * Released under Apache License, version 2.0
 *
 */

#ifndef _DNSCLIENT_H__
#define _DNSCLIENT_H__

#include <EthernetUdp.h>


/**
 * \class DNSClient
 * Performs the function of name resolution
 */
class DNSClient {
public:
	/**
	 * Constructor for the DNSClient object
	 *
	 * \param[in]	aDNSServer	The DNS server IP address to use for name resolution
	 */
	void begin(const IPAddress& aDNSServer);

	/**
	* Convert a numeric IP address string into a four-byte IP address.
	 *
	 * \brief Convert IP string into 4-byte IP.
	 *
	 * \param[in]	aIPAddrString	IP address to convert
	 * \param[out]	aResult			IPAddress structure to store the returned IP address
	 *
	 * \return Indicates success of the function call, or else an error code
	 * \retval	1	Indicates aIPAddrString was successfully converted to an IP address
	 */
	int inet_aton(const char *aIPAddrString, IPAddress& aResult);

	/**
	 * Resolve the given hostname to an IP address.
	 *
	 * \brief Perform DNS resolution.
	 *
	 * \param[in]	aHostname	Name to be resolved
	 * \param[out]	aResult		IPAddress structure to store the returned IP address
	 *
	 * \return Indicates success of the function call, or else an error code.
	 * \retval	1	Indicates aIPAddrString was successfully converted to an IP address
	 */
	int getHostByName(const char* aHostname, IPAddress& aResult);

protected:
	uint16_t BuildRequest(const char* aName);
	uint16_t ProcessResponse(uint16_t aTimeout, IPAddress& aAddress);

	IPAddress iDNSServer;
	uint16_t iRequestId;
	EthernetUDP iUdp;
};

#endif  /* _DNSCLIENT_H__ */
