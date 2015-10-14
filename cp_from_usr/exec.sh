#!/bin/sh

make > /dev/null 2>&1
sudo insmod char.ko
sudo mknod /dev/testchar c 232 0
sudo ./orz
sudo rm /dev/testchar
sudo rmmod char
dmesg | tail
make clean > /dev/null 2>&1
