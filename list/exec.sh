#!/bin/sh

make > /dev/null 2>&1
sudo insmod list.ko
sudo rmmod list
dmesg | tail
make clean > /dev/null 2>&1
