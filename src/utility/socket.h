/*
 * src/utility/socket.h
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */

#ifndef	_UTILITY_SOCKET_H__
#define	_UTILITY_SOCKET_H__


#include "utility/w5100.h"


/* Open a socket (in TCP, UDP or IP_RAW mode) */
extern uint8_t	socket(SOCKET s, uint8_t protocol, uint16_t port, uint8_t flag);

/* Retrieves the status of an open socket */
extern uint8_t	socketStatus(SOCKET s);

/* Close an open socket */
extern void		close(SOCKET s);

/* Establish a TCP connection (client mode) */
extern uint8_t	connect(SOCKET s, uint8_t * addr, uint16_t port);

/* Disconnect an open connection */
extern void		disconnect(SOCKET s);

/* Listen on a TCP socket (server mode) */
extern uint8_t	listen(SOCKET s);

/* Send TCP data */
extern uint16_t	send(SOCKET s, const uint8_t * buf, uint16_t len);

/* Receive TCP data */
extern int16_t	recv(SOCKET s, uint8_t * buf, int16_t len);

/* Wait for transmission to complete */
extern void		flush(SOCKET s);

/* Check if data is available on a socket */
extern int16_t	recvAvailable(SOCKET s);

/* "Peek" into a socket's buffer */
extern uint16_t	peek(SOCKET s, uint8_t *buf);

/* Send an IGMP message */
extern uint16_t igmpsend(SOCKET s, const uint8_t * buf, uint16_t len);

/* Send data (UDP/IP RAW) */
extern uint16_t	sendto(SOCKET s, const uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t port);

/* Receive data (UDP/IP RAW) */
extern uint16_t	recvfrom(SOCKET s, uint8_t * buf, uint16_t len, uint8_t * addr, uint16_t *port);


/**
 * Functions to allow buffered UDP send
 * (ie: where the UDP datagram is built up over a number of calls before being sent)
 */

/**
 * @brief This function sets up a UDP datagram, the data for which will be provided by one
 * or more calls to bufferData and then finally sent with sendUDP.
 *
 * @return 1 if the datagram was successfully set up, or 0 if there was an error
 */
extern int startUDP(SOCKET s, uint8_t* addr, uint16_t port);


/**
 * \fn bufferData	This function copies up to len bytes of data from buf into a UDP datagram to be sent later by
 *					sendUDP.  Allows datagrams to be built up from a series of bufferData calls.
 *
 * \brief Copies data from a buffer into an ("under construction") UDP datagram, to be sent later.
 *
 * \return	Number of bytes successfully added to the UDP datagram buffer.
 */
uint16_t bufferData(SOCKET s, uint16_t offset, const uint8_t* buf, uint16_t len);


/**
 * \fn sendUDP	Send a UDP datagram, which was built up from a sequence of startUDP, followed by one-or-more calls to
 *				bufferData (this sequence "builds" a UDP packet suitable for transmission).
 *
 * \brief Send a "pre-built" UDP datagram.
 *
 * \return	Provides indication as to whether the UDP datagram was successfully transmitted.
 * \retval	1	The UDP datagram was successfully transmitted.
 * \retval	0	Transmission failed due to an error.
 */
int sendUDP(SOCKET s);


#endif	/* _UTILITY_SOCKET_H__ */
