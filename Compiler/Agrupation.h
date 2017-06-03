#pragma once
#include "State.h"

class CAgrupation : public CState
{
public:
	int iToken;
	void update();
	void onEnter();
	void onExit();
	CAgrupation();
	virtual ~CAgrupation();
};

