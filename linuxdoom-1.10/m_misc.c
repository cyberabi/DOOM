// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
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
// $Log:$
//
// DESCRIPTION:
//	Main loop menu stuff.
//	Default Config File.
//	PCX Screenshots.
//
//-----------------------------------------------------------------------------

static const char
rcsid[] = "$Id: m_misc.c,v 1.6 1997/02/03 22:45:10 b1 Exp $";

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include <ctype.h>

#include "doomtype.h"
#include "doomdef.h"

#include "z_zone.h"

#include "m_swap.h"
#include "m_argv.h"

#include "w_wad.h"

#include "i_system.h"
#include "i_video.h"
#include "v_video.h"

#include "hu_stuff.h"

// State.
#include "doomstat.h"

// Data.
#include "dstrings.h"

#include "m_misc.h"

//
// M_DrawText
// Returns the final X coordinate
// HU_Init must have been called to init the font
//
extern patch_t*		hu_font[HU_FONTSIZE];

INT32
M_DrawText
( INT32		x,
  INT32		y,
  boolean	direct,
  CHAR8*		string )
{
    INT32 	c;
    INT32		w;

    while (*string)
    {
	c = toupper(*string) - HU_FONTSTART;
	string++;
	if (c < 0 || c> HU_FONTSIZE)
	{
	    x += 4;
	    continue;
	}
		
	w = SHORT (hu_font[c]->width);
	if (x+w > SCREENWIDTH)
	    break;
	if (direct)
	    V_DrawPatchDirect(x, y, 0, hu_font[c]);
	else
	    V_DrawPatch(x, y, 0, hu_font[c]);
	x+=w;
    }

    return x;
}




//
// M_WriteFile
//
#ifndef O_BINARY
#define O_BINARY 0
#endif

boolean
M_WriteFile
( CHAR8 const*	name,
  void*		source,
  INT32		length )
{
    INT32		handle;
    INT32		count;
	
    handle = open ( name, O_WRONLY | O_CREAT | O_TRUNC | O_BINARY, 0666);

    if (handle == -1)
	return false;

    count = write (handle, source, length);
    close (handle);
	
    if (count < length)
	return false;
		
    return true;
}


//
// M_ReadFile
//
INT32
M_ReadFile
( CHAR8 const*	name,
  byte**	buffer )
{
    INT32	handle, count, length;
    struct stat	fileinfo;
    byte		*buf;
	
    handle = open (name, O_RDONLY | O_BINARY, 0666);
    if (handle == -1)
	I_Error ("Couldn't read file %s", name);
    if (fstat (handle,&fileinfo) == -1)
	I_Error ("Couldn't read file %s", name);
    length = fileinfo.st_size;
    buf = Z_Malloc (length, PU_STATIC, NULL);
    count = read (handle, buf, length);
    close (handle);
	
    if (count < length)
	I_Error ("Couldn't read file %s", name);
		
    *buffer = buf;
    return length;
}


//
// DEFAULTS
//
INT32		usemouse;
INT32		usejoystick;

extern INT32	key_right;
extern INT32	key_left;
extern INT32	key_up;
extern INT32	key_down;

extern INT32	key_strafeleft;
extern INT32	key_straferight;

extern INT32	key_fire;
extern INT32	key_use;
extern INT32	key_strafe;
extern INT32	key_speed;

extern INT32	mousebfire;
extern INT32	mousebstrafe;
extern INT32	mousebforward;

extern INT32	joybfire;
extern INT32	joybstrafe;
extern INT32	joybuse;
extern INT32	joybspeed;

extern INT32	viewwidth;
extern INT32	viewheight;

extern INT32	mouseSensitivity;
extern INT32	showMessages;

extern INT32	detailLevel;

extern INT32	screenblocks;

extern INT32	showMessages;

// machine-independent sound params
extern	INT32	numChannels;


// UNIX hack, to be removed.
#ifdef SNDSERV
extern CHAR8*	sndserver_filename;
extern INT32	mb_used;
#endif

#ifdef LINUX
CHAR8*		mousetype;
CHAR8*		mousedev;
#endif

extern CHAR8*	chat_macros[];



typedef struct
{
    CHAR8*	name;
    INT32*	location;
    INT32		defaultvalue;
    INT32		scantranslate;		// PC scan code hack
    INT32		untranslated;		// lousy hack
} default_t;

