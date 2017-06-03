#pragma once
#include "State.h"

class CError : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CError();
	virtual ~CError();
};

