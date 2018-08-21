#pragma once

#include "stdafx.h"

namespace _hooks
{
	extern void __fastcall _setViewAngles( void* thisptr, int edx, PFLOAT angles );
	extern void __fastcall _paintTraverse( void* thisptr, int edx, size_t handle, bool forceRepaint, bool allowForce );
};