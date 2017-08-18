#include "Semantic.h"
#include "FSM.h"

void Semantic::skipTo(std::string find, bool extraJump)
{
	while (pActualtoken->getToken() != find)
		getNextToken();
	if (extraJump)
		getNextToken();
	return;
}

void Semantic::getNextToken()
{
	if (std::distance(pActualtoken, pStateMachine->getTokens().end()) != 1)
		pActualtoken++;
}

CToken * Semantic::peekNextToken(int iPeek)
{
	std::list<CToken>::iterator tmpIter = pStateMachine->getTokens().begin();

	for (tmpIter; tmpIter != pStateMachine->getTokens().end(); tmpIter++)
	{
		if (!std::distance(tmpIter, pActualtoken))
		{
			for (int iIndexPeek = 0; iIndexPeek < iPeek; iIndexPeek++)
			{
				tmpIter++;
				if (tmpIter == pStateMachine->getTokens().end())
					return nullptr;
			}
			return &(*tmpIter);
		}
	}
	return nullptr;
}

bool Semantic::isStatement()
{
	if (pActualtoken->getToken() == "return" || pActualtoken->getToken() == "if" || pActualtoken->getToken() == "while" || pActualtoken->getToken() == "for" || pActualtoken->getToken() == "switch"
		|| pActualtoken->getToken() == "print" || pActualtoken->getToken() == "read")
		return true;
	return false;
}

bool Semantic::isCall()
{
	if (pActualtoken->getIDType() == TokenID::E::id)
		if (peekNextToken(1)->getToken() == "(")
			return true;
	return false;
}

bool Semantic::isAssign()
{
	if (pActualtoken->getIDType() == TokenID::E::id)
		if (peekNextToken(1)->getToken() == "=")
			return true;
		else if (peekNextToken(4)->getToken() == "=")
			return true;
	return false;
}

bool Semantic::isOperator()
{
	if (pActualtoken->getIDType() == TokenID::E::opArithmetic || pActualtoken->getIDType() == TokenID::E::opLogic || pActualtoken->getIDType() == TokenID::E::opRelational)
		return true;
	return false;
}

bool Semantic::varExist()
{
	for (auto &it : pStateMachine->Syn->m_nodes)
	{
		if (it->m_name == pActualtoken->getToken() && it->m_iType == pActualtoken->getIDType() - MAXTYPES)
			return true;
	}
	return false;
}

void Semantic::checkTokens()
{
	if (pStateMachine->getTokens().empty())
		return;
	pActualtoken = pStateMachine->getTokens().begin();
	checkProgram();
}

void Semantic::checkProgram()
{
	while (pActualtoken->getToken() == "var")
		while (checkVarDecl())
			checkDimention();

	while (pActualtoken->getToken() == "procedure")
		checkProcedure();

	while (pActualtoken->getToken() == "function")
		checkFunction();

	if(pActualtoken->getToken() == "main")
		checkMain();
}

void Semantic::checkMain()
{
	getNextToken();
	getNextToken();
	getNextToken();
	checkBlock();
}

void Semantic::checkFunction()
{
	getNextToken();

	functName = pActualtoken->getToken();

	skipTo(":", true);

	iReturnType = pActualtoken->getIDType();
	bHasReturn = true;

	getNextToken();
	checkBlock();

	bHasReturn = false;
	iReturnType = -1;

}

void Semantic::checkProcedure()
{
	skipTo("{", false);
	checkBlock();
}

void Semantic::checkAsign()
{
	if (!varExist())
		pStateMachine->pushError(SynE::VarNotDefined, pActualtoken->getToken());
	CToken* Assign = &(*pActualtoken);

	if (peekNextToken(1)->getToken() == "[")
		skipTo("]", false);

	getNextToken();
	getNextToken();

	if (Assign->getIDType() != checkExpresion())
		pStateMachine->pushError(SynE::E::IncompAssign, Assign->getToken());

//	skipTo(";", true);

}

int Semantic::checkCall()
{
	for (auto &it : pStateMachine->Syn->m_nodes)
	{
		if (it->m_name == pActualtoken->getToken())
		{
			if (it->m_iCategory == nodesCat::E::function)
			{
				skipTo(";", true);
				return it->m_iType + MAXTYPES;
			}
			else
			{
				pStateMachine->pushError(SynE::E::undeclared, "call : " + pActualtoken->getToken());
				skipTo(";", true);
				return -1;
			}
		}
	}
	pStateMachine->pushError(SynE::E::undeclared, "call : " + pActualtoken->getToken());
	skipTo(";", true);
	return -1;
}

void Semantic::checkDimention()
{
	getNextToken();
	if (pActualtoken->getToken() == "-" || pActualtoken->getToken() == "0")
		pStateMachine->pushError(SynE::E::arrayNegative, "");
	else if (pActualtoken->getIDType() != TokenID::E::Int)
		pStateMachine->pushError(SynE::E::DimensionArray, "");
	skipTo("]", true);
}