default_t	defaults[] =
{
    {"mouse_sensitivity",&mouseSensitivity, 5},
    {"sfx_volume",&snd_SfxVolume, 8},
    {"music_volume",&snd_MusicVolume, 8},
    {"show_messages",&showMessages, 1},
    

#ifdef NORMALUNIX
    {"key_right",&key_right, KEY_RIGHTARROW},
    {"key_left",&key_left, KEY_LEFTARROW},
    {"key_up",&key_up, KEY_UPARROW},
    {"key_down",&key_down, KEY_DOWNARROW},
    {"key_strafeleft",&key_strafeleft, ','},
    {"key_straferight",&key_straferight, '.'},

    {"key_fire",&key_fire, KEY_RCTRL},
    {"key_use",&key_use, ' '},
    {"key_strafe",&key_strafe, KEY_RALT},
    {"key_speed",&key_speed, KEY_RSHIFT},

// UNIX hack, to be removed. 
#ifdef SNDSERV
    {"sndserver", (INT32 *) &sndserver_filename, (INT32) "sndserver"},
    {"mb_used", &mb_used, 2},
#endif
    
#endif

#ifdef LINUX
    {"mousedev", (INT32*)&mousedev, (INT32)"/dev/ttyS0"},
    {"mousetype", (INT32*)&mousetype, (INT32)"microsoft"},
#endif

    {"use_mouse",&usemouse, 1},
    {"mouseb_fire",&mousebfire,0},
    {"mouseb_strafe",&mousebstrafe,1},
    {"mouseb_forward",&mousebforward,2},

    {"use_joystick",&usejoystick, 0},
    {"joyb_fire",&joybfire,0},
    {"joyb_strafe",&joybstrafe,1},
    {"joyb_use",&joybuse,3},
    {"joyb_speed",&joybspeed,2},

    {"screenblocks",&screenblocks, 9},
    {"detaillevel",&detailLevel, 0},

    {"snd_channels",&numChannels, 3},



    {"usegamma",&usegamma, 0},

    {"chatmacro0", (INT32 *) &chat_macros[0], (INT32) HUSTR_CHATMACRO0 },
    {"chatmacro1", (INT32 *) &chat_macros[1], (INT32) HUSTR_CHATMACRO1 },
    {"chatmacro2", (INT32 *) &chat_macros[2], (INT32) HUSTR_CHATMACRO2 },
    {"chatmacro3", (INT32 *) &chat_macros[3], (INT32) HUSTR_CHATMACRO3 },
    {"chatmacro4", (INT32 *) &chat_macros[4], (INT32) HUSTR_CHATMACRO4 },
    {"chatmacro5", (INT32 *) &chat_macros[5], (INT32) HUSTR_CHATMACRO5 },
    {"chatmacro6", (INT32 *) &chat_macros[6], (INT32) HUSTR_CHATMACRO6 },
    {"chatmacro7", (INT32 *) &chat_macros[7], (INT32) HUSTR_CHATMACRO7 },
    {"chatmacro8", (INT32 *) &chat_macros[8], (INT32) HUSTR_CHATMACRO8 },
    {"chatmacro9", (INT32 *) &chat_macros[9], (INT32) HUSTR_CHATMACRO9 }

};

INT32	numdefaults;
CHAR8*	defaultfile;


//
// M_SaveDefaults
//
void M_SaveDefaults (void)
{
    INT32		i;
    INT32		v;
    FILE*	f;
	
    f = fopen (defaultfile, "w");
    if (!f)
	return; // can't write the file, but don't complain
		
    for (i=0 ; i<numdefaults ; i++)
    {
	if (defaults[i].defaultvalue > -0xfff
	    && defaults[i].defaultvalue < 0xfff)
	{
	    v = *defaults[i].location;
	    fprintf (f,"%s\t\t%i\n",defaults[i].name,v);
	} else {
	    fprintf (f,"%s\t\t\"%s\"\n",defaults[i].name,
		     * (CHAR8 **) (defaults[i].location));
	}
    }
	
    fclose (f);
}


//
// M_LoadDefaults
//
extern byte	scantokey[128];

