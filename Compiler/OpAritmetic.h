#pragma once
#include "State.h"

class COpAritmetic : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	COpAritmetic();
	virtual ~COpAritmetic();
};

