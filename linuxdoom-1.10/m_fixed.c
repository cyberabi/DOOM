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
//	Fixed point implementation.
//
//-----------------------------------------------------------------------------


static const char
rcsid[] = "$Id: m_bbox.c,v 1.1 1997/02/03 22:45:10 b1 Exp $";

#include "stdlib.h"

#include "doomtype.h"
#include "i_system.h"

#ifdef __GNUG__
#pragma implementation "m_fixed.h"
#endif
#include "m_fixed.h"




// Fixme. __USE_C_FIXED__ or something.

fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )
{
    // Fixme. Adjust for the next larger data type from fixed_t
    return SQUAREDTOFIXED((fixed_squared_t) a * (fixed_squared_t) b);
}



//
// FixedDiv, C version.
//

fixed_t
FixedDiv
( fixed_t	a,
  fixed_t	b )
{
    // Fixme. Adjust for FRACBITS and datatype size
    // MININT and MAXINT (doomtype.h) are based on INT32
    if ( (abs(a)>>(FRACBITS-2)) >= abs(b))
	return (a^b)<0 ? MINFIXED : MAXFIXED;
    return FixedDiv2 (a,b);
}



fixed_t
FixedDiv2
( fixed_t	a,
  fixed_t	b )
{
    // Fixme. Consider using using fast 1/x and multiplication.
    // for platforms with no hardware floating point.
#if 1
    fixed_squared_t c;
    c = FIXEDTOSQUARED(a) / ((fixed_squared_t)b);
    return (fixed_t) c;
#else
    double c;

    c = ((double)a) / ((double)b) * FRACUNIT;

    if (c >= FIXED_T_UNDERLYING_TYPEMAX_AS_DOUBLE ||
	c < -FIXED_T_UNDERLYING_TYPEMAX_AS_DOUBLE)
	I_Error("FixedDiv: divide by zero");
    return (fixed_t) c;
#endif
}
