#pragma once
#include "State.h"
class CProcedure : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CProcedure();
	~CProcedure();
};

