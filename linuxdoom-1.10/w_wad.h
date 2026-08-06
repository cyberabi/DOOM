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
//	WAD I/O functions.
//
//-----------------------------------------------------------------------------


#ifndef __W_WAD__
#define __W_WAD__


#ifdef __GNUG__
#pragma interface
#endif


//
// TYPES
//
typedef struct
{
    // Should be "IWAD" or "PWAD".
    CHAR8		identification[4];		
    INT32			numlumps;
    INT32			infotableofs;
    
} wadinfo_t;


typedef struct
{
    INT32			filepos;
    INT32			size;
    CHAR8		name[8];
    
} filelump_t;

//
// WADFILE I/O related stuff.
//
typedef struct
{
    CHAR8	name[8];
    INT32		handle;
    INT32		position;
    INT32		size;
} lumpinfo_t;


extern	void**		lumpcache;
extern	lumpinfo_t*	lumpinfo;
extern	INT32		numlumps;

void    W_InitMultipleFiles (CHAR8** filenames);
void    W_Reload (void);

INT32	W_CheckNumForName (CHAR8* name);
INT32	W_GetNumForName (CHAR8* name);

INT32	W_LumpLength (INT32 lump);
void    W_ReadLump (INT32 lump, void *dest);

void*	W_CacheLumpNum (INT32 lump, INT32 tag);
void*	W_CacheLumpName (CHAR8* name, INT32 tag);




#endif
//-----------------------------------------------------------------------------
//
// $Log:$
//
//-----------------------------------------------------------------------------
