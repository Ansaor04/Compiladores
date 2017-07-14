#include "Agrupation.h"
#include "FSM.h"


void CAgrupation::update()
{
	iToken = TokenID::E::agrupation;
	pStateMachine->pushChar();
	pStateMachine->pChar++;
	iNextState = States::Reading;
	if (*pStateMachine->pChar == '[' || *pStateMachine->pChar == ']')
		iToken = TokenID::E::opDimension;
}

void CAgrupation::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CAgrupation::onExit()
{
	pStateMachine->tmpToken.setType(iToken);
	pStateMachine->pushString();
}

CAgrupation::CAgrupation()
{
}


CAgrupation::~CAgrupation()
{
}
