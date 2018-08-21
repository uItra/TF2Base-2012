#pragma once

#include "stdafx.h"

namespace _offsets
{
	namespace entity
	{
		extern int m_lifeState;
		extern int m_iHealth;
		extern int m_PlayerClass;
		extern int m_iClass;
		extern int m_fFlags;
		extern int m_flSimulationTime;
		extern int m_Shared;
		extern int m_nPlayerCond;
		extern int m_iTeamNum;
		extern int m_nTickBase;
		extern int m_vecViewOffset0;
		extern DWORD getActiveWeapon;
	};
	namespace weapon
	{
		extern int m_flNextPrimaryAttack;
		extern int m_bReadyToBackstab;
		extern int m_iPrimaryAmmoType;
		extern int m_iClip1;
		extern int m_flLastFireTime;
		extern DWORD weaponSeed;
		extern DWORD isShotCritical;
		extern DWORD getSpread;
		extern DWORD getWeaponID;
	};

	extern void fillOffsets();
};
