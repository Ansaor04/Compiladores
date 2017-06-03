#pragma once
#include "State.h"

class CDelimitator : public CState
{
public:
	bool bIsComa;
	void update();
	void onEnter();
	void onExit();
	CDelimitator();
	virtual ~CDelimitator();
};

