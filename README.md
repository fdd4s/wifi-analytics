# Wifi Analytics Monitor: an opensource wifi presence analytics monitor

## What it does

wmon (Wifi MONitor) captures mac address and RSSI (signal strength) of wifi packets received by a wifi device in monitor mode (passively, it doesnt send data of any kind).

## How it works

wmon capture whole wifi network packets, i.e: this software doesnt capture only probe requests, it captures everything. Even in encrypted wifi networks, MAC address is never encrypted. wmon saves only the higher RSSI each minute for every MAC. So if the device keeps sending data through wifi, you can monitor when the device enters and exit in the coverage range, with the signal strength every minute.

## Uses

- indoor position tracking: Running wmon over enough capture devices you can track RSSI of a MAC address in every position and know how it's moving.  
- time control of employees: Control when a MAC enters and exit in the coverage range.  
- customers counting in retail: Control the number of different MAC addresses that enter in the coverage range every moment.

## Recommended hardware

- X88 Pro 10 Android Box compatible with ARMBian https://s.click.aliexpress.com/e/_olSWtLz (Rk3318 Armbian image)  
- Wifi N 2.4 GHz USB dongle with RPSMA external antenna connector https://s.click.aliexpress.com/e/_okFfSkb "USB Wifi Adapter 150Mbps 2.4 ghz Antenna USB 802.11n/g/b Ethernet Wi-fi dongle RTL8188 Wireless Network Card for PC Windows" Compatible with last ARMBian version.  
- 2.4 GHz Yagi Antenna with SMA connector with antenna pigtail RPSMA to SMA connector https://s.click.aliexpress.com/e/_oDmNKmr "16dBi 2.4GHz WIFI Yagi Directional Antenna Enhanced Signal Notebook Desktop PC Computer USB Wireless Network Card PCIE Adapter"  
- SMA to RPSMA connector to avoid the use of pigtail in the previous antenna https://s.click.aliexpress.com/e/_oCpHgcL  
- USB Extension cable for Wifi N USB Dongle https://s.click.aliexpress.com/e/_onG80rP it's always better to use USB extension cable than a Pigtail antenna extension cable because pigtals always have some degree of RF signal loss.  

## Hardware requirements

It needs a wifi device supporting monitor mode in aircrack-ng over linux

## Successfully tested in the next platforms

- OpenWRT Barrier Breaker over Router TP-Link MR-3220 / MR-3420. Around 35$ hardware total cost and 5-10W energy consumption  
- ARMBian over Android Box X88Pro10 and TP-Link TL-WN722N USB dongle. Around 40$ hardware total cost and 5-10W energy consumption  
- Ubuntu over PC and TP-Link TL-WN722N USB dongle  

## Dependencies

aircrack-ng

## Compiling

Just run make

## Set up a wifi interface in monitor mode

First delete wifi interface created by operating system

e.g in openwrt: 
	wifi down  
	iw wlan0 del

Then create a wifi interface in monitor mode:
	iw phy0 interface add wlan0 type monitor  
	airmon-ng start wlan0

## Running

If the wifi interface in monitor mode is wlan0, then run:  
sudo ./wmon wlan0  

## Additional tools

one wifi device can only listen one wifi channel at the same time, to maximize the amount of information received you can run the script: change-channel.sh  
It changes the wifi channel every second  
e.g: sudo ./change-channel.sh wlan0

## Related projects

https://github.com/fdd4s/FH8616_CCTV_Security_Camera  
https://github.com/armbian/community/releases/ Use "Rk3318" Bookworm minimal image to run this software over X88 Pro 10 Android Box.  

## Credits

Created by fdd4s  
Send feedback and questions to fc1471789@gmail.com  
All files are public domain https://unlicense.org/
