#include "Reserved.h"
#include "FSM.h"


void CReserved::update()
{
	while (isLetter(*pStateMachine->pChar))
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
	}
	iNextState = States::Reading;
}

void CReserved::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CReserved::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::keyword);
	pStateMachine->pushString();
}

CReserved::CReserved()
{
}


CReserved::~CReserved()
{
}
