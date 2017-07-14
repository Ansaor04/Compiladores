#include "OpRelational.h"
#include "FSM.h"


void COpRelational::update()
{
	pStateMachine->pushChar();
	pStateMachine->pChar++;
	iNextState = States::Reading;
}

void COpRelational::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void COpRelational::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::opRelational);
	pStateMachine->pushString();
}

COpRelational::COpRelational()
{
}


COpRelational::~COpRelational()
{
}
