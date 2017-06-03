#include "Function.h"
#include "FSM.h"

void CFunction::update()
{
	while (isLetter(*pStateMachine->pChar) || *pStateMachine->pChar != '(')
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
	}
	iNextState = States::Reading;
}

void CFunction::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CFunction::onExit()
{
	pStateMachine->actualToken.setType(TokenID::E::keyword);
	pStateMachine->pushString();
}

CFunction::CFunction()
{
}


CFunction::~CFunction()
{
}
