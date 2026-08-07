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

// The tan and arctan tables use 32-bit fixed
// point numbers. The sine table uses 17-bit
// fixed point numbers (-65525 to +65535).
//
// These masks are used to experiment with
// lower numbers of significant bits in the
// table values.

// To try less-precise tan and arctan.
// Use 0xFFFFFFFF for full precision.
//
// Based on experimentation, the lowest usable
// tan precision is about 19 bits of TAN_MASK.
//
// Examining the values in finetangent shows
// that its values use only about 29 bits of
// the available 32 bits. This means 19 bits
// of TAN_MASK are equivalent to 16 significant
// bits in each finetangent value, suggesting
// we could use a 16-bit table for finetangent.
//
// The values in tantoangle (arctangent) also
// use only about 29 bits of the available
// 32 bits, suggesting we could use a 16-bit
// table for tantoangle.

//#define TAN_MASK_CJB	0xFFFFE000
#define TAN_MASK_CJB	0xFFFFFFFF

// To try less-precise sin and cos.
// Use 0xFFFFFFFF for full precision but
// the top 15 bits are sign extension.
//
// Based on experimentation, the lowest usable
// sin precision is about 6 bits. For precisions
// of 8 bits and below, a table with 256 entries
// per 2pi is sufficient for low-end performance.

//#define SIN_MASK_CJB	0xFFFFF800
#define SIN_MASK_CJB	0xFFFFFFFF

#define FINEANGLES		8192
#define FINEMASK		(FINEANGLES-1)


// 0x100000000 to 0x2000
#define ANGLETOFINESHIFT	19		

// Effective size is 10240.
extern  fixed_t		finesine[5*FINEANGLES/4];
#define FINESINE(theta) (INT32)(finesine[(theta)] & SIN_MASK_CJB)
//#define FINESINE(theta) finesine[(theta)]

// Re-use data, is just PI/2 pahse shift.
extern  fixed_t*	finecosine;
#define FINECOSINE(theta) (INT32)(finecosine[(theta)] & SIN_MASK_CJB)
//#define FINECOSINE(theta) finecosine[(theta)]


// Effective size is 4096.
extern fixed_t		finetangent[FINEANGLES/2];
#define FINETANGENT(theta) (INT32)(finetangent[(theta)] & TAN_MASK_CJB)
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
#define TANTOANGLE(m) (INT32)(tantoangle[(m)] & TAN_MASK_CJB)
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
