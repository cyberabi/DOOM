// Emacs style mode select   -*- C++ -*- 
//-----------------------------------------------------------------------------
//
// $Id:$
//
// Copyright (C) 1993-1996, 2026 by id Software, Inc.
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
//	The trig functions in DOOM are used in specific idioms such
//	as r cos theta or a dot product. This header encapsulates
//	those idioms in macros, potentially allowing faster or more
//	compact implementation on low-end platforms while preserving
//	the fidelity of the original.
//    
//-----------------------------------------------------------------------------


#ifndef __FASTTRIG__
#define __FASTTRIG__

// Operations that produce a fixed-point result from fixed-point operands

// Use these if the angle has been prescaled to a lookup table index.
// Initial implementations are naive, pending future optimization.
// NOTE: Discouraging use of these as they expose the sizes of trig tables.
// NOTE: sine, cosine, and tangent tables might use different prescalers.

#define RTANTHETA_IDX(r, theta_tan_idx)		FixedMul(FIXEDTAN_IDX(theta_tan_idx), (r))
#define RCOTANTHETA_IDX(r, theta_tan_idx)	FixedDiv((r), FIXEDTAN_IDX(theta_tan_idx))
#define RSINTHETA_IDX(r, theta_sin_idx)		FixedMul(FIXEDSIN_IDX(theta_sin_idx), (r))
#define RCOSTHETA_IDX(r, theta_cos_idx)		FixedMul(FIXEDCOS_IDX(theta_cos_idx), (r))

#define XYFROMRTHETA_IDX(x_dest, y_dest, r, theta_sin_idx) \
	x_dest = RCOSTHETA_IDX((r), (theta_sin_idx)); \
	y_dest = RSINTHETA_IDX((r), (theta_sin_idx));

#define SINCOSFROMTHETA_IDX(s_dest, c_dest, theta_sin_idx) \
	s_dest = FIXEDSIN_IDX(theta_sin_idx); \
	c_dest = FIXEDCOS_IDX(theta_sin_idx);

// Use these if the angle etc. is a fixed point number.
// Initial implementations are naive, pending future optimization.

#define XYFROMRTHETA(x_dest, y_dest, r, theta) \
	{ angle_t theta_sin_idx = (theta) >> ANGLETOIDXSHIFT; \
	  x_dest = RCOSTHETA_IDX((r), (theta_sin_idx)); \
	  y_dest = RSINTHETA_IDX((r), (theta_sin_idx)); }

#define SLOPETOANGLE(num, den)	(TANTOANGLE(SlopeDiv((num),(den))))

// Specialized macros for recurring actions on specific data structures

#define INITMOMXY(mob)	XYFROMRTHETA(mob->momx, mob->momy, (mob)->info->speed, (mob)->angle)

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
