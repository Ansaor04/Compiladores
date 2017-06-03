#include "Error.h"
#include "FSM.h"


void CError::update()
{
	while (*pStateMachine->pChar == ' ')
	{
		pStateMachine->pChar++;
	}
	iNextState = States::E::Reading;
}

void CError::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CError::onExit()
{
}

CError::CError()
{
}


CError::~CError()
{
}
