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
//	Refresh/render internal state variables (global).
//
//-----------------------------------------------------------------------------


#ifndef __R_STATE__
#define __R_STATE__

// Need data structure definitions.
#include "d_player.h"
#include "r_data.h"



#ifdef __GNUG__
#pragma interface
#endif



//
// Refresh internal data structures,
//  for rendering.
//

// needed for texture pegging
extern fixed_t*		textureheight;

// needed for pre rendering (fracs)
extern fixed_t*		spritewidth;

extern fixed_t*		spriteoffset;
extern fixed_t*		spritetopoffset;

extern lighttable_t*	colormaps;

extern INT32		viewwidth;
extern INT32		scaledviewwidth;
extern INT32		viewheight;

extern INT32		firstflat;

// for global animation
extern INT32*		flattranslation;	
extern INT32*		texturetranslation;	


// Sprite....
extern INT32		firstspritelump;
extern INT32		lastspritelump;
extern INT32		numspritelumps;



//
// Lookup tables for map data.
//
extern INT32		numsprites;
extern spritedef_t*	sprites;

extern INT32		numvertexes;
extern vertex_t*	vertexes;

extern INT32		numsegs;
extern seg_t*		segs;

extern INT32		numsectors;
extern sector_t*	sectors;

extern INT32		numsubsectors;
extern subsector_t*	subsectors;

extern INT32		numnodes;
extern node_t*		nodes;

extern INT32		numlines;
extern line_t*		lines;

extern INT32		numsides;
extern side_t*		sides;


//
// POV data.
//
extern fixed_t		viewx;
extern fixed_t		viewy;
extern fixed_t		viewz;

extern angle_t		viewangle;
extern player_t*	viewplayer;


// ?
extern angle_t		clipangle;

extern INT32		viewangletox[FINEANGLES/2];
extern angle_t		xtoviewangle[SCREENWIDTH+1];
//extern fixed_t		finetangent[FINEANGLES/2];

extern fixed_t		rw_distance;
extern angle_t		rw_normalangle;



// angle to line origin
extern INT32		rw_angle1;

// Segs count?
extern INT32		sscount;

extern visplane_t*	floorplane;
extern visplane_t*	ceilingplane;


#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
