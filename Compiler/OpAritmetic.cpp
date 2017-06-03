#include "OpAritmetic.h"
#include "FSM.h"


void COpAritmetic::update()
{
	pStateMachine->pushChar();
	pStateMachine->pChar++;
	iNextState = States::Reading;
}

void COpAritmetic::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void COpAritmetic::onExit()
{
	pStateMachine->actualToken.setType(TokenID::E::opArithmetic);
	pStateMachine->pushString();
}

COpAritmetic::COpAritmetic()
{
}


COpAritmetic::~COpAritmetic()
{
}
