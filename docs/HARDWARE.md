# **EnhancedEthernet** Supported Hardware #

Initially, **EnhancedEthernet** will support Ethernet interfaces based on the **[WIZnet][1a] [W5100][1b] Ethernet Interface**, which is the chipset used in the original **[Arduino Ethernet shield][2]**.

Beyond the official hardware, a plethora of _3rd-party_ implementations of the official Ethernet shield are available _(also based on the **[W5100][1b]** chipset)_.

Finally, hardware taking a different form factor, the _"breakout board"_, also based on the **[W5100][1b]** chipset, are available from a variety of vendors.

Ideally, all of these devices should function in a similar manner. However, some differences may be present, and they shall be noted below. Additionally, pinout and connection information can be found below, to ease hardware design based on known usage of GPIO/pin resouces.


## Shields ##

This section will cover **[W5100][1b]-based hardware** in the _**"shield"** form factor_.


### Arduino Ethernet Shield - _Version 1_ **(Official Hardware)** ###

Though now considered [obsolete][2] by the Arduino developers, many of these boards are out in the wild, actively being used in pretty much any application imaginable. As such, it seems prudent to start here; after all, this is what started it all _(**Ethernet** on the Arduino)_.

#### Pin Usage ####

Below is the official pinout:

- ``MOSI`` - **SPI** _"Master-Out, Slave-In"_
	- Connection made via the **ICSP** header
	- Uses **Digital Pin 11** on the Arduino Uno
	- Uses **Digital Pin 51** on the Arduino Mega
- ``MISO`` - **SPI** _"Master-In, Slave-Out"_
	- Connection made via the **ICSP** header
	- Uses **Digital Pin 12** on the Arduino Uno
	- Uses **Digital Pin 50** on the Arduino Mega
- ``SCK`` - **SPI** _"Serial Clock"_
	- Connection made via the **ICSP** header
	- Uses **Digital Pin 13** on the Arduino Uno
	- Uses **Digital Pin 52** on the Arduino Mega
- ``SS (Ethernet)`` - **SPI** _"Slave Select"_ for the Ethernet interface
	- Uses **Digital Pin 10** on the Arduino Uno
	- Uses **Digital Pin 10** on the Arduino Mega, with the caveat that the hardware ``SS`` pin (**Digital Pin 53**) must be configured as an **OUTPUT**, else the SPI library will fail to function correctly
- ``SS (microSD Card)`` - **SPI** _"Slave Select"_ for the microSD card
	- Uses **Digital Pin 4** on the Arduino Uno
	- Uses **Digital Pin 4** on the Arduino Mega
- ``IRQ (Ethernet)`` - **Interrupt Request** for the Ethernet interface
	- **No physical connection to shield pins, _by default_**
		- Must be connected by joining the small solder bridge on the bottom side of the PCB
	- Once connected, uses **Digital Pin 2** _(external interrupt 0)_ on the Arduino Uno
	- **No support for use of the ``IRQ`` pin/function in the "default" Ethernet library**
		- _One of the primary goals of this project is the addition of Ethernet ``IRQ`` functionality_











[1a]:	<http://site.tld/a>
[1b]:	<http://site.tld/b>
[2]:	<https://www.arduino.cc/en/Main/ArduinoEthernetShieldV1>
