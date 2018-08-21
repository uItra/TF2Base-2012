#pragma once

#include "stdafx.h"

struct globals_t
{
	float realTime;
	int frameCount;
	float absoluteFrameTime;
	float curTime;
	float frameTime;
	int maxClients;
	int tickCount;
	float intervalPerTick;
	float interpolationAmount;
	int simticksThisFrame;
	int networkProtocol;
	void* saveData;
	bool isClient;
	int timeStampNetworkingBase;   
	int timeStampRandomizeWindow;	
};