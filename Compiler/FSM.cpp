#include "FSM.h"


std::string g_SynError[20] =
{
"Variable already defined : ",
"Expected ",
"No entry point defined",
"Expected type 'int' on a switch statement",
"Expresion must return a value",
"Function must have a return type",
"Array index must be an integer",
"Variable does not exist :",
"Only functions return values",
"Incompatible type on assign :",
"Function return type does not match",
"Statement must have a boolean expresion :",
"Statement must be an incrementable expresion : ",
"Array index can not be less or equals to zero",
"Expected an expresion",
"",
"Undeclared ",
"",
"",
""
};


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
			if (!bHasErrors)
			{ 
				bHasErrors = true;
				errorFile.open(filename + ".err");
			}
			errorFile << "Lexic error on line  " << iLine << " \r\n";
		}
		break;
	case CompilerPhase::E::syntactic:
		{
			if (!bHasErrors)
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
			}
			errorFile << "Syntactic error on token " << Syn->getActualToken()->getToken() << " \r\n";
		}
		break;

	case CompilerPhase::E::semantic:
		{
			if (!bHasErrors)
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
			}
			errorFile << "Semantic error on token " << Sem->pActualtoken->getToken() << " \r\n";
		}
	break;
	}
}

void CFSM::pushError(int iError, std::string info)
{
	switch (iNumPhase)
	{
		case CompilerPhase::E::lexic:
			//aun no se implementa
		break;
		case CompilerPhase::E::syntactic:
		{
			if (!bHasErrors)
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
			}
			if (!Syn->localVarName.empty() && iError != SynE::E::custom)
				errorFile << g_SynError[iError] << info << " in " << Syn->localVarName << "\r\n";
			else
				errorFile << g_SynError[iError] << info <<  "\r\n";

		}
		break;
		case CompilerPhase::E::semantic:
		{
			if (!bHasErrors)
			{
				bHasErrors = true;
				errorFile.open(filename + ".err");
			}
			if (!Sem->functName.empty())
				errorFile << g_SynError[iError] << info << " in " << Sem->functName << "\r\n";
			else
				errorFile << g_SynError[iError] << info << "\r\n";
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

void CFSM::reset()
{
	iLine = 0;
	bHasErrors = false;

	Syn->m_nodes.clear();
	Syn->iRecoveredErrors = 0;
	m_Tokens.clear();
	Syn->global = true;
}


CFSM::CFSM()
{
	iLine = 0;
	Syn = new Syntactic(this);
	Sem = new Semantic(this);
	iNumPhase = CompilerPhase::E::lexic;
	bHasErrors = false;
	for (int i = 0; i < 14; i++)
		m_States[i]->pStateMachine = this;
	m_pActualState = m_States[0];
}

CFSM::~CFSM()
{
	delete Syn;
	delete Sem;
}
