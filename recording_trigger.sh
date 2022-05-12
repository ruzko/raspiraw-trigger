#!/bin/bash

FILENAME="$(<gpio_pin_status.txt)"
#echo "$FILENAME"

if [ $FILENAME = '1' ]; then
#	640x64_s_jacob 800 10000
echo "HIGH"

elif [ $FILENAME = '0' ]; then
echo "LOW"

fi
