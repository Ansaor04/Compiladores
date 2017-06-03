#pragma once
#include "State.h"
class CVariable : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CVariable();
	virtual ~CVariable();
};

