#pragma once
#include "State.h"
class CComent : public CState
{
public:
	void update();
	void onEnter();
	void onExit();
	CComent();
	~CComent();
};

