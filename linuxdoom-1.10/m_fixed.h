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
//	Fixed point arithemtics, implementation.
//
//-----------------------------------------------------------------------------


#ifndef __M_FIXED__
#define __M_FIXED__


#ifdef __GNUG__
#pragma interface
#endif


//
// Fixed point, 32bit as 16.16.
// FIXEDTOINT is used on 32bit fixed_t quantities
// HUGETOFIXED is used on 64bit fixed_squared_t
// quantities that result from multiplying two
// fixed_t quantities, to get back to fixed_t
//
#define FRACBITS		16
#define INTTOFIXED(x)		((fixed_t)(x)<<FRACBITS)
#define FIXEDTOINT(x)		((INT32)((x)>>FRACBITS))
#define SQUAREDTOFIXED(x)	((fixed_t)((x)>>FRACBITS))
#define FIXEDTOSQUARED(x)	((fixed_squared_t)(x)<<FRACBITS)
#define FRACUNIT		INTTOFIXED(1)

typedef INT32 fixed_t;
typedef LONGLONG64 fixed_squared_t;

// The min and max values of the data type used to hold fixed_t
#define MINFIXED	0x80000000
#define MAXFIXED	0x7FFFFFFF

// The max value of the data type used to hold fixed_t + 1.0
#define FIXED_T_UNDERLYING_TYPEMAX_AS_DOUBLE	2147483648.0

fixed_t FixedMul	(fixed_t a, fixed_t b);
fixed_t FixedDiv	(fixed_t a, fixed_t b);
fixed_t FixedDiv2	(fixed_t a, fixed_t b);



#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
