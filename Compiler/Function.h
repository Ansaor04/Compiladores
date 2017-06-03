#pragma once
#include "State.h"
class CFunction : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CFunction();
	~CFunction();
};

