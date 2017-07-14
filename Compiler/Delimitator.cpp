#include "Delimitator.h"
#include "FSM.h"


void CDelimitator::update()
{
	if (*pStateMachine->pChar == ',')
		bIsComa = true;
	else
		bIsComa = false;
	pStateMachine->pushChar();
	pStateMachine->pChar++;
}

void CDelimitator::onEnter()
{
	update();
	onExit();
	if (bIsComa)
		pStateMachine->popState();
	else
		pStateMachine->pushState(States::E::Reading);
}

void CDelimitator::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::delimitator);
	pStateMachine->pushString();
}

CDelimitator::CDelimitator()
{
}


CDelimitator::~CDelimitator()
{
}
