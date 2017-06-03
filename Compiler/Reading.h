#pragma once
#include "State.h"

class CReading : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CReading();
	virtual ~CReading();
};

