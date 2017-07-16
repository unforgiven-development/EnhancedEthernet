/**
 * \file WebServerInterrupts.ino
 * An example
 */


#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>

/* ------------------------------------------------------------------------------------------------------------------ */

#define WEB_SERVER_PORT 80
#define USE_STATIC_IP 0


#if (USE_STATIC_IP == 1) || defined(USE_STATIC_IP)
IPAddress staticIP(192, 168, 1, 123);
IPAddress subnetMask(255, 255, 255, 0);
IPAddress gatewayIP(192, 168, 1, 1);
IPAddress dnsServerIP(8, 8, 8, 8);
#endif

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetServer webServer(WEB_SERVER_PORT);


/* ------------------------------------------------------------------------------------------------------------------ */

void setup() {

}

void loop() {

}
