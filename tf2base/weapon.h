#pragma once

#include "stdafx.h"

class weapon_t
{
public:
	__forceinline float getNextPrimaryAttack()
	{
		return *( PFLOAT )( ( DWORD )( this ) + _offsets::weapon::m_flNextPrimaryAttack );
	}
	__forceinline bool readyToBackstab()
	{
		return *( bool* )( ( DWORD )( this ) + _offsets::weapon::m_bReadyToBackstab );
	}
	__forceinline int getPrimaryAmmoType()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::weapon::m_iPrimaryAmmoType );
	}
	__forceinline int getClipCount()
	{
		return *( PINT )( ( DWORD )( this ) + _offsets::weapon::m_iClip1 );
	}
	__forceinline float getLastFireTime()
	{
		return *( PFLOAT )( ( DWORD )( this ) + _offsets::weapon::m_flLastFireTime );
	}
	__forceinline PINT getSeed()
	{
		return ( PINT )( ( DWORD )( this ) + _offsets::weapon::weaponSeed );
	}

	bool isShotCritical()
	{
		__asm
		{
			mov edx, _offsets::weapon::isShotCritical
			mov ecx, this
			mov eax, dword ptr ds:[ecx]
			call dword ptr ds:[eax + edx]
		}
	}
	float getSpread()
	{
		__asm
		{
			mov edx, _offsets::weapon::getSpread
			mov ecx, this
			mov eax, dword ptr ds:[ecx]
			call dword ptr ds:[eax + edx]
		}
	}
	int getID()
	{
		__asm
		{
			mov edx, _offsets::weapon::getWeaponID
			mov ecx, this
			mov eax, dword ptr ds:[ecx]
			call dword ptr ds:[eax + edx]
		}
	}
	bool isMelee()
	{
		if( this->getID() == WEAPON_WRANGLER ) return false;

		int type = this->getPrimaryAmmoType();

		return ( type == -1 || type == 4 );
	}
};