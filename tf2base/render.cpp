#include "stdafx.h"

namespace _render
{
	void drawSetColor( int r, int g, int b, int a )
	{		
		vmt_t* surface = _base::interfaces()->surface();
		surface->getMethod< DrawSetColor_t >( 11 )( surface->getInst(), r, g, b, a );
	}
	void drawFilledRect( int x0, int y0, int x1, int y1 )
	{
		vmt_t* surface = _base::interfaces()->surface();
		surface->getMethod< DrawFilledRect_t >( 12 )( surface->getInst(), x0, y0, x1, y1 );
	}
	void drawOutlinedRect( int x0, int y0, int x1, int y1 )
	{
		vmt_t* surface = _base::interfaces()->surface();
		surface->getMethod< DrawOutlinedRect_t >( 14 )( surface->getInst(), x0, y0, x1, y1 );
	}
	void drawLine( int x0, int y0, int x1, int y1 )
	{
		vmt_t* surface = _base::interfaces()->surface();
		surface->getMethod< DrawLine_t >( 15 )( surface->getInst(), x0, y0, x1, y1 );
	}
	void drawString( DWORD font, int x, int y, int r, int g, int b, int a, const std::string text )
	{
		std::wstring wide = _util::stringToWide( text );

		vmt_t* surface = _base::interfaces()->surface();
		void* inst = surface->getInst();

		surface->getMethod< DrawSetTextFont_t >( 17 )( inst, font );
		surface->getMethod< DrawSetTextColor_t >( 19 )( inst, r, g, b, a );
		surface->getMethod< DrawSetTextPos_t >( 20 )( inst, x, y );
		surface->getMethod< DrawPrintText_t >( 22 )( inst, wide.c_str(), wide.length(), 0 );
	}
	bool worldToScreen( PFLOAT in, PFLOAT out )
	{
		static void* _addr = 0;
		if( !_addr ) _addr = _util::findPattern( _base::client, "\x8B\x0D????\x8B\x01\x8B\x90????\xFF\xD2\x8B\x4C\x24\x04" );

		int transform = 1;

		__asm
		{
			push out
			push in
			call _addr
			add esp, 0x8
			mov transform, eax
		}

		if( transform != 0 ) return false;
		
		screenSize_t size;
		_util::getScreenSize( &size );

		out[0] = ( size.w * 0.5f ) + ( 0.5f * out[0] * size.w + 0.5f );	
		out[1] = ( size.h * 0.5f ) - ( 0.5f * out[1] * size.h + 0.5f );

		return true;
	}
	void createFont( DWORD& font, PCHAR name, int size, int flags )
	{
		vmt_t* surface = _base::interfaces()->surface();
		void* inst = surface->getInst();

		font = surface->getMethod< CreateFont_t >( 64 )( inst );
		surface->getMethod< SetFontGlyphSet_t >( 65 )( inst, font, name, size, 0, 0, 0, flags, 0, 0 );
	}
};