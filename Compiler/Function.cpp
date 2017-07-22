#include "Function.h"
#include "FSM.h"

void CFunction::update()
{
	while (*pStateMachine->pChar != ' ')
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
	}
	pStateMachine->tmpToken.setType(TokenID::E::keyword);
	pStateMachine->pushString();
	pStateMachine->pChar++;

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
	pStateMachine->tmpToken.setType(TokenID::E::id);
	pStateMachine->pushString();
}

CFunction::CFunction()
{
}


CFunction::~CFunction()
{
}
