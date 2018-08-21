#pragma once

#include "stdafx.h"

struct cplane_t
{
	float normal[3];
	float dist;
	BYTE type;
	BYTE signBits;
	BYTE pad[2];
};

struct csurface_t
{
	const char* name;
	short surfaceProps;
	WORD flags;
};

struct trace_t
{
	float start[3];
	float end[3];
	cplane_t plane;
	float fraction;
	int contents;
	WORD dispFlags;
	bool allSolid;
	bool startSolid;
	float fractionLeftSolid;
	csurface_t surface;
	int hitGroup;
	short physicsBone;
	entity_t* ent;
	int hitbox;
};
