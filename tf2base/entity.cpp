#include "stdafx.h"

bool entity_t::getBonePosition( int bone, PFLOAT pos )
{
	PINT cond = this->getCond();

	if( *cond & TFCOND_DISGUISED ) *cond &= ~TFCOND_DISGUISED;
	if( *cond & TFCOND_CLOAKED ) *cond &= ~TFCOND_CLOAKED;

	matrix_t matrix[128];
	if( !this->setupBones( matrix, 128, 0x100, this->getSimulationTime() ) ) return false;
		
	pos[0] = matrix[bone][0][3];
	pos[1] = matrix[bone][1][3];
	pos[2] = matrix[bone][2][3];

	return true;
}

bool localPlayer_t::pathFree( PFLOAT dest, entity_t* target )
{
	trace_t tr;
	float src[3];
	
	this->getEyePos( src );	
	_util::UTIL_TraceLine( src, dest, 0x4200400B, this, 0, &tr );

	if( tr.fraction == 1.0f ) return true;

	if( tr.ent )
	{
		if( target && target->getIndex() == tr.ent->getIndex() ) return true;

		if( !strcmp( tr.ent->getClientClass()->GetName(), "CFuncRespawnRoomVisualizer" ) )
		{
			_util::UTIL_TraceLine( tr.end, dest, 0x4200400B, tr.ent, 0, &tr );

			if( tr.fraction == 1.0f ) return true;
			if( target && target->getIndex() == tr.ent->getIndex() ) return true;
		}
	}

	return false;
}

void localPlayer_t::getSpreadVector( int seed, PFLOAT angles, PFLOAT dir, weapon_t* weapon )
{
	static RandomSeed_t randomSeed = 0;
	if( !randomSeed ) randomSeed = ( RandomSeed_t )( GetProcAddress( _base::vstdlib, "RandomSeed" ) );

	static RandomFloat_t randomFloat = 0;
	if( !randomFloat ) randomFloat = ( RandomFloat_t )( GetProcAddress( _base::vstdlib, "RandomFloat" ) );

	randomSeed( seed & 0xFF );

	float spread = weapon->getSpread();
	if( ( _util::getCurtime( this ) - weapon->getLastFireTime() ) > 2.0f ) spread = 0.0f;

	float x = ( randomFloat( -0.5f, 0.5f ) + randomFloat( -0.5f, 0.5f ) ) * spread;
	float y = ( randomFloat( -0.5f, 0.5f ) + randomFloat( -0.5f, 0.5f ) ) * spread;

	float f[3], r[3], u[3];
	_util::angleVectors( angles, f, r, u );

	dir[0] = f[0] + ( r[0] * x ) + ( u[0] * y );
	dir[1] = f[1] + ( r[1] * x ) + ( u[1] * y );
	dir[2] = f[2] + ( r[2] * x ) + ( u[2] * y );

	_util::vectorNormalize( dir );
}

void localPlayer_t::removeSpread( cmd_t* cmd, weapon_t* weapon )
{
	float view[3], dir[3], spread[3], angles[3];

	view[0] = cmd->viewAngles[0];
	view[1] = cmd->viewAngles[1];
	view[2] = cmd->viewAngles[2];

	_util::clampAngle( view );

	this->getSpreadVector( cmd->randomSeed, view, spread, weapon );
	
	_util::vectorAngles( spread, angles );

	dir[0] = view[0] - angles[0];
	dir[1] = view[1] - angles[1];
	dir[2] = view[2] - angles[2];

	_util::clampAngle( dir );

	cmd->viewAngles[0] -= dir[0];
	cmd->viewAngles[1] -= dir[1];

	_util::clampAngle( cmd->viewAngles );
}

bool localPlayer_t::waitForCrit( cmd_t* cmd, weapon_t* weapon )
{
	static void* _addr = 0;
	if( !_addr ) _addr = _util::findPattern( _base::client, "\x8B\x0D????\x56\x8B\x74\x24\x08\x50\x51\xE8????" );

	PINT globalSeed = *( PINT* )( ( DWORD )( _addr ) + 0x2 );
	PINT weaponSeed = weapon->getSeed();

	int globalSeedBackup = *globalSeed;
	int weaponSeedBackup = *weaponSeed;

	*globalSeed = cmd->randomSeed;

	bool crit = !weapon->isShotCritical();

	*globalSeed = globalSeedBackup;
	*weaponSeed = weaponSeedBackup;

	return crit;
}

entity_t* entity_t::get( int index )
{
	vmt_t* entlist = _base::interfaces()->entlist();
	return ( entity_t* )( entlist->getMethod< GetClientEntity_t >( 3 )( entlist->getInst(), index ) );
}

localPlayer_t* localPlayer_t::get()
{
	vmt_t* entlist = _base::interfaces()->entlist();
	return ( localPlayer_t* )( entlist->getMethod< GetClientEntity_t >( 3 )( entlist->getInst(), _util::getLocalPlayer() ) );
}