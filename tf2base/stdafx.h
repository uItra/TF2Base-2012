#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include "Psapi.h"
#include "client_class.h"

#pragma comment( lib, "user32.lib" )
#pragma comment( lib, "psapi.lib" )

#define PI 3.14159265358979323846f
#define DEG2RAD( x ) ( ( float )( x ) * ( float )( ( float )( PI ) / 180.0f ) )
#define RAD2DEG( x ) ( ( float )( x ) * ( float )( 180.0f / ( float )( PI ) ) )
#define square( x ) ( x * x )

#include "convar.h"
#include "weaponlist.h"

typedef void* ( __cdecl* CreateInterface_t )( const char*, int* );
typedef void ( __thiscall* SetViewAngles_t )( void*, PFLOAT );
typedef void ( __thiscall* PaintTraverse_t )( void*, size_t, bool, bool );
typedef void* ( __thiscall* GetClientEntity_t )( void*, int );
typedef int ( __thiscall* GetLocalPlayer_t )( void* );
typedef const char* ( __thiscall* GetName_t )( void*, size_t );
typedef void ( __thiscall* DrawSetColor_t )( void*, int, int, int, int );
typedef void ( __thiscall* DrawFilledRect_t )( void*, int, int, int, int );
typedef void ( __thiscall* DrawOutlinedRect_t )( void*, int, int, int, int );
typedef void ( __thiscall* DrawLine_t )( void*, int, int, int, int );
typedef void ( __thiscall* DrawSetTextFont_t )( void*, DWORD );
typedef void ( __thiscall* DrawSetTextPos_t )( void*, int, int );
typedef void ( __thiscall* DrawSetTextColor_t )( void*, int, int, int, int );
typedef void ( __thiscall* DrawPrintText_t )( void*, const wchar_t*, int, int );
typedef void ( __thiscall* GetScreenSize_t )( void*, int&, int& );
typedef DWORD ( __thiscall* CreateFont_t )( void* );
typedef bool ( __thiscall* SetFontGlyphSet_t )( void*, DWORD, const char*, int, int, int, int, int, int, int );
typedef bool ( __thiscall* IsInGame_t )( void* );
typedef bool ( __thiscall* IsConnected_t )( void* );
typedef void ( __cdecl* RandomSeed_t )( int );
typedef float ( __cdecl* RandomFloat_t )( float, float );
typedef conVar_t* ( __thiscall* FindVar_t )( void*, const char* );
typedef ClientClass* ( __thiscall* GetAllClasses_t )( void* );

typedef float matrix_t[3][4];

struct color32_t
{
	BYTE r, g, b, a;
};

#include "cmd.h"
#include "globals.h"
#include "gameresources.h"
#include "offsets.h"
#include "weapon.h"
#include "entity.h"
#include "trace.h"
#include "util.h"
#include "vmt.h"
#include "interfaces.h"
#include "log.h"
#include "memory.h"
#include "hooks.h"
#include "render.h"

namespace _base
{
	extern std::string dir;
	extern HMODULE client;
	extern HMODULE engine;
	extern HMODULE vstdlib;
	extern globals_t* global;
	extern DWORD espfont;

	__forceinline log_t* log()
	{
		static log_t log;
		return &log;
	}
	__forceinline interfaces_t* interfaces()
	{
		static interfaces_t interfaces;
		return &interfaces;
	}
};