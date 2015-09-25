#!/bin/sh

make > /dev/null 2>&1
sudo insmod fs.ko
mkdir tmp
sudo mount -t myfs none tmp
ls -l tmp
sudo umount tmp
