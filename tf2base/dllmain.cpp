/*=====================================================================
	tf2 basehook (2012)
=====================================================================*/

#include "stdafx.h"

DWORD WINAPI HookThread( LPVOID args )
{
	log_t* log = _base::log();

	log->init( _base::dir, "tf2base.log" );
	log->write( "initializing" );

	while( FindWindowA( "Valve001", 0 ) ) Sleep( 100 );

	_base::client = _util::getModuleHandle( "client.dll" );
	log->write( "found client.dll at [0x%X]", _base::client );

	_base::engine = _util::getModuleHandle( "engine.dll" );
	log->write( "found engine.dll at [0x%X]", _base::engine );

	_base::vstdlib = _util::getModuleHandle( "vstdlib.dll" );
	log->write( "found vstdlib.dll at [0x%X]", _base::vstdlib );

	_base::global = *( globals_t** )( ( DWORD )( _util::findPattern( _base::engine, "\x68????\x50\x50\x8B\x02\xFF\xD0\x85\xC0" ) ) + 0x1 );
	log->write( "found CGlobalVarsBase at [0x%X]", _base::global );

	_base::interfaces()->init();
	_offsets::fillOffsets();

	log->write( "injected" );

	return 0;
}

BOOL APIENTRY DllMain( HMODULE module, DWORD reason, LPVOID reserved )
{
	if( reason == DLL_PROCESS_ATTACH )
	{
		_base::dir = _util::getDirectory( module );
		CreateThread( 0, 0, HookThread, 0, 0, 0 );
	}
	
	return TRUE;
}
