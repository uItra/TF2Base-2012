#include "stdafx.h"

void interfaces_t::init()
{
	log_t* log = _base::log();

	CreateInterface_t clientFactory = ( CreateInterface_t )( GetProcAddress( _base::client, "CreateInterface" ) );
	log->write( "found clientFactory at [0x%X]", clientFactory );

	CreateInterface_t appSysFactory = **( CreateInterface_t** )( ( DWORD )( _util::findPattern( _base::engine, "\xA1????\x8B\x0D????\x8B\x11\x83\xC4\x04\x68????\x50" ) ) + 0x1 );
	log->write( "found appSystemFactory at [0x%X]", appSysFactory );

	_client = _util::getInterface( &clientFactory, "VClient" );
	log->write( "found IBaseClientDLL at [0x%X]", _client );

	_engine = _util::getInterface( &appSysFactory, "VEngineClient" );
	log->write( "found IVEngineClient at [0x%X]", _engine );

	_entlist = _util::getInterface( &clientFactory, "VClientEntityList" );
	log->write( "found IClientEntityList at [0x%X]", _entlist );

	_panel = _util::getInterface( &appSysFactory, "VGUI_Panel" );
	log->write( "found vgui::IPanel at [0x%X]", _panel );

	_surface = _util::getInterface( &appSysFactory, "VGUI_Surface" );
	log->write( "found vgui::ISurface at [0x%X]", _surface );

	_input = **( void*** )( ( DWORD )( _util::findPattern( _base::client, "\x8B\x0D????\x8B\x01\x8B\x40\x0C\x52" ) ) + 0x2 );
	log->write( "found CInput at [0x%X]", _input );

	_cvar = _util::getInterface( &appSysFactory, "VEngineCvar" );
	log->write( "found ICvar at [0x%X]", _cvar );

	vmt_t* engine = this->engine();
	if( engine->reHook() ) engine->hookMethod( &_hooks::_setViewAngles, 20 );

	log->write( "hooked IVEngineClient" );
	
	vmt_t* panel = this->panel();
	if( panel->reHook() ) panel->hookMethod( &_hooks::_paintTraverse, 40 );
	
	log->write( "hooked vgui::IPanel" );
}

gameResources_t* interfaces_t::getGameResources()
{
	static void* _addr = 0;
	if( !_addr ) _addr = _util::findPattern( _base::client, "\xA1????\x85\xC0\x74\x06\x05????" );

	__asm call _addr
}