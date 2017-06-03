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
	if (actualToken.getToken().empty())
		return;
	lexFile << actualToken.getToken() << " " << actualToken.getType() << "\n";
	actualToken.clearToken();
}

void CFSM::pushChar()
{
	char tmp = *pChar;
	actualToken.getToken().push_back(tmp);
}

void CFSM::openFile(char * pfilename)
{
	lexFile.open(pfilename);
}

void CFSM::closeFile()
{
	lexFile.close();
}

CFSM::CFSM()
{
	for (int i = 0; i < 14; i++)
		m_States[i]->pStateMachine = this;
	m_pActualState = m_States[0];
}

CFSM::~CFSM()
{
}
