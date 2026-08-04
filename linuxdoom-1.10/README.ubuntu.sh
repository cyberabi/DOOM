# Pseudo-script

# File modification and build instructions to get 32-bit Linux Doom running
# on Ubuntu (or Debian). This assumes you've already run PREREQUISITES.ubuntu.sh
# If you're on the 'ubuntu' branch, you already have the repo and all of the
# changes and can go straight to the builds.

# Fork the ID software repo
git clone https://github.com/id-Software/DOOM.git
git switch -c ubuntu
cd DOOM

# Modifications to the base repository
# You can see what the specific edits were to these files by comparing
# with the 'master' branch. This is more of an informative outline.

# Top level
vi .gitignore

# DOOM
cd linuxdoom-1.10/
vi Makefile
vi i_video.c
vi i_sound.c
vi am_map.c

# New launcher script to wrap everything in padp, Xephyr, and osspd
# compatibility layers.
vi launch.sh
chmod 755 launch.sh

# Get yourself a copy of shareware version 1.9 (Demo) DOOM1.WAD
# e.g. from Internet Archive, into the linuxdoom-1.10 folder before this.
# The double 'mv' is a gambit to change the case of the filename.
mv DOOM1.WAD foo; mv foo doom1.wad

# SNDSERVER
# We duplicate 'doom1.wad' here, for testing.
pushd ../sndserv
cp ../linuxdoom-1.10/doom1.wad .
vi Makefile
vi linux.c

# Build and test sndserver
mkdir linux
make clean
make
padsp_32 linux/sndserver

# We'll need a copy of sndserver in our launch folder, later
cp linux/sndserver ../linuxdoom-1.10/
chmod 755 ../linuxdoom-1.10/sndserver
popd

# Build and run doom with sndserver
mkdir linux
make clean
make
./launch.sh

# If all went well, DOOM should launch in a small window,
# and you should hear sound effects when navigating the
# menus or playing the game. No music.
