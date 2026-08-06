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
// $Log:$
//
// DESCRIPTION:
//	Mission begin melt/wipe screen special effect.
//
//-----------------------------------------------------------------------------


static const char rcsid[] = "$Id: f_wipe.c,v 1.2 1997/02/03 22:45:09 b1 Exp $";



#include "doomtype.h"

#include "z_zone.h"
#include "i_video.h"
#include "v_video.h"
#include "m_random.h"

#include "doomdef.h"

#include "f_wipe.h"

//
//                       SCREEN WIPE PACKAGE
//

// when zero, stop the wipe
static boolean	go = 0;

static byte*	wipe_scr_start;
static byte*	wipe_scr_end;
static byte*	wipe_scr;


void
wipe_shittyColMajorXform
( SHORT16*	array,
  INT32		width,
  INT32		height )
{
    INT32		x;
    INT32		y;
    SHORT16*	dest;

    dest = (SHORT16*) Z_Malloc(width*height*2, PU_STATIC, 0);

    for(y=0;y<height;y++)
	for(x=0;x<width;x++)
	    dest[x*height+y] = array[y*width+x];

    memcpy(array, dest, width*height*2);

    Z_Free(dest);

}

INT32
wipe_initColorXForm
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    memcpy(wipe_scr, wipe_scr_start, width*height);
    return 0;
}

INT32
wipe_doColorXForm
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    boolean	changed;
    byte*	w;
    byte*	e;
    INT32		newval;

    changed = false;
    w = wipe_scr;
    e = wipe_scr_end;
    
    while (w!=wipe_scr+width*height)
    {
	if (*w != *e)
	{
	    if (*w > *e)
	    {
		newval = *w - ticks;
		if (newval < *e)
		    *w = *e;
		else
		    *w = newval;
		changed = true;
	    }
	    else if (*w < *e)
	    {
		newval = *w + ticks;
		if (newval > *e)
		    *w = *e;
		else
		    *w = newval;
		changed = true;
	    }
	}
	w++;
	e++;
    }

    return !changed;

}

INT32
wipe_exitColorXForm
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    return 0;
}


static INT32*	y;

INT32
wipe_initMelt
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    INT32 i, r;
    
    // copy start screen to main screen
    memcpy(wipe_scr, wipe_scr_start, width*height);
    
    // makes this wipe faster (in theory)
    // to have stuff in column-major format
    wipe_shittyColMajorXform((SHORT16*)wipe_scr_start, width/2, height);
    wipe_shittyColMajorXform((SHORT16*)wipe_scr_end, width/2, height);
    
    // setup initial column positions
    // (y<0 => not ready to scroll yet)
    y = (INT32 *) Z_Malloc(width*sizeof(INT32), PU_STATIC, 0);
    y[0] = -(M_Random()%16);
    for (i=1;i<width;i++)
    {
	r = (M_Random()%3) - 1;
	y[i] = y[i-1] + r;
	if (y[i] > 0) y[i] = 0;
	else if (y[i] == -16) y[i] = -15;
    }

    return 0;
}

INT32
wipe_doMelt
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    INT32		i;
    INT32		j;
    INT32		dy;
    INT32		idx;
    
    SHORT16*	s;
    SHORT16*	d;
    boolean	done = true;

    width/=2;

    while (ticks--)
    {
	for (i=0;i<width;i++)
	{
	    if (y[i]<0)
	    {
		y[i]++; done = false;
	    }
	    else if (y[i] < height)
	    {
		dy = (y[i] < 16) ? y[i]+1 : 8;
		if (y[i]+dy >= height) dy = height - y[i];
		s = &((SHORT16 *)wipe_scr_end)[i*height+y[i]];
		d = &((SHORT16 *)wipe_scr)[y[i]*width+i];
		idx = 0;
		for (j=dy;j;j--)
		{
		    d[idx] = *(s++);
		    idx += width;
		}
		y[i] += dy;
		s = &((SHORT16 *)wipe_scr_start)[i*height];
		d = &((SHORT16 *)wipe_scr)[y[i]*width+i];
		idx = 0;
		for (j=height-y[i];j;j--)
		{
		    d[idx] = *(s++);
		    idx += width;
		}
		done = false;
	    }
	}
    }

    return done;

}

INT32
wipe_exitMelt
( INT32	width,
  INT32	height,
  INT32	ticks )
{
    Z_Free(y);
    return 0;
}

INT32
wipe_StartScreen
( INT32	x,
  INT32	y,
  INT32	width,
  INT32	height )
{
    wipe_scr_start = screens[2];
    I_ReadScreen(wipe_scr_start);
    return 0;
}

INT32
wipe_EndScreen
( INT32	x,
  INT32	y,
  INT32	width,
  INT32	height )
{
    wipe_scr_end = screens[3];
    I_ReadScreen(wipe_scr_end);
    V_DrawBlock(x, y, 0, width, height, wipe_scr_start); // restore start scr.
    return 0;
}

INT32
wipe_ScreenWipe
( INT32	wipeno,
  INT32	x,
  INT32	y,
  INT32	width,
  INT32	height,
  INT32	ticks )
{
    INT32 rc;
    static INT32 (*wipes[])(INT32, INT32, INT32) =
    {
	wipe_initColorXForm, wipe_doColorXForm, wipe_exitColorXForm,
	wipe_initMelt, wipe_doMelt, wipe_exitMelt
    };

    void V_MarkRect(INT32, INT32, INT32, INT32);

    // initial stuff
    if (!go)
    {
	go = 1;
	// wipe_scr = (byte *) Z_Malloc(width*height, PU_STATIC, 0); // DEBUG
	wipe_scr = screens[0];
	(*wipes[wipeno*3])(width, height, ticks);
    }

    // do a piece of wipe-in
    V_MarkRect(0, 0, width, height);
    rc = (*wipes[wipeno*3+1])(width, height, ticks);
    //  V_DrawBlock(x, y, 0, width, height, wipe_scr); // DEBUG

    // final stuff
    if (rc)
    {
	go = 0;
	(*wipes[wipeno*3+2])(width, height, ticks);
    }

    return !go;

}
