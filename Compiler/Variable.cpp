#include "Variable.h"
#include "FSM.h"

bool isDigit(char &a)
{
	if (a >= 48 && a <= 57)
		return true;
	return false;
}

bool isLetter(char &a)
{
	if ((a >= 65 && a <= 90) || (a >= 97 && a <= 122))
		return true;
	return false;
}

bool isAlphanumeric(char &a)
{
	if (isDigit(a) || isLetter(a))
		return true;
	return false;
}


void CVariable::update()
{
	iNextState = States::E::Reading;

	while (*pStateMachine->pChar == ' ')
	{
		pStateMachine->pChar++;
	}

	if (stringCompare("var ", pStateMachine->pChar))
	{
		pStateMachine->tmpToken.setType(TokenID::E::keyword);
		while (*pStateMachine->pChar != ' ')
		{
			pStateMachine->pushString();
			pStateMachine->pChar++;
		}
		pStateMachine->pChar++;
	}
	
	if (isLetter(*pStateMachine->pChar))
	{
		pStateMachine->pushChar();
		pStateMachine->pChar++;
		while (*pStateMachine->pChar != ' ')
		{
			if (isAlphanumeric(*pStateMachine->pChar))
			{
				pStateMachine->pushChar();
				pStateMachine->pChar++;
			}
			else if (*pStateMachine->pChar == '[')
			{
				iNextState = States::E::Agrupation;
				return;
			}
			else if (*pStateMachine->pChar == ',')
			{
				iNextState = States::E::Delimitator;
				return;
			}
			else
			{
				iNextState = States::E::Error;
				return;
			}
		}
	}
	else
	{
		iNextState = States::E::Error;
		return;
	}

}

void CVariable::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CVariable::onExit()
{
	pStateMachine->tmpToken.setType(TokenID::E::id);
	pStateMachine->pushString();
}

CVariable::CVariable()
{
}


CVariable::~CVariable()
{
}
