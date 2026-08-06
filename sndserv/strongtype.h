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
//	Strong types added by Chris Burke to aid in porting to
//	low-end architectures
//    
//-----------------------------------------------------------------------------


#ifndef __STRONGTYPE__
#define __STRONGTYPE__

// Signed

#ifndef CHAR8
// Default signed vs unsigned of 'char' is compiler dependent
#define CHAR8 signed char
#endif

#ifndef SHORT16
#define SHORT16 short
#endif

#ifndef INT32
#define INT32 int
#endif

#ifndef LONG32
#define LONG32 long
#endif

#ifndef LONGLONG64
#define LONGLONG64 long long
#endif

// Unsigned

#ifndef UCHAR8
#define UCHAR8 unsigned char
#endif

#ifndef USHORT16
#define USHORT16 unsigned short
#endif

#ifndef UINT32
#define UINT32 unsigned int
#endif

#ifndef ULONG32
#define ULONG32 unsigned long
#endif

#ifndef ULONGLONG64
#define ULONGLONG64 unsigned long long
#endif

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
