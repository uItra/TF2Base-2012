#pragma once

#include "stdafx.h"

struct screenSize_t
{
	int w, h;
};

namespace _util
{
	__forceinline void* getCallAddress( DWORD call )
	{
		return ( void* )( *( PDWORD )( call + 0x1 ) + call + 0x5 );
	}
	__forceinline tm* getLocalTime()
	{
		time_t rawTime;
		time( &rawTime );

		return localtime( &rawTime );
	}
	__forceinline void clampAngle( PFLOAT angles )
	{
		if( angles[0] > 180.0f )  angles[0] -= 360.0f;
		if( angles[0] < -180.0f ) angles[0] += 360.0f;
		if( angles[1] > 180.0f )  angles[1] -= 360.0f;
		if( angles[1] < -180.0f ) angles[1] += 360.0f;
	}

	extern conVar_t* findVar( PCHAR name );
	extern void UTIL_TraceLine( PFLOAT start, PFLOAT end, size_t mask, entity_t* ignore, int collision, trace_t* tr );
	extern float getCurtime( localPlayer_t* local );
	extern bool isInGame();
	extern bool isConnected();
	extern void getScreenSize( screenSize_t* size );
	extern int getLocalPlayer();
	extern std::string getDirectory( HMODULE module );
	extern std::wstring stringToWide( const std::string& text );
	extern std::string formatString( PCHAR fmt, ... );	
	extern HMODULE getModuleHandle( PCHAR name );
	extern void* getInterface( CreateInterface_t* fn, PCHAR name );
	extern bool checkAddress( PCHAR address, PCHAR sig );
	extern void* findPattern( HMODULE module, PCHAR sig );
	extern size_t MD5_PseudoRandom( size_t seed );
	extern float sseSqrt( float x );
	extern float sseRsqrt( float x );
	extern void vectorAngles( PFLOAT forward, PFLOAT angles );
	extern void angleVectors( PFLOAT angles, PFLOAT forward );
	extern void angleVectors( PFLOAT angles, PFLOAT forward, PFLOAT right, PFLOAT up );
	extern float vectorDistance( PFLOAT start, PFLOAT end );
	extern float vectorNormalize( PFLOAT forward );
	extern int getOffsetFromTable( PCHAR className, PCHAR varName, RecvTable* table );
	extern int getNetVarOffset( PCHAR className, PCHAR varName );
};