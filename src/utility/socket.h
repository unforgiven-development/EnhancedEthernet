/*
 * src/utility/socket.h
 * COMPONENT OF: Arduino Library "EnhancedEthernet"
 *
 */

#ifndef _UTILITY_SOCKET_H__
#define _UTILITY_SOCKET_H__


#include "utility/w5100.h"


/**
 * \name Socket operations
 * Operations which interact directly with the hardware sockets, at a low level. These operations are \e generally not
 * used directly by an end-user, but are used to implement EthernetClass and its various child classes.
 */

/**
 * @{
 */

/**
 * \brief Open a socket (in TCP, UDP or IP_RAW mode)
 *
 * \param s
 * \param protocol
 * \param port
 * \param flag
 * \return
 */
extern uint8_t socket(SOCKET s, uint8_t protocol, uint16_t port, uint8_t flag);

/* Retrieves the status of an open socket */
extern uint8_t socketStatus(SOCKET s);

/**
 * \brief Close an open socket
 *
 * \param[in]	s	The socket to close
 */
extern void close(SOCKET s);

/* Establish a TCP connection (client mode) */
extern uint8_t connect(SOCKET s, uint8_t *addr, uint16_t port);

/**
 * \brief Disconnect an open connection
 *
 * \param[in]	s	The socket on which the connection to be closed is located
 */
extern void disconnect(SOCKET s);

/* Listen on a TCP socket (server mode) */
extern uint8_t listen(SOCKET s);

/* Send TCP data */
extern uint16_t send(SOCKET s, const uint8_t *buf, uint16_t len);

/* Receive TCP data */
extern int16_t recv(SOCKET s, uint8_t *buf, int16_t len);

/**
 * \brief Wait for buffered transmission to complete.
 *
 * \note Currently, this function is empty -- it contains no logic.
 *
 * \param[in]	s	The socket on which to wait for buffered transmission completion to occur
 *
 */
extern void flush(SOCKET s);

/**
 * \brief Check if data is available on a socket
 *
 * \param[in]	s	The socket
 *
 * \return TODO
 */
extern int16_t recvAvailable(SOCKET s);

/**
 * \brief Returns the first byte in the receive queue (no checking)
 *
 * \param[in]	s	The socket of which to "peek" into the RX queue
 * \param[in]   buf	The pointer to the receive buffer of the socket
 *
 * \return Returns the first byte contained in the socket's recieve buffer (queue)
 */
extern uint16_t peek(SOCKET s, uint8_t *buf);


/**
 * \name Special Socket Operations
 * These functions are also low-level socket operations, however, their use is more specific, generally providing more
 * specific functionality, such as sending \b IGMP packets, or utilizing the \b IPRAW mode.
 */

/**
 * @{
 */


/**
 * \brief Send an IGMP message
 *
 * \param[in]	s	The socket to send the message from
 * \param[in]	buf	The data buffer containing the IGMP message to be sent
 * \param[in]	len	The length of the IGMP message to be sent
 *
 * \return TODO
 */
extern uint16_t igmpsend(SOCKET s, const uint8_t *buf, uint16_t len);




/**
 * \brief Send data (UDP and IPRAW modes)
 *
 * \param[in]	s		The socket to operate on
 * \param[in]	buf		A pointer to the data buffer containing the data to be sent
 * \param[in]	len		The length of the data (contained in the buffer) which is to be sent
 * \param[in]	addr	A pointer to an array which contains the destination IP address
 * \param[in]	port	The port the data shall be sent to
 *
 * \return TODO
 */
extern uint16_t sendto(SOCKET s, const uint8_t *buf, uint16_t len, uint8_t *addr, uint16_t port);

/**
 * This function provides an application interface which is used to receive data in modes \e other than \b TCP mode. The
 * function is used to handle the following data types:
 * \li \b UDP mode data
 * \li \b IP_RAW mode data
 * \li \b MAC_RAW mode data
 * \li The header of incoming packets
 *
 * \brief Receive data (UDP and IPRAW modes)
 *
 * \param[in]	s		The socket to operate on
 * \param[out]	buf		A pointer to the data buffer to which the received data will be copied to
 * \param[in]	len		The length of the data (contained in the buffer) which is to be sent
 * \param addr
 * \param port
 * \return
 */
extern uint16_t recvfrom(SOCKET s, uint8_t *buf, uint16_t len, uint8_t *addr, uint16_t *port);

/**
 * @}
 */

/**
 * \name BufferedUDPSend
 * Functions to allow buffered UDP send
 * (ie: where the UDP datagram is built up over a number of calls before being sent)
 */

/**
 * @{
 */

/**
 * This function sets up a UDP datagram, the data for which will be provided by one or more calls to bufferData(), and
 * then finally sent with the sendUDP() function.
 *
 * \brief Start creation of a new UDP datagram, for buffered UDP send
 *
 * \param[in]	s		The socket which will be used to send the datagram
 * \param[in]	addr	A pointer to the array holding the IP address which the UDP datagram is destined for
 * \param[in]	port	The UDP port for which the UDP datagram is destined for
 *
 * \return		Indicates whether the datagram was successfully setup.
 * \retval	1	The datagram was successfully set up
 * \retval	0	There was an error
 */
extern int startUDP(SOCKET s, uint8_t *addr, uint16_t port);


/**
 * This function copies up to len bytes of data from buf into a UDP datagram to be sent later by the sendUDP() function.
 * This allows datagrams to be built up from a series of bufferData() calls.
 *
 * \brief Copies data from a buffer into an ("under construction") UDP datagram, to be sent later.
 *
 * \return	Number of bytes successfully added to the UDP datagram buffer.
 */
uint16_t bufferData(SOCKET s, uint16_t offset, const uint8_t *buf, uint16_t len);


/**
 * Send a UDP datagram, which was built up from a sequence of startUDP, followed by one-or-more calls to bufferData()
 * (this sequence "builds" a UDP packet suitable for transmission).
 *
 * \brief Send a "pre-built" UDP datagram.
 *
 * \return	Provides indication as to whether the UDP datagram was successfully transmitted.
 * \retval	1	The UDP datagram was successfully transmitted.
 * \retval	0	Transmission failed due to an error.
 */
int sendUDP(SOCKET s);

/**
 * @}
 */

/**
 * @}
 */


#endif	/* _UTILITY_SOCKET_H__ */
