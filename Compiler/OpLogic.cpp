#include "OpLogic.h"
#include "FSM.h"


void COpLogic::update()
{
	pStateMachine->pushChar();
	pStateMachine->pChar++;
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
	pStateMachine->actualToken.setType(TokenID::E::opLogic);
	pStateMachine->pushString();
}

COpLogic::COpLogic()
{
}


COpLogic::~COpLogic()
{
}
