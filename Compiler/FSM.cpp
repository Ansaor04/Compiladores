#include "FSM.h"


void CFSM::update()
{
	m_pActualState->onEnter();
}

void CFSM::pushState(int iState)
{
	m_Stack.push_back(iState);
	m_pActualState = m_States[m_Stack.back()];
}

void CFSM::popState()
{
	if (m_Stack.empty())
		m_Stack.push_back(States::E::Reading);
	else
		m_Stack.pop_back();
	m_pActualState = m_States[m_Stack.back()];

}

void CFSM::pushString()
{
	if (tmpToken.getToken().empty())
		return;
	lexFile << tmpToken.getToken() << " " << tmpToken.getType() << "\n";
	m_Tokens.push_back(CToken(tmpToken.getToken(), tmpToken.getType(), tmpToken.getIDType()));
	tmpToken.clearToken();
}

void CFSM::pushChar()
{
	char tmp = *pChar;
	tmpToken.getToken().push_back(tmp);
}

void CFSM::pushError()
{
	switch (iNumPhase)
	{
	case CompilerPhase::E::lexic:
		{
			if (bHasErrors)
				errorFile << "Error de lexico en linea " << iLine << " \n";
			else
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
				errorFile << "Error de lexico en linea " << iLine << " \n";
			}
		}
		break;
	case CompilerPhase::E::syntactic:
		{
			if (bHasErrors)
				errorFile << "Error de Sintactico en el token " << Syn->getActualToken()->getToken() << " \n";
			else
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
				errorFile << "Error de Sintactico en el token " << Syn->getActualToken()->getToken() << " \n";
			}
		}
		break;
	}


}

void CFSM::openFile(int iType)
{
	switch (iType)
	{
	case CompilerPhase::E::lexic:
		lexFile.open(filename + ".lex");
		break;
	case CompilerPhase::E::syntactic:
		symbolTable.open(filename + ".symb");
		break;
	case CompilerPhase::E::semantic:
		//		syntactic.open(filename + ".syn");
		break;
	}

}

void CFSM::closeFile()
{
	lexFile.close();
	symbolTable.close();
//	syntactic.close();

	if (bHasErrors)
		errorFile.close();
}


void CFSM::setMode(int iType)
{
	iNumPhase = iType;
	openFile(iType);
}


CFSM::CFSM()
{
	iLine = 0;
	Syn = new Syntactic(this);
	iNumPhase = CompilerPhase::E::lexic;
	bHasErrors = false;
	for (int i = 0; i < 14; i++)
		m_States[i]->pStateMachine = this;
	m_pActualState = m_States[0];
}

CFSM::~CFSM()
{
	delete Syn;
}
