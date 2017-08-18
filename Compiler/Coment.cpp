#include "Coment.h"
#include "FSM.h"

void CComent::update()
{
	pStateMachine->pChar += 2;
	while (true)
	{
		if (stringCompare("\r\n", pStateMachine->pChar) || *pStateMachine->pChar == '\n')
		{
			pStateMachine->pChar += 2;
			pStateMachine->iLine++;
		}

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
