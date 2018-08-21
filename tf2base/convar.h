#pragma once

#include "stdafx.h"

class conVar_t
{
public:
	__forceinline PCHAR getName()
	{
		return ( PCHAR )( *( PDWORD )( ( DWORD )( this ) + 0x1C ) + 0xC );
	}
	__forceinline PINT getFlags()
	{
		return ( PINT )( *( PDWORD )( ( DWORD )( this ) + 0x1C ) + 0x14 );
	}
	__forceinline PCHAR getString()
	{
		return ( PCHAR )( ( DWORD )( this ) + 0x24 );
	}
	__forceinline PFLOAT getFloat()
	{
		return ( PFLOAT )( ( DWORD )( this ) + 0x2C );
	}
	__forceinline PINT getInt()
	{
		return ( PINT )( ( DWORD )( this ) + 0x30 );
	}
};
