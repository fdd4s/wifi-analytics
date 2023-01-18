# Wifi Analytics Monitor: an opensource wifi presence analytics monitor

## What does

wmon captures mac address and RSSI (signal strength) of wifi packets received by a wifi device in monitor mode (passively, it doesnt send data of any kind).

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

## Credits

Created by fdd  
Send feedback and questions to fdd4776s@gmail.com  
All files are public domain https://unlicense.org/
