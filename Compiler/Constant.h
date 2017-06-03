#pragma once
#include "State.h"

class CConstant : public CState
{
public:
	int iToken;
	void update();
	void onEnter();
	void onExit();
	CConstant();
	virtual ~CConstant();
};

