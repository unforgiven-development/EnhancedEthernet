# "EnhancedEthernet" Arduno Library #

This library, **EnhancedEthernet**, is pretty much as the name describes:
_An enhanced version of the official Arduino **Ethernet library**_

This library _(as well as the original **Ethernet library**)_ allows an Arduino board to connect to an Ethernet network,
providing access to network resources, from services located on the same LAN, to services located on the other side of
the world, via the internet. The **Ethernet library** _(as well as this **enhanced** version)_ are compatible with the
first generation of the official **Arduino Ethernet shield**, which utilizes the **WIZnet W5100** chipset.


## Enhancements ##

As implied by the name, there are some _enhancements_ to be expected.

The primary enhancement _(which happened to be the motivation for this project)_ is the addition of hardware interrupt
support for the **WIZnet W5100** Ethernet shield on AVR-based Arduino platforms.

It's likely that additional enhancements will work their way in, as well. A list can be found below:
* Hardware Interrupt Support



## License ##

	Copyright (c) 2017 Gerad Munsch <gmunsch@unforgivendevelopment.com>
	Copyright (c) 2010 Arduino LLC. All right reserved.

	This library is free software; you can redistribute it and/or
	modify it under the terms of the GNU Lesser General Public
	License as published by the Free Software Foundation; either
	version 2.1 of the License, or (at your option) any later version.

	This library is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
	Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public
	License along with this library; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
