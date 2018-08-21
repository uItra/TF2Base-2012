#include "stdafx.h"

namespace _offsets
{
	namespace entity
	{
		int m_lifeState = 0;
		int m_iHealth = 0;
		int m_PlayerClass = 0;
		int m_iClass = 0;
		int m_fFlags = 0;
		int m_flSimulationTime = 0;
		int m_Shared = 0;
		int m_nPlayerCond = 0;
		int m_iTeamNum = 0;
		int m_nTickBase = 0;
		int m_vecViewOffset0 = 0;
		DWORD getActiveWeapon = 0;
	};
	namespace weapon
	{
		int m_flNextPrimaryAttack = 0;
		int m_bReadyToBackstab = 0;
		int m_iPrimaryAmmoType = 0;
		int m_iClip1 = 0;
		int m_flLastFireTime = 0;
		DWORD weaponSeed = 0;
		DWORD isShotCritical = 0;
		DWORD getSpread = 0;
		DWORD getWeaponID = 0;
	};

	void fillOffsets()
	{
		entity::m_lifeState				= _util::getNetVarOffset( "DT_BasePlayer", "m_lifeState" );
		entity::m_iHealth				= _util::getNetVarOffset( "DT_BasePlayer", "m_iHealth" );
		entity::m_fFlags				= _util::getNetVarOffset( "DT_BasePlayer", "m_fFlags" );
		entity::m_flSimulationTime		= _util::getNetVarOffset( "DT_BaseEntity", "m_flSimulationTime" );
		entity::m_Shared				= _util::getNetVarOffset( "DT_TFPlayer", "m_Shared" );
		entity::m_PlayerClass			= _util::getNetVarOffset( "DT_TFPlayer", "m_PlayerClass" );
		entity::m_nPlayerCond			= _util::getNetVarOffset( "DT_TFPlayerShared", "m_nPlayerCond" );
		entity::m_iClass				= _util::getNetVarOffset( "DT_TFPlayerClassShared", "m_iClass" );
		entity::m_iTeamNum				= _util::getNetVarOffset( "DT_BaseEntity", "m_iTeamNum" );
		entity::m_nTickBase				= _util::getNetVarOffset( "DT_LocalPlayerExclusive", "m_nTickBase" );
		entity::m_vecViewOffset0		= _util::getNetVarOffset( "DT_LocalPlayerExclusive", "m_vecViewOffset[0]" );

		weapon::m_bReadyToBackstab		= _util::getNetVarOffset( "DT_TFWeaponKnife", "m_bReadyToBackstab" );
		weapon::m_flLastFireTime		= _util::getNetVarOffset( "DT_LocalTFWeaponData", "m_flLastFireTime" );
		weapon::m_flNextPrimaryAttack	= _util::getNetVarOffset( "DT_LocalActiveWeaponData", "m_flNextPrimaryAttack" );
		weapon::m_iClip1				= _util::getNetVarOffset( "DT_LocalWeaponData", "m_iClip1" );
		weapon::m_iPrimaryAmmoType		= _util::getNetVarOffset( "DT_LocalWeaponData", "m_iPrimaryAmmoType" );

		log_t* log = _base::log();

		entity::getActiveWeapon = *( PDWORD )( ( DWORD )( _util::findPattern( _base::client, "\x8B\x90????\x53\x56\x57\x8B\xCD\x83\xCE\xFF" ) ) + 0x2 );
		log->write( "found GetActiveWeapon offset at [0x%X]", entity::getActiveWeapon );

		weapon::getWeaponID = *( PDWORD )( ( DWORD )( _util::findPattern( _base::client, "\x8B\x82????\x51\x8B\x8E????\xD9\x1C\x24\x81\xE3????\x53" ) ) + 0x2 );
		log->write( "found GetWeaponID offset at [0x%X]", weapon::getWeaponID );

		weapon::getSpread = *( PDWORD )( ( DWORD )( _util::findPattern( _base::client, "\x8B\x82????\x51\x8B\xCE\xD9\x1C\x24\xFF\xD0\x8B\x16\x8B\x82????\x51\x8B\x8E????" ) ) + 0x2 );
		log->write( "found GetSpread offset at [0x%X]", weapon::getSpread );

		weapon::isShotCritical = *( PDWORD )( ( DWORD )( _util::findPattern( _base::client, "\x8B\x82????\x8B\xCE\xFF\xD0\x88\x86\xDA\x09\x00\x00" ) ) + 0x2 );
		log->write( "found IsShotCritical offset at [0x%X]", weapon::isShotCritical );

		weapon::weaponSeed	= *( PDWORD )( ( DWORD )( _util::findPattern( _base::client, "\x3B\x8E????\x74\x10\x51\x89\x8E????\xFF\x15????\x83\xC4\x04\x83\xBB?????\x75\x07" ) ) + 0x2 );
		log->write( "found weaponSeed offset at [0x%X]", weapon::weaponSeed );
	}
};
