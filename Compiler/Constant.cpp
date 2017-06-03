#include "Constant.h"
#include "FSM.h"


void CConstant::update()
{
	iToken = TokenID::E::Int;
	pStateMachine->pChar++;
	while (isDigit(*pStateMachine->pChar) || *pStateMachine->pChar == '.')
	{
		if (*pStateMachine->pChar == '.')
			iToken = TokenID::E::Float;
		pStateMachine->pushChar();
		pStateMachine->pChar++;

	}
	iNextState = States::E::Reading;
}

void CConstant::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CConstant::onExit()
{
	pStateMachine->actualToken.setType(iToken);
	pStateMachine->pushString();
}

CConstant::CConstant()
{
}


CConstant::~CConstant()
{
}

