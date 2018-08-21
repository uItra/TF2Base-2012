#pragma once

#include "stdafx.h"

namespace _render
{
	extern void drawSetColor( int r, int g, int b, int a );
	extern void drawFilledRect( int x0, int y0, int x1, int y1 );
	extern void drawOutlinedRect( int x0, int y0, int x1, int y1 );
	extern void drawLine( int x0, int y0, int x1, int y1 );
	extern void drawString( DWORD font, int x, int y, int r, int g, int b, int a, const std::string text );
	extern bool worldToScreen( PFLOAT in, PFLOAT out );
	extern void createFont( DWORD& font, PCHAR name, int size, int flags );
};