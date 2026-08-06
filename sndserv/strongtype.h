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

#ifndef CHAR8_DEFINED
typedef char CHAR8;
#define CHAR8_DEFINED
#endif

#ifndef SHORT16_DEFINED
typedef short SHORT16;
#define SHORT16_DEFINED
#endif

#ifndef INT32_DEFINED
typedef int INT32;
#define INT32_DEFINED
#endif

#ifndef LONG32_DEFINED
typedef long LONG32;
#define LONG32_DEFINED
#endif

#ifndef LONGLONG64_DEFINED
typedef long long LONGLONG64;
#define LONGLONG64_DEFINED
#endif

// Unsigned

#ifndef UCHAR8_DEFINED
typedef unsigned char UCHAR8;
#define UCHAR8_DEFINED
#endif

#ifndef USHORT16_DEFINED
typedef unsigned short USHORT16;
#define USHORT16_DEFINED
#endif

#ifndef UINT32_DEFINED
typedef unsigned int UINT32;
#define UINT32_DEFINED
#endif

#ifndef ULONG32_DEFINED
typedef unsigned long ULONG32;
#define ULONG32_DEFINED
#endif

#ifndef ULONGLONG64_DEFINED
typedef unsigned long long ULONGLONG64;
#define ULONGLONG64_DEFINED
#endif

#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
