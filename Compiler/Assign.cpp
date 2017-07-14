#include "Assign.h"
#include "FSM.h"


void CAssign::update()
{
	iNextState = -1;
	while (iNextState == -1)
	{
		if (stringCompare("==", pStateMachine->pChar))
		{
			iNextState = States::E::OpRelational;
		}
		else if (*pStateMachine->pChar == ' ')
		{
			pStateMachine->pChar++;
		} 
		else if (stringCompare("=", pStateMachine->pChar))
		{
			pStateMachine->pushChar();
			pStateMachine->pChar++;
			iNextState = States::E::Reading;
		}
		else
		{
			iNextState = States::E::Error;
		}
	} 
}

void CAssign::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CAssign::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::assign);
	pStateMachine->pushString();
}

CAssign::CAssign()
{
}


CAssign::~CAssign()
{
}
