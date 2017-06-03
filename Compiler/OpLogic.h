#pragma once
#include "State.h"

class COpLogic : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	COpLogic();
	virtual ~COpLogic();
};

