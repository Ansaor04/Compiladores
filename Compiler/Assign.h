#pragma once
#include "State.h"
class CAssign : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CAssign();
	virtual ~CAssign();
};

