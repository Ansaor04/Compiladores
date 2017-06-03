#pragma once
#include "State.h"

class COpRelational : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	COpRelational();
	virtual ~COpRelational();
};

