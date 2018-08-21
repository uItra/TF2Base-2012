#pragma once

#include "stdafx.h"

class gameResources_t
{
public:
	virtual	~gameResources_t() {};
	virtual const char* getTeamName( int index ) = 0;
	virtual int getTeamScore( int index ) = 0;
	virtual color32_t& getTeamColor( int index ) = 0;
	virtual bool isConnected( int index ) = 0;
	virtual bool isAlive( int index ) = 0;
	virtual bool isFakePlayer( int index ) = 0;
	virtual bool isLocalPlayer( int index ) = 0;
	virtual const char* getPlayerName( int index ) = 0;
	virtual int getPlayerScore( int index ) = 0;
	virtual int getPing( int index ) = 0;
	virtual int getDeaths( int index ) = 0;
	virtual int getFrags( int index ) = 0;
	virtual int getTeam( int index ) = 0;
	virtual int getHealth( int index ) = 0;
};