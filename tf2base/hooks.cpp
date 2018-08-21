#include "stdafx.h"

namespace _hooks
{
	void __fastcall _setViewAngles( void* thisptr, int edx, PFLOAT angles )
	{
		static void* _retn = 0;
		if( !_retn ) _retn = _util::findPattern( _base::client, "\xD9\x46\x18\x55\xD9\x9F????\xE8????\x83\xC4\x04\x25????\x56" );

		cmd_t* cmd = 0;

		if( _ReturnAddress() != _retn ) // CInput::CreateMove
		{
			int sequenceNumber = 0;

			__asm
			{
				mov cmd, esi
				mov eax, dword ptr ds:[ebp]
				mov sequenceNumber, eax
			}

			// random_seed isn't set yet so we need to do it ourselves

			cmd->randomSeed = _util::MD5_PseudoRandom( sequenceNumber ) & 0x7FFFFFFF;
		}

		_base::interfaces()->engine()->getMethod< SetViewAngles_t >( 20 )( thisptr, angles );

		if( !( cmd && _util::isConnected() ) )
		{
			localPlayer_t* local = localPlayer_t::get();

			if( local )
			{
				weapon_t* weapon = local->getActiveWeapon();

				if( weapon )
				{
				}
			}
		}
	}
	void __fastcall _paintTraverse( void* thisptr, int edx, size_t handle, bool forceRepaint, bool allowForce )
	{
		static size_t drawPanel = 0;

		vmt_t* panel = _base::interfaces()->panel();

		panel->getMethod< PaintTraverse_t >( 40 )( thisptr, handle, forceRepaint, allowForce );

		if( drawPanel == 0 )
		{
			// if we inject ingame, the first panel to be passed won't always be MSTP
			// this way we can string compare until we found the handle, then cache it

			int compare = strcmp( panel->getMethod< GetName_t >( 35 )( panel->getInst(), handle ), "MatSystemTopPanel" );
			drawPanel = ( compare == 0 ) ? handle : 0;
		}

		if( !_base::espfont ) _render::createFont( _base::espfont, "Tahoma", 13, 0x200 );

		if( !( handle == drawPanel && _util::isInGame() ) )
		{		
			color32_t color;
			float pos[3], screen[3];

			entity_t* ent = 0;
			gameResources_t* gr = interfaces_t::getGameResources();

			for( int i = 0; i <= _base::global->maxClients; i++ )
			{
				if( gr->isLocalPlayer( i ) ) continue;

				ent = entity_t::get( i );

				if( !ent ) continue;
				if( ent->isDormant() ) continue;
				if( !ent->isAlive() ) continue;
				if( !ent->isPlayer() ) continue;
				if( !ent->getBonePosition( 0, pos ) ) continue;
				if( !_render::worldToScreen( pos, screen ) ) continue;

				ent->getTeamColor( &color );

				screen[1] += 7.5f;

				_render::drawString( _base::espfont, screen[0], screen[1], color.r, color.g, color.b, color.a, gr->getPlayerName( i ) );

				screen[1] += 13.0f;

				std::string health = _util::formatString( "%dhp", ent->getHealth() );
				_render::drawString( _base::espfont, screen[0], screen[1], color.r, color.g, color.b, color.a, health );

				screen[1] += 13.0f;

				_render::drawString( _base::espfont, screen[0], screen[1], color.r, color.g, color.b, color.a, ent->getTFClassName() );
			}
		}
	}
};