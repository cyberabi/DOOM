#! /bin/sh
# Prerequisites for building and running 32-bit Linux DOOM on clean x64 Ubuntu
# Although is in the ubuntu branch of my copy of the repo, the script is written
# as if you are starting from the ID software original.
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc
sudo apt install make
sudo apt-get install gcc-multilib g++-multilib
sudo apt install libx11-dev xserver-xorg-dev xorg-dev
sudo apt install libx11-dev:i386 xserver-xorg-dev:i386
sudo apt install libx11-dev:i386 xserver-xorg-dev:i386
sudo apt-get install libxext6:i386
sudo apt-get install libxrender1:i386 libxtst6:i386 libxi6:i386
sudo apt install libx11-dev:i386
sudo apt install libx11-dev:i386 libxext-dev:i386 libxrender-dev:i386 xserver-xorg-dev:i386
sudo apt install xserver-xephyr
sudo apt install xterm
sudo apt install pulseaudio pulseaudio-utils
sudo apt install libpulsedsp
sudo apt install libpulsedsp:i386
sudo apt install osspd
sudo apt install osspd:i386
sudo apt install libnsl-dev:i386

# Modifications to the padsp startup files to
# hard-code the correct 32-bit and 64-bit libraries
sudo cp /usr/bin/padsp /usr/bin/padsp_32
sudo sed -i 's/\\\\\$\$LIB/lib\/i386-linux-gnu/' /usr/bin/padsp_32 
sudo sed -i 's/\\\$LIB/lib\/i386-linux-gnu/' /usr/bin/padsp_32 
sudo cp /usr/bin/padsp /usr/bin/padsp_64
sudo sed -i 's/\\\$\$LIB/lib\/x86_64-linux-gnu/' /usr/bin/padsp_64
sudo sed -i 's/\\\\\$LIB/lib\/x86_64-linux-gnu/' /usr/bin/padsp_64

