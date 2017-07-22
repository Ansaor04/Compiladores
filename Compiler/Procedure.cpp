#include "Procedure.h"
#include "FSM.h"

void CProcedure::update()
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

void CProcedure::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CProcedure::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::id);
	pStateMachine->pushString();
}

CProcedure::CProcedure()
{
}


CProcedure::~CProcedure()
{
}
