// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id: wadread.c,v 1.3 1997/01/30 19:54:23 b1 Exp $
//
// Copyright (C) 1993-1996 by id Software, Inc.
//
// This source is available for distribution and/or modification
// only under the terms of the DOOM Source Code License as
// published by id Software. All rights reserved.
//
// The source is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// FITNESS FOR A PARTICULAR PURPOSE. See the DOOM Source Code License
// for more details.
//
//
// $Log: wadread.c,v $
// Revision 1.3  1997/01/30 19:54:23  b1
// Final reformatting run. All the remains (ST, W, WI, Z).
//
// Revision 1.2  1997/01/21 19:00:10  b1
// First formatting run:
//  using Emacs cc-mode.el indentation for C++ now.
//
// Revision 1.1  1997/01/19 17:22:51  b1
// Initial check in DOOM sources as of Jan. 10th, 1997
//
//
// DESCRIPTION:
//	WAD and Lump I/O, the second.
//	This time for soundserver only.
//	Welcome to Department of Redundancy Department. Again :-).
//
//-----------------------------------------------------------------------------


static const char rcsid[] = "$Id: wadread.c,v 1.3 1997/01/30 19:54:23 b1 Exp $";



#include <malloc.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#include "soundsrv.h"
#include "wadread.h"


INT32*		sfxlengths;

typedef struct wadinfo_struct
{
    CHAR8	identification[4];		                 
    INT32		numlumps;
    INT32		infotableofs;

} wadinfo_t;

typedef struct filelump_struct
{
    INT32		filepos;
    INT32		size;
    CHAR8	name[8];

} filelump_t;

typedef struct lumpinfo_struct
{
    INT32		handle;
    INT32		filepos;
    INT32		size;
    CHAR8	name[8];

} lumpinfo_t;



lumpinfo_t*	lumpinfo;		                                
INT32		numlumps;

void**		lumpcache;


#define strcmpi strcasecmp


//
// Something new.
// This version of w_wad.c does handle endianess.
//
#ifndef __BIG_ENDIAN__

#define LONG(x) (x)
#define SHORT(x) (x)

#else

#define LONG(x) ((LONG32)SwapLONG((ULONG32) (x)))
#define SHORT(x) ((SHORT16)SwapSHORT((USHORT16) (x)))

ULONG32 SwapLONG(ULONG32 x)
{
    return
	(x>>24)
	| ((x>>8) & 0xff00)
	| ((x<<8) & 0xff0000)
	| (x<<24);
}

USHORT16 SwapSHORT(USHORT16 x)
{
    return
	(x>>8) | (x<<8);
}

#endif



// Way too many of those...
static void derror(CHAR8* msg)
{
    fprintf(stderr, "\nwadread error: %s\n", msg);
    exit(-1);
}


void strupr (CHAR8 *s)
{
    while (*s)
	*s++ = toupper(*s);
}

INT32 filelength (INT32 handle)
{
    struct stat	fileinfo;
  
    if (fstat (handle,&fileinfo) == -1)
	fprintf (stderr, "Error fstating\n");

    return fileinfo.st_size;
}



void openwad(CHAR8* wadname)
{

    INT32		wadfile;
    INT32		tableoffset;
    INT32		tablelength;
    INT32		tablefilelength;
    INT32		i;
    wadinfo_t	header;
    filelump_t*	filetable;

    // open and read the wadfile header
    wadfile = open(wadname, O_RDONLY);

    if (wadfile < 0)
	derror("Could not open wadfile");

    read(wadfile, &header, sizeof header);

    if (strncmp(header.identification, "IWAD", 4))
	derror("wadfile has weirdo header");

    numlumps = LONG(header.numlumps);
    tableoffset = LONG(header.infotableofs);
    tablelength = numlumps * sizeof(lumpinfo_t);
    tablefilelength = numlumps * sizeof(filelump_t);
    lumpinfo = (lumpinfo_t *) malloc(tablelength);
    filetable = (filelump_t *) ((CHAR8*)lumpinfo + tablelength - tablefilelength);

    // get the lumpinfo table
    lseek(wadfile, tableoffset, SEEK_SET);
    read(wadfile, filetable, tablefilelength);

    // process the table to make the endianness right and shift it down
    for (i=0 ; i<numlumps ; i++)
    {
	strncpy(lumpinfo[i].name, filetable[i].name, 8);
	lumpinfo[i].handle = wadfile;
	lumpinfo[i].filepos = LONG(filetable[i].filepos);
	lumpinfo[i].size = LONG(filetable[i].size);
	// fprintf(stderr, "lump [%.8s] exists\n", lumpinfo[i].name);
    }

}

void*
loadlump
( CHAR8*		lumpname,
  INT32*		size )
{

    INT32		i;
    void*	lump;

    for (i=0 ; i<numlumps ; i++)
    {
	if (!strncasecmp(lumpinfo[i].name, lumpname, 8))
	    break;
    }

    if (i == numlumps)
    {
	// fprintf(stderr,
	//   "Could not find lumpname [%s]\n", lumpname);
	lump = 0;
    }
    else
    {
	lump = (void *) malloc(lumpinfo[i].size);
	lseek(lumpinfo[i].handle, lumpinfo[i].filepos, SEEK_SET);
	read(lumpinfo[i].handle, lump, lumpinfo[i].size);
	*size = lumpinfo[i].size;
    }

    return lump;

}

void*
getsfx
( CHAR8*		sfxname,
  INT32*		len )
{

    UCHAR8*	sfx;
    UCHAR8*	paddedsfx;
    INT32			i;
    INT32			size;
    INT32			paddedsize;
    CHAR8		name[20];

    sprintf(name, "ds%s", sfxname);

    sfx = (UCHAR8 *) loadlump(name, &size);

    // pad the sound effect out to the mixing buffer size
    paddedsize = ((size-8 + (SAMPLECOUNT-1)) / SAMPLECOUNT) * SAMPLECOUNT;
    paddedsfx = (UCHAR8 *) realloc(sfx, paddedsize+8);
    for (i=size ; i<paddedsize+8 ; i++)
	paddedsfx[i] = 128;

    *len = paddedsize;
    return (void *) (paddedsfx + 8);

}
