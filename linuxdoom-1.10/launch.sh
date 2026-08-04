#! /bin/sh
Xephyr :1 -screen 320x240x8 &
sleep 2
export DISPLAY=:1
DISPLAY=:1 linux/linuxxdoom &
