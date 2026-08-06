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
//	Lookup tables.
//	Do not try to look them up :-).
//	In the order of appearance: 
//
//	INT32 finetangent[4096]	- Tangens LUT.
//	 Should work with BAM fairly well (12 of 16bit,
//      effectively, by shifting).
//
//	INT32 finesine[10240]		- Sine lookup.
//	 Guess what, serves as cosine, too.
//	 Remarkable thing is, how to use BAMs with this? 
//
//	INT32 tantoangle[2049]	- ArcTan LUT,
//	  maps tan(angle) to angle fast. Gotta search.	
//    
//-----------------------------------------------------------------------------


#ifndef __TABLES__
#define __TABLES__



#ifdef LINUX
#include <math.h>
#else
#define PI				3.141592657
#endif


#include "m_fixed.h"

#define FIXED_MASK_CJB		0xFFFFFFFFL

#define FINEANGLES		8192
#define FINEMASK		(FINEANGLES-1)


// 0x100000000 to 0x2000
#define ANGLETOFINESHIFT	19		

// Effective size is 10240.
extern  fixed_t		finesine[5*FINEANGLES/4];
#define FINESINE(theta) (INT32)(finesine[(theta)] & FIXED_MASK_CJB)
//#define FINESINE(theta) finesine[(theta)]

// Re-use data, is just PI/2 pahse shift.
extern  fixed_t*	finecosine;
#define FINECOSINE(theta) (INT32)(finecosine[(theta)] & FIXED_MASK_CJB)
//#define FINECOSINE(theta) finecosine[(theta)]


// Effective size is 4096.
extern fixed_t		finetangent[FINEANGLES/2];
#define FINETANGENT(theta) (INT32)(finetangent[(theta)] & FIXED_MASK_CJB)
//#define FINETANGENT(theta) finetangent[(theta)]

// Binary Angle Measument, BAM.
#define ANG45			0x20000000
#define ANG90			0x40000000
#define ANG180		0x80000000
#define ANG270		0xc0000000


#define SLOPERANGE		2048
#define SLOPEBITS		11
#define DBITS			(FRACBITS-SLOPEBITS)

typedef UINT32 angle_t;


// Effective size is 2049;
// The +1 size is to handle the case when x==y
//  without additional checking.
extern angle_t		tantoangle[SLOPERANGE+1];
#define TANTOANGLE(m) (INT32)(tantoangle[(m)] & FIXED_MASK_CJB)
//#define TANTOANGLE(m) tantoangle[(m)]


// Utility function,
//  called by R_PointToAngle.
INT32
SlopeDiv
( UINT32	num,
  UINT32	den);


#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
