#include "Reading.h"
#include "FSM.h"

bool stringCompare(std::string str, char * pcSource)
{
	char *pActualChar = pcSource;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] == *pActualChar)
			pActualChar++;
		else
			return false;
	}
	return true;
}

bool isCall(char * pcSource)
{
	char *pActualChar = pcSource;

	while (*pActualChar != ' ')
	{
		if (!isAlphanumeric(*pActualChar))
			return false;
		pActualChar++;
		if (*pActualChar == '(')
			return true;
	}
	return false;
}


void CReading::update() //To do.. optimizar los ciclos "For"
{

	while (*pStateMachine->pChar == ' ' || *pStateMachine->pChar == '\t')
	{
		pStateMachine->pChar++;
	}

	if (stringCompare("\r\n", pStateMachine->pChar) || *pStateMachine->pChar == '\n')
	{
		pStateMachine->pChar += 2;
		pStateMachine->iLine++;
		iNextState = States::E::Reading;
		return;
	}

	if (stringCompare("/*", pStateMachine->pChar))
	{
		iNextState = States::E::Comment;
		return;
	}

	for (int iReserved = 0; iReserved < 15; iReserved++)
	{
		if (stringCompare(reservedWords[iReserved], pStateMachine->pChar))
		{
			iNextState = States::E::Reserved;
			return;
		}
	}

	for (int iLogic = 0; iLogic < 3; iLogic++)
	{
		if (stringCompare(operatorLogic[iLogic], pStateMachine->pChar))
		{
			iNextState = States::E::OpLogic;
			return;
		}
	}

	for (int iOper = 0; iOper < 6; iOper++)
	{
		if (stringCompare(operatorAritmetic[iOper], pStateMachine->pChar))
		{
			iNextState = States::E::OpAritmetic;
			return;
		}
		else if (stringCompare(operatorRelational[iOper], pStateMachine->pChar))
		{
			iNextState = States::E::OpRelational;
			return;
		}
	}

	for (int iState = States::E::Variable; iState < States::E::Delimitator; iState++)
	{
		if (stringCompare(keyWords[iState], pStateMachine->pChar))
		{
			iNextState = iState;
			return;
		}
	}

	if (*pStateMachine->pChar == ';' || *pStateMachine->pChar == ',' || *pStateMachine->pChar == ':')
	{
		iNextState = States::E::Delimitator;
		return;
	}

	if (isCall(pStateMachine->pChar)) 
	{
		while (*pStateMachine->pChar != '(')
		{
			pStateMachine->pushChar();
			pStateMachine->pChar++;
		}
		pStateMachine->tmpToken.setType(TokenID::E::id);
		pStateMachine->pushString();

		iNextState = States::E::Agrupation;
		return;
	}

	if (isDigit(*pStateMachine->pChar))
	{
		iNextState = States::E::Constant;
		return;
	}

	if (isLetter(*pStateMachine->pChar) || *pStateMachine->pChar == '"')
	{
		iNextState = States::E::Variable;
		return;
	}

	if (*pStateMachine->pChar == ']' || *pStateMachine->pChar == '(' || *pStateMachine->pChar == ')' 
		|| *pStateMachine->pChar == '[' || *pStateMachine->pChar == '{' || *pStateMachine->pChar == '}')
	{
		iNextState = States::E::Agrupation;
		return;
	}

	iNextState = States::E::Error;
}

void CReading::onEnter()
{
	update();
	onExit();
	pStateMachine->pushState(iNextState);
}

void CReading::onExit()
{
	pStateMachine->pushString();
}

CReading::CReading()
{
}


CReading::~CReading()
{
}