void M_LoadDefaults (void)
{
    INT32		i;
    INT32		len;
    FILE*	f;
    CHAR8	def[80];
    CHAR8	strparm[100];
    CHAR8*	newstring;
    INT32		parm;
    boolean	isstring;
    
    // set everything to base values
    numdefaults = sizeof(defaults)/sizeof(defaults[0]);
    for (i=0 ; i<numdefaults ; i++)
	*defaults[i].location = defaults[i].defaultvalue;
    
    // check for a custom default file
    i = M_CheckParm ("-config");
    if (i && i<myargc-1)
    {
	defaultfile = myargv[i+1];
	printf ("	default file: %s\n",defaultfile);
    }
    else
	defaultfile = basedefault;
    
    // read the file in, overriding any set defaults
    f = fopen (defaultfile, "r");
    if (f)
    {
	while (!feof(f))
	{
	    isstring = false;
	    if (fscanf (f, "%79s %[^\n]\n", def, strparm) == 2)
	    {
		if (strparm[0] == '"')
		{
		    // get a string default
		    isstring = true;
		    len = strlen(strparm);
		    newstring = (CHAR8 *) malloc(len);
		    strparm[len-1] = 0;
		    strcpy(newstring, strparm+1);
		}
		else if (strparm[0] == '0' && strparm[1] == 'x')
		    sscanf(strparm+2, "%x", &parm);
		else
		    sscanf(strparm, "%i", &parm);
		for (i=0 ; i<numdefaults ; i++)
		    if (!strcmp(def, defaults[i].name))
		    {
			if (!isstring)
			    *defaults[i].location = parm;
			else
			    *defaults[i].location =
				(INT32) newstring;
			break;
		    }
	    }
	}
		
	fclose (f);
    }
}


//
// SCREEN SHOTS
//


typedef struct
{
    CHAR8		manufacturer;
    CHAR8		version;
    CHAR8		encoding;
    CHAR8		bits_per_pixel;

    USHORT16	xmin;
    USHORT16	ymin;
    USHORT16	xmax;
    USHORT16	ymax;
    
    USHORT16	hres;
    USHORT16	vres;

    UCHAR8	palette[48];
    
    CHAR8		reserved;
    CHAR8		color_planes;
    USHORT16	bytes_per_line;
    USHORT16	palette_type;
    
    CHAR8		filler[58];
    UCHAR8	data;		// unbounded
} pcx_t;


//
// WritePCXfile
//
void
WritePCXfile
( CHAR8*		filename,
  byte*		data,
  INT32		width,
  INT32		height,
  byte*		palette )
{
    INT32		i;
    INT32		length;
    pcx_t*	pcx;
    byte*	pack;
	
    pcx = Z_Malloc (width*height*2+1000, PU_STATIC, NULL);

    pcx->manufacturer = 0x0a;		// PCX id
    pcx->version = 5;			// 256 color
    pcx->encoding = 1;			// uncompressed
    pcx->bits_per_pixel = 8;		// 256 color
    pcx->xmin = 0;
    pcx->ymin = 0;
    pcx->xmax = SHORT(width-1);
    pcx->ymax = SHORT(height-1);
    pcx->hres = SHORT(width);
    pcx->vres = SHORT(height);
    memset (pcx->palette,0,sizeof(pcx->palette));
    pcx->color_planes = 1;		// chunky image
    pcx->bytes_per_line = SHORT(width);
    pcx->palette_type = SHORT(2);	// not a grey scale
    memset (pcx->filler,0,sizeof(pcx->filler));


    // pack the image
    pack = &pcx->data;
	
    for (i=0 ; i<width*height ; i++)
    {
	if ( (*data & 0xc0) != 0xc0)
	    *pack++ = *data++;
	else
	{
	    *pack++ = 0xc1;
	    *pack++ = *data++;
	}
    }
    
    // write the palette
    *pack++ = 0x0c;	// palette ID byte
    for (i=0 ; i<768 ; i++)
	*pack++ = *palette++;
    
    // write output file
    length = pack - (byte *)pcx;
    M_WriteFile (filename, pcx, length);

    Z_Free (pcx);
}


//
// M_ScreenShot
//
void M_ScreenShot (void)
{
    INT32		i;
    byte*	linear;
    CHAR8	lbmname[12];
    
    // munge planar buffer to linear
    linear = screens[2];
    I_ReadScreen (linear);
    
    // find a file name to save it to
    strcpy(lbmname,"DOOM00.pcx");
		
    for (i=0 ; i<=99 ; i++)
    {
	lbmname[4] = i/10 + '0';
	lbmname[5] = i%10 + '0';
	if (access(lbmname,0) == -1)
	    break;	// file doesn't exist
    }
    if (i==100)
	I_Error ("M_ScreenShot: Couldn't create a PCX");
    
    // save the pcx file
    WritePCXfile (lbmname, linear,
		  SCREENWIDTH, SCREENHEIGHT,
		  W_CacheLumpName ("PLAYPAL",PU_CACHE));
	
    players[consoleplayer].message = "screen shot";
}


