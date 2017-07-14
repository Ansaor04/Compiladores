#include "Coment.h"
#include "FSM.h"

void CComent::update()
{
	pStateMachine->pChar += 2;
	while (1)
	{
		if (*pStateMachine->pChar == '*')
			if (*(pStateMachine->pChar + 1) == '/')
				break;
		pStateMachine->pChar++;
	}
	pStateMachine->pChar += 2;

	iNextState = States::E::Reading;
}

void CComent::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CComent::onExit()
{
	pStateMachine->pushString();
}

CComent::CComent()
{
}


CComent::~CComent()
{
}
