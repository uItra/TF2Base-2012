#include "stdafx.h"

namespace _util
{
	conVar_t* findVar( PCHAR name )
	{
		vmt_t* cvar = _base::interfaces()->cvar();
		return cvar->getMethod< FindVar_t >( 12 )( cvar->getInst(), name );
	}
	void UTIL_TraceLine( PFLOAT start, PFLOAT end, size_t mask, entity_t* ignore, int collision, trace_t* tr )
	{
		static void* _addr = 0;
		if( !_addr ) _addr = findPattern( _base::client, "\x55\x8B\xEC\x83\xE4\xF0\x83\xEC\x6C\x56\x8B\x45\x08" );

		__asm
		{
			push tr
			push collision
			push ignore
			push mask
			push end
			push start
			call _addr
			add esp, 0x18
		}
	}
	float getCurtime( localPlayer_t* local )
	{
		if( !local ) return _base::global->curTime;
		
		return ( ( float )( local->getTickBase() + 1 ) * _base::global->intervalPerTick );
	}
	bool isInGame()
	{
		vmt_t* engine = _base::interfaces()->engine();
		return engine->getMethod< IsInGame_t >( 26 )( engine->getInst() );
	}
	bool isConnected()
	{
		vmt_t* engine = _base::interfaces()->engine();
		return engine->getMethod< IsConnected_t >( 27 )( engine->getInst() );
	}
	void getScreenSize( screenSize_t* size )
	{
		vmt_t* engine = _base::interfaces()->engine();
		engine->getMethod< GetScreenSize_t >( 5 )( engine->getInst(), size->w, size->h );
	}
	int getLocalPlayer()
	{
		vmt_t* engine = _base::interfaces()->engine();
		return engine->getMethod< GetLocalPlayer_t >( 12 )( engine->getInst() );
	}
	std::string getDirectory( HMODULE module )
	{
		char path[255], drive[255], dir[255];
	
		GetModuleFileNameA( module, path, 260 );
		_splitpath( path, drive, dir, 0, 0 );

		return formatString( "%s%s", drive, dir );
	}
	std::wstring stringToWide( const std::string& text )
	{
		std::wstring wide( text.length(), L' ' );
		std::copy( text.begin(), text.end(), wide.begin() );

		return wide;
	}
	std::string formatString( PCHAR fmt, ... )
	{
		char buf[1024];
		memset( buf, 0, 1024 );

		va_list va_alist;
		va_start( va_alist, fmt );
		_vsnprintf( buf + strlen( buf ), sizeof( buf ) - strlen( buf ), fmt, va_alist );
		va_end( va_alist );

		return buf;
	}
	HMODULE getModuleHandle( PCHAR name )
	{
		HMODULE module = 0;

		do
		{
			module = GetModuleHandleA( name );
			Sleep( 200 );
		}
		while( !module );

		return module;
	}
	void* getInterface( CreateInterface_t* fn, PCHAR name )
	{
		void* ptr = 0;

		for( int i = 0; i < 100; ++i )
		{
			PCHAR fmt = ( i < 10 ) ? "%s00%d" : "%s0%d"; // i hope they dont go over 99
			
			ptr = ( *fn )( formatString( fmt, name, i ).c_str(), 0 );
			if( ptr ) break;
		}

		return ptr;
	}
	bool checkAddress( PCHAR address, PCHAR sig )
	{
		int len = ( int )( strlen( sig ) );

		for( int i = 0; i < len; i++ )
		{
			if( sig[i] == '?' ) 
			{
				address++; // ignore wildcards, compare the next byte in the code section
				continue;
			}
		
			if( *address != sig[i] ) return false; // byte comparison failed
			
			address++; // bytes match, compare next
		}

		return true;
	}
	void* findPattern( HMODULE module, PCHAR sig )
	{
		MODULEINFO info;
		if( !GetModuleInformation( GetCurrentProcess(), module, &info, sizeof( info ) ) ) return 0;

		PCHAR base = ( PCHAR )( module );

		for( PCHAR address = base; address <= ( base + info.SizeOfImage ); ++address )
		{
			if( checkAddress( address, sig ) )
				return address;
		}
		
		return 0;
	}
	size_t MD5_PseudoRandom( size_t seed )
	{
		static void* _addr = 0;
		if( !_addr ) _addr = findPattern( _base::client, "\x83\xEC\x68\x6A\x58\x8D\x44\x24\x14\x6A\x00\x50\xE8????" );

		__asm
		{
			push seed
			call _addr
			add esp, 0x4
		}
	}
	float sseSqrt( float x )
	{
		float root = 0.0f;

		__asm
		{
			sqrtss xmm0, x
			movss root, xmm0
		}

		return root;
	}
	float sseRsqrt( float x )
	{
		float rroot = 0.0f;

		__asm
		{
			rsqrtss	xmm0, x
			movss rroot, xmm0
		}

		return ( ( 0.5f * rroot ) * ( 3.0f - ( x * rroot ) * rroot ) );
	}
	void sinCos( float radians, PFLOAT sine, PFLOAT cosine )
	{
		__asm
		{
			fld dword ptr [radians]
			fsincos
			mov edx, dword ptr [cosine]
			mov eax, dword ptr [sine]
			fstp dword ptr [edx]
			fstp dword ptr [eax]
		}
	}
	void vectorAngles( PFLOAT forward, PFLOAT angles )
	{	
		if( forward[1] == 0.0f && forward[0] == 0.0f )
		{
			angles[0] = ( forward[2] > 0.0f ) ? 270.0f : 90.0f;
			angles[1] = 0.0f;
		}
		else
		{
			float len2d = sseSqrt( square( forward[0] ) + square( forward[1] ) );

			angles[0] = RAD2DEG( atan2f( -forward[2], len2d ) );
			angles[1] = RAD2DEG( atan2f( forward[1], forward[0] ) );

			if( angles[0] < 0.0f ) angles[0] += 360.0f;
			if( angles[1] < 0.0f ) angles[1] += 360.0f;
		}

		angles[2] = 0.0f;
	}
	void angleVectors( PFLOAT angles, PFLOAT forward )
	{
		float sp, sy, cp, cy;

		sinCos( DEG2RAD( angles[0] ), &sp, &cp );
		sinCos( DEG2RAD( angles[1] ), &sy, &cy );

		forward[0] = cp * cy;
		forward[1] = cp * sy;
		forward[2] = -sp;
	}
	void angleVectors( PFLOAT angles, PFLOAT f, PFLOAT r, PFLOAT u )
	{
		float sp, sy, sr, cp, cy, cr;

		sinCos( DEG2RAD( angles[0] ), &sp, &cp );
		sinCos( DEG2RAD( angles[1] ), &sy, &cy );
		sinCos( DEG2RAD( angles[2] ), &sr, &cr );

		f[0] = cp * cy;
		f[1] = cp * sy;
		f[2] = -sp;

		r[0] = -1.0f * sr * sp * cy + -1.0f * cr * -sy;
		r[1] = -1.0f * sr * sp * sy + -1.0f * cr * cy;
		r[2] = -1.0f * sr * cp;

		u[0] = cr * sp * cy + -sr * -sy;
		u[1] = cr * sp * sy + -sr * cy;
		u[2] = cr * cp;
	}
	float vectorDistance( PFLOAT start, PFLOAT end )
	{
		float dir[3];

		dir[0] = end[0] - start[0];
		dir[1] = end[1] - start[1];
		dir[2] = end[2] - start[2];

		return sseSqrt( square( dir[0] ) + square( dir[1] ) + square( dir[2] ) );
	}
	float vectorNormalize( PFLOAT forward )
	{
		float lensqr = square( forward[0] ) + square( forward[1] ) + square( forward[2] );
		float rsqrt = sseRsqrt( lensqr + FLT_EPSILON );

		forward[0] *= rsqrt;
		forward[1] *= rsqrt;
		forward[2] *= rsqrt;

		return sseSqrt( lensqr );
	}
	int getOffsetFromTable( PCHAR className, PCHAR varName, RecvTable* table )
	{
		int offset = 0;

		for( int i = 0; i < table->GetNumProps(); i++ )
		{
			RecvProp* prop = table->GetPropW( i );
			if( !prop ) continue;

			RecvTable* child = prop->GetDataTable();
			if( child && child->GetNumProps() ) offset += getOffsetFromTable( className, varName, child );

			if( !strcmp( table->GetName(), className ) && !strcmp( prop->GetName(), varName ) )
			{
				offset += prop->GetOffset();
				break;
			}
		}

		return offset;
	}
	int getNetVarOffset( PCHAR className, PCHAR varName )
	{
		vmt_t* client = _base::interfaces()->client();
		ClientClass* clientClass = client->getMethod< GetAllClasses_t >( 8 )( client->getInst() );

		int offset = 0;

		for( ; clientClass; clientClass = clientClass->m_pNext )
		{
			RecvTable* table = clientClass->m_pRecvTable;

			if( !table ) continue;
			if( table->GetNumProps() <= 0 ) continue;
			if( !strstr( table->GetName(), "DT_" ) ) continue;

			offset = getOffsetFromTable( className, varName, table );
			if( offset != 0 ) break;
		}

		_base::log()->write( "found %s->%s offset at [0x%X]", className, varName, offset );
		
		return offset;
	}
};