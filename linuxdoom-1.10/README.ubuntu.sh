#! /bin/sh
# Prerequisites for building and running 32-bit Linux DOOM on clean x64 Ubuntu
sudo dpkg --add-architecture i386
sudo apt update
sudo apt install gcc
sudo apt-get install gcc-multilib g++-multilib
sudo apt install libx11-dev:i386
sudo apt install libx11-dev xserver-xorg-dev xorg-dev
sudo apt install libx11-dev:i386 xserver-xorg-dev:i386 xorg-dev:i386
sudo apt install libx11-dev:i386 xserver-xorg-dev:i386
sudo apt-get install libxext6:i386
sudo apt-get install libxrender1:i386 libxtst6:i386 libxi6:i386
sudo apt install libx11-dev:i386
sudo apt install libx11-dev:i386 libxext-dev:i386 libxrender-dev:i386 xserver-xorg-dev:i386
sudo apt install xserver-xephyr
sudo apt install xterm
sudo apt install padsp
sudo apt install pulseaudio pulseaudio-utils
sudo apt install libpulsedsp
sudo apt install libpulsedsp:i386
sudo apt install osspd
sudo apt install osspd:i36

# Modifications to the padsp startup files
# to hard-code the correct 32-bit libraries
#sudo cp padsp/padsp_32 /usr/bin/
#sudo chmod 755 /usr/bin/padsp_32
#sudo cp padsp/padsp_64 /usr/bin/
#sudo chmod 755 /usr/bin/padsp_64

#$ diff /usr/bin/padsp /usr/bin/padsp_32
#77c77
#<    LD_PRELOAD="/usr/\\$$LIB/pulseaudio/libpulsedsp.so"
#---
#>    LD_PRELOAD="/usr/lib/i386-linux-gnu/pulseaudio/libpulsedsp.so"
#79c79
#<    LD_PRELOAD="$LD_PRELOAD /usr/\\$$LIB/pulseaudio/libpulsedsp.so"
#---
#>    LD_PRELOAD="$LD_PRELOAD /usr/lib/i386-linux-gnu/pulseaudio/libpulsedsp.so"
sudo cp /usr/bin/padsp /usr/bin/padsp_32
sudo vi !$

#$ diff /usr/bin/padsp /usr/bin/padsp_64
#77c77
#<    LD_PRELOAD="/usr/\\$$LIB/pulseaudio/libpulsedsp.so"
#---
#>    LD_PRELOAD="/usr/lib/x86_64-linux-gnu/pulseaudio/libpulsedsp.so"
#79c79
#<    LD_PRELOAD="$LD_PRELOAD /usr/\\$$LIB/pulseaudio/libpulsedsp.so"
#---
#>    LD_PRELOAD="$LD_PRELOAD /usr/lib/x86_64-linux-gnu/pulseaudio/libpulsedsp.so"
sudo cp /usr/bin/padsp /usr/bin/padsp_64
sudo vi !$

# Modifications to the base repository
# -- Also get yourself a copy of shareware version 1.9 (Demo) DOOM1.WAD
# -- e.g. from Internet Archive
git clone https://github.com/id-Software/DOOM.git
git switch -c ubuntu
# DOOM
cd DOOM
vi .gitignore
cd linuxdoom-1.10/
vi ../.gitignore
vi Makefile
vi i_video.c
vi i_sound.c
vi launch.sh
chmod 755 launch.sh 
mv DOOM1.WAD foo; mv foo doom1.wad
cp doom1.wad ../sndserv/
# SNDSERVER
pushd ../sndserv
cp ../linuxdoom-1.10/doom1.wad .
vi Makefile
vi linux.c
# Build and test sndserver
mkdir linux
make clean
make
padsp_32 linux/sndserver
cp linux/sndserver ../linuxdoom-1.10/
popd
# Build and run doom
mkdir linux
make clean
make
./launch.sh

