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

// Use these if the angle has been prescaled to a lookup table index
// Note that the sine, cosine, and tangent tables use different prescalers
#define RTANTHETA_IDX(r,theta_tan_idx) FixedMul(FINETANGENT(theta_tan_idx),r)
#define RCOTANTHETA_IDX(r,theta_tan_idx) FixedDiv(r,FINETANGENT(theta_tan_idx))
#define RSINTHETA_IDX(r,theta_sin_idx) FixedMul(FINESINE(theta_sin_idx),r)
#define RCOSTHETA_IDX(r,theta_cos_idx) FixedMul(FINECOSINE(theta_cos_idx),r)

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
