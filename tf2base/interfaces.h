#pragma once

#include "stdafx.h"

class interfaces_t
{
private:
	void* _client;
	void* _engine;
	void* _entlist;
	void* _panel;
	void* _surface;
	void* _input;
	void* _cvar;
public:
	void init();
	
	static gameResources_t* getGameResources();

	__forceinline vmt_t* client()
	{
		static vmt_t client( _client );
		return &client;
	}
	__forceinline vmt_t* engine()
	{
		static vmt_t engine( _engine );
		return &engine;
	}
	__forceinline vmt_t* entlist()
	{
		static vmt_t entlist( _entlist );
		return &entlist;
	}
	__forceinline vmt_t* panel()
	{
		static vmt_t panel( _panel );
		return &panel;
	}
	__forceinline vmt_t* surface()
	{
		static vmt_t surface( _surface );
		return &surface;
	}
	__forceinline vmt_t* input()
	{
		static vmt_t input( _input );
		return &input;
	}
	__forceinline vmt_t* cvar()
	{
		static vmt_t cvar( _cvar );
		return &cvar;
	}
};
