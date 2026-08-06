##########################################################
#
# $Id:$
#
# $Log:$
#
#

CC=gcc
CFLAGS=-m32 -O -DNORMALUNIX -DLINUX
LDFLAGS=-L/usr/lib/i386-linux-gnu/
LIBS=-lm

O=linux

all:	 $(O)/sndserver

clean:
	rm -f *.o *~ *.flc
	rm -f linux/*
	rm -f preprocessor.txt

prep:	soundsrv.c sounds.c wadread.c linux.c
	rm -f preprocessor.txt
	$(CC) -E $(CFLAGS) soundsrv.c sounds.c wadread.c linux.c | grep . | awk '{$$1=$$1};1' >> preprocessor.txt

# Target
$(O)/sndserver: \
	$(O)/soundsrv.o \
	$(O)/sounds.o \
	$(O)/wadread.o \
	$(O)/linux.o
	$(CC) $(CFLAGS) $(LDFLAGS) \
	$(O)/soundsrv.o \
	$(O)/sounds.o \
	$(O)/wadread.o \
	$(O)/linux.o -o $(O)/sndserver $(LIBS)
	echo make complete.

# Rule
$(O)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