void Semantic::checkStatements()
{
	if (pActualtoken->getToken() == "return")
	{
		if (!bHasReturn)
		{
			pStateMachine->pushError(SynE::E::WrongReturn, "");
			skipTo(";", true);
			return;
		}
		else
		{
			getNextToken();
			if (checkExpresion() != iReturnType)
				pStateMachine->pushError(SynE::ReturnMismatch, "");
		}

	}
	else if (pActualtoken->getToken() == "if")
	{
		getNextToken();
		getNextToken();

		if (checkExpresion() != TokenID::E::Bool)
			pStateMachine->pushError(SynE::statementBool, "if");

		getNextToken();
		checkBlock();
		if (pActualtoken->getToken() == "else")
		{
			getNextToken();
			checkBlock();
		}
	}
	else if (pActualtoken->getToken() == "while")
	{
		getNextToken();
		getNextToken();

		if (checkExpresion() != TokenID::E::Bool)
			pStateMachine->pushError(SynE::statementBool, "while");

		getNextToken();
		checkBlock();
	}
	else if (pActualtoken->getToken() == "for")
	{
		skipTo(";", true);

		if (checkExpresion() != TokenID::E::Bool)
			pStateMachine->pushError(SynE::statementBool, "for");

		if (checkExpresion() == TokenID::E::Bool)
			pStateMachine->pushError(SynE::statementNonBool, "for");

		checkBlock();

	}
	else if (pActualtoken->getToken() == "switch")
	{
		getNextToken();
		getNextToken();
		if (pActualtoken->getIDType() != TokenID::E::Int)
			pStateMachine->pushError(SynE::E::SwitchInt, "");

		skipTo("{", true);
		while (pActualtoken->getToken() != "}")
		{
			while (pActualtoken->getIDType() == TokenID::E::Int || pActualtoken->getToken() == "default")
			{
				getNextToken();
				getNextToken();
				checkBlock();
			}

			if (pActualtoken->getIDType() == TokenID::E::Float)
			{
				pStateMachine->pushError(SynE::E::SwitchInt, " on token " + pActualtoken->getToken());
				skipTo("}", true);
				getNextToken();
			}
		}

	}
	else if (pActualtoken->getToken() == "print")
	{
	}
	else if (pActualtoken->getToken() == "read")
	{
	}
}

int Semantic::checkExpresion()
{
	if (pActualtoken->getToken() == ")" || pActualtoken->getToken() == ";")
		pStateMachine->pushError(SynE::E::noExpresion, "");

	int iResult = -1;

	if (peekNextToken(1)->getToken() == ";")
	{
		if (pActualtoken->getToken() == "true" || pActualtoken->getToken() == "false")
		{			
			return TokenID::E::Bool;
			skipTo(";", true);
		}
		else
		{
			iResult = pActualtoken->getIDType();
			skipTo(";", true);
			return iResult;
		}

	}

	std::map<bool, CToken> tmpTree;

	Expresion(tmpTree);
	
	vecTrees.push_back(tmpTree);

	skipTo(";", true);
	return iResult;
}

void Semantic::Expresion(std::map<bool, CToken>& tree)
{
	if (pActualtoken->getIDType() == TokenID::E::id)
	{
		getNextToken();
		if (isOperator())
		{
			getNextToken();
			if (pActualtoken->getToken() == "(")
				Expresion(tree);
			else if (pActualtoken->getIDType() == TokenID::E::id)
				getNextToken();
		}
		if (pActualtoken->getToken() == ";")
		{
			getNextToken();
			return;
		}
	}
	else if (pActualtoken->getToken() == "(")
	{
		getNextToken();
		Expresion(tree);
		if (peekNextToken(1)->getToken() == ";")
		{
			getNextToken();
			getNextToken();
		}
		else if (pActualtoken->getToken() == ")")
			getNextToken();
		return;
	}

	
}

bool Semantic::checkVarDecl()
{
	while (pActualtoken->getToken() != ";")
	{
		if (pActualtoken->getToken() == "[")
			return true;
		else
			getNextToken();
	}
	getNextToken();
	return false;
}

void Semantic::checkBlock()
{
	getNextToken();
	while (pActualtoken->getToken() != "}")
	{
		if (isAssign())
			checkAsign();
		else if (isCall())
			checkCall();
		else if (isStatement())
			checkStatements();
		else if (pActualtoken->getToken() == "var")
			skipTo(";", true);
		else if (pActualtoken->getToken() != "}")
			getNextToken();
	}
	getNextToken();
}

Semantic::Semantic(CFSM * pFSM)
{
	pStateMachine = pFSM;
	pNodes = &pStateMachine->Syn->m_nodes;
	bHasReturn = false;
	iReturnType = -1;
}

Semantic::Semantic()
{
}


Semantic::~Semantic()
{
}