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
//	Refresh, visplane stuff (floor, ceilings).
//
//-----------------------------------------------------------------------------


#ifndef __R_PLANE__
#define __R_PLANE__


#include "r_data.h"

#ifdef __GNUG__
#pragma interface
#endif


// Visplane related.
extern  SHORT16*		lastopening;


typedef void (*planefunction_t) (INT32 top, INT32 bottom);

extern planefunction_t	floorfunc;
extern planefunction_t	ceilingfunc_t;

extern SHORT16		floorclip[SCREENWIDTH];
extern SHORT16		ceilingclip[SCREENWIDTH];

extern fixed_t		yslope[SCREENHEIGHT];
extern fixed_t		distscale[SCREENWIDTH];

void R_InitPlanes (void);
void R_ClearPlanes (void);

void
R_MapPlane
( INT32		y,
  INT32		x1,
  INT32		x2 );

void
R_MakeSpans
( INT32		x,
  INT32		t1,
  INT32		b1,
  INT32		t2,
  INT32		b2 );

void R_DrawPlanes (void);

visplane_t*
R_FindPlane
( fixed_t	height,
  INT32		picnum,
  INT32		lightlevel );

visplane_t*
R_CheckPlane
( visplane_t*	pl,
  INT32		start,
  INT32		stop );



#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
