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
// DESCRIPTION:
// 	The status bar widget code.
//
//-----------------------------------------------------------------------------

#ifndef __STLIB__
#define __STLIB__


// We are referring to patches.
#include "r_defs.h"


//
// Background and foreground screen numbers
//
#define BG 4
#define FG 0



//
// Typedefs of widgets
//

// Number widget

typedef struct
{
    // upper right-hand corner
    //  of the number (right-justified)
    INT32		x;
    INT32		y;

    // max # of digits in number
    INT32 width;    

    // last number value
    INT32		oldnum;
    
    // pointer to current value
    INT32*	num;

    // pointer to boolean stating
    //  whether to update number
    boolean*	on;

    // list of patches for 0-9
    patch_t**	p;

    // user data
    INT32 data;
    
} st_number_t;



// Percent widget ("child" of number widget,
//  or, more precisely, contains a number widget.)
typedef struct
{
    // number information
    st_number_t		n;

    // percent sign graphic
    patch_t*		p;
    
} st_percent_t;



// Multiple Icon widget
typedef struct
{
     // center-justified location of icons
    INT32			x;
    INT32			y;

    // last icon number
    INT32			oldinum;

    // pointer to current icon
    INT32*		inum;

    // pointer to boolean stating
    //  whether to update icon
    boolean*		on;

    // list of icons
    patch_t**		p;
    
    // user data
    INT32			data;
    
} st_multicon_t;




// Binary Icon widget

typedef struct
{
    // center-justified location of icon
    INT32			x;
    INT32			y;

    // last icon value
    INT32			oldval;

    // pointer to current icon status
    boolean*		val;

    // pointer to boolean
    //  stating whether to update icon
    boolean*		on;  


    patch_t*		p;	// icon
    INT32			data;   // user data
    
} st_binicon_t;



//
// Widget creation, access, and update routines
//

// Initializes widget library.
// More precisely, initialize STMINUS,
//  everything else is done somewhere else.
//
void STlib_init(void);



// Number widget routines
void
STlib_initNum
( st_number_t*		n,
  INT32			x,
  INT32			y,
  patch_t**		pl,
  INT32*			num,
  boolean*		on,
  INT32			width );

void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh );


// Percent widget routines
void
STlib_initPercent
( st_percent_t*		p,
  INT32			x,
  INT32			y,
  patch_t**		pl,
  INT32*			num,
  boolean*		on,
  patch_t*		percent );


void
STlib_updatePercent
( st_percent_t*		per,
  INT32			refresh );


// Multiple Icon widget routines
void
STlib_initMultIcon
( st_multicon_t*	mi,
  INT32			x,
  INT32			y,
  patch_t**		il,
  INT32*			inum,
  boolean*		on );


void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh );

// Binary Icon widget routines

void
STlib_initBinIcon
( st_binicon_t*		b,
  INT32			x,
  INT32			y,
  patch_t*		i,
  boolean*		val,
  boolean*		on );

void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh );

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
