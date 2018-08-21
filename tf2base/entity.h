#pragma once

#include "stdafx.h"

enum tfcond_t
{
	TFCOND_SCOPED = ( 1 << 1 ),
	TFCOND_DISGUISED = ( 1 << 3 ),
	TFCOND_CLOAKED = ( 1 << 4 ),
	TFCOND_UBERED = ( 1 << 5 ),
	TFCOND_TAUNTING = ( 1 << 7 ),
	TFCOND_FEIGNDEATH = ( 1 << 13 ),
	TFCOND_BONKED = ( 1 << 14 ),
	TFCOND_STUNNED = ( 1 << 15 ),
	TFCOND_CHARGING = ( 1 << 17 ),
};

enum tfclass_t
{
	CLASS_NONE,
	CLASS_SCOUT,
	CLASS_SNIPER,
	CLASS_SOLDIER,
	CLASS_DEMOMAN,
	CLASS_MEDIC,
	CLASS_HEAVY,
	CLASS_PYRO,
	CLASS_SPY,
	CLASS_ENGINEER,
};

enum moveflag_t
{
	FL_ONGROUND = ( 1 << 0 ),
	FL_DUCKING = ( 1 << 1 ),
	FL_WATERJUMP = ( 1 << 3 ),
	FL_ONTRAIN = ( 1 << 4 ),
	FL_INRAIN = ( 1 << 5 ),
	FL_FROZEN = ( 1 << 6 ),
	FL_ATCONTROLS = ( 1 << 7 ),
	FL_CLIENT = ( 1 << 8 ),
	FL_FAKECLIENT = ( 1 << 9 ),
	FL_INWATER = ( 1 << 10 ),
};

class entity_t
{
public:
	bool getBonePosition( int bone, PFLOAT pos );

	__forceinline bool isAlive()
	{
		return ( *( PBYTE )( ( DWORD )( this ) + _offsets::entity::m_lifeState ) == 0 );
	}
	__forceinline int getHealth()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::entity::m_iHealth );
	}
	__forceinline int getClass()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::entity::m_PlayerClass + _offsets::entity::m_iClass );
	}
	__forceinline int getFlags()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::entity::m_fFlags );
	}
	__forceinline bool isOnGround()
	{
		return ( this->getFlags() & FL_ONGROUND );
	}
	__forceinline float getSimulationTime()
	{
		return *( PFLOAT )( ( DWORD )( this ) + _offsets::entity::m_flSimulationTime );
	}
	__forceinline PINT getCond()
	{
		return ( PINT )( ( DWORD )( this ) + _offsets::entity::m_Shared + _offsets::entity::m_nPlayerCond );
	}
	__forceinline bool isPlayer()
	{
		return ( !strcmp( this->getClientClass()->GetName(), "CTFPlayer" ) );
	}
	__forceinline int getTeam()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::entity::m_iTeamNum );
	}

	PFLOAT getAbsOrigin()
	{
		__asm
		{
			mov ecx, this
			mov eax, dword ptr ds:[ecx]
			call dword ptr ds:[eax + 0x24]
		}
	}
	ClientClass* getClientClass()
	{
		__asm
		{
			mov edi, this
			lea ecx, [edi + 0x8]
			mov edx, dword ptr ds:[ecx]
			call [edx + 0x8]
		}
	}
	bool isDormant()
	{
		__asm
		{
			mov edi, this
			lea ecx, [edi + 0x8]
			mov edx, dword ptr ds:[ecx]
			call [edx + 0x20]
		}
	}
	bool getIndex()
	{
		__asm
		{
			mov edi, this
			lea ecx, [edi + 0x8]
			mov edx, dword ptr ds:[ecx]
			call [edx + 0x24]
		}
	}
	const void* getModel()
	{
		__asm
		{
			mov edi, this
			lea ecx, [edi + 0x4]
			mov edx, dword ptr ds:[ecx]
			call [edx + 0x24]
		}
	}
	bool setupBones( matrix_t* matrix, int maxbones, int mask, float time )
	{
		__asm
		{
			mov edi, this
			lea ecx, [edi + 0x4]
			mov edx, dword ptr ds:[ecx]
			push time
			push mask
			push maxbones
			push matrix
			call [edx + 0x40]
		}
	}
	weapon_t* getActiveWeapon()
	{
		__asm
		{
			mov edx, _offsets::entity::getActiveWeapon
			mov ecx, this
			mov eax, dword ptr ds:[ecx]
			call dword ptr ds:[eax + edx]
		}
	}
	std::string getTFClassName()
	{
		switch( this->getClass() )
		{
		case CLASS_SCOUT: return "scout";
		case CLASS_SNIPER: return "sniper";
		case CLASS_SOLDIER: return "soldier";
		case CLASS_DEMOMAN: return "demoman";
		case CLASS_MEDIC: return "medic";
		case CLASS_HEAVY: return "heavy";
		case CLASS_PYRO: return "pyro";
		case CLASS_SPY: return "spy";
		case CLASS_ENGINEER: return "engineer";
		default: return "n/a";
		}
	}
	void getTeamColor( color32_t* color )
	{
		switch( this->getTeam() )
		{
		case 2:
			{
				color->r = 255;
				color->g = 71;
				color->b = 71;
				color->a = 255;
				return;
			}
		case 3:
			{
				color->r = 156;
				color->g = 192;
				color->b = 255;
				color->a = 255;
				return;
			}
		default:
			{
				color->r = 255;
				color->g = 255;
				color->b = 255;
				color->a = 255;
				return;
			}
		}
	}

	static entity_t* get( int index );
};

class localPlayer_t : public entity_t
{
public:
	__forceinline int getTickBase()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::entity::m_nTickBase );
	}

	bool pathFree( PFLOAT dest, entity_t* target = NULL );
	void getSpreadVector( int seed, PFLOAT angles, PFLOAT dir, weapon_t* weapon );
	void removeSpread( cmd_t* cmd, weapon_t* weapon );
	bool waitForCrit( cmd_t* cmd, weapon_t* weapon );

	static localPlayer_t* get();

	void getEyePos( PFLOAT out )
	{
		PFLOAT origin = this->getAbsOrigin();
		PFLOAT offset = ( PFLOAT )( ( DWORD )( this ) + _offsets::entity::m_vecViewOffset0 );

		out[0] = origin[0] + offset[0];
		out[1] = origin[1] + offset[1];
		out[2] = origin[2] + offset[2];
	}
};