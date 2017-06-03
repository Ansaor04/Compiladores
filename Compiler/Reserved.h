#pragma once
#include "State.h"

class CReserved : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CReserved();
	virtual ~CReserved();
};

