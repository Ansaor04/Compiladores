#include "Reserved.h"
#include "FSM.h"


void CReserved::update()
{
	/*if (stringCompare("print", pStateMachine->pChar) || stringCompare("read", pStateMachine->pChar))
	{
		while (isLetter(*pStateMachine->pChar))
		{
			pStateMachine->pushChar();
			pStateMachine->pChar++;
		}
		pStateMachine->tmpToken.setType(TokenID::E::keyword);
		pStateMachine->pushString();

		pStateMachine->pushChar();
		pStateMachine->pChar++;
		pStateMachine->tmpToken.setType(TokenID::E::agrupation);
		pStateMachine->pushString();

		if (*pStateMachine->pChar == '"')
		{
			pStateMachine->pChar++;
			while (*pStateMachine->pChar != '"')
			{
				pStateMachine->pushChar();
				pStateMachine->pChar++;
			}
			pStateMachine->tmpToken.setType(TokenID::E::String);
			pStateMachine->pushString();
			pStateMachine->pChar++;
		}
	}
	else*/
	{
		while (isLetter(*pStateMachine->pChar))
		{
			pStateMachine->pushChar();
			pStateMachine->pChar++;
		}

		pStateMachine->tmpToken.setType(TokenID::E::keyword);
		pStateMachine->pushString();
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

}

CReserved::CReserved()
{
}


CReserved::~CReserved()
{
}
