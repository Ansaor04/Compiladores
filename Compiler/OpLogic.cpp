#include "OpLogic.h"
#include "FSM.h"


void COpLogic::update()
{
	if (*pStateMachine->pChar == '!')
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
	}
	else
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
		pStateMachine->pushChar();
		pStateMachine->pChar++;
	}

	iNextState = States::Reading;
}

void COpLogic::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void COpLogic::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::opLogic);
	pStateMachine->pushString();
}

COpLogic::COpLogic()
{
}


COpLogic::~COpLogic()
{
}
