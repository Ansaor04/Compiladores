#include "Procedure.h"
#include "FSM.h"

void CProcedure::update()
{
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
	pStateMachine->tmpToken.setType(TokenID::E::keyword);
	pStateMachine->pushString();
}

CProcedure::CProcedure()
{
}


CProcedure::~CProcedure()
{
}
