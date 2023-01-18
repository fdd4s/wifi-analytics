#!/bin/bash

ARGS=1
if [ "$#" -ne "$ARGS" ]; then
	echo "change-channel.sh <wifi interface>"
	exit 0
fi

while :
do
	iw "$1" set channel 1
	sleep 1
	iw "$1" set channel 2
	sleep 1
	iw "$1" set channel 3
	sleep 1
	iw "$1" set channel 4
	sleep 1
	iw "$1" set channel 5
	sleep 1
	iw "$1" set channel 6
	sleep 1
	iw "$1" set channel 7
	sleep 1
	iw "$1" set channel 8
	sleep 1
	iw "$1" set channel 9
	sleep 1
	iw "$1" set channel 10
	sleep 1
	iw "$1" set channel 11
	sleep 1
done

