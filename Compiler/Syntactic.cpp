#include "Syntactic.h"
#include "FSM.h"

std::list<CToken>::iterator nextElement(std::list<CToken>::iterator iter)
{
	return iter++;
}

bool Syntactic::tokenIsValue()
{
	if (pActualtoken->getIDType() == TokenID::E::Float || pActualtoken->getIDType() == TokenID::Int || pActualtoken->getIDType() == TokenID::E::String
		|| pActualtoken->getToken() == "true" || pActualtoken->getToken() == "false")
		return true;
	return false;
}

bool Syntactic::tokenIsStatement()
{
	if (pActualtoken->getToken() == "return" || pActualtoken->getToken() == "if" || pActualtoken->getToken() == "while" || pActualtoken->getToken() == "for" || pActualtoken->getToken() == "switch" 
		|| pActualtoken->getToken() == "print" || pActualtoken->getToken() == "read")
		return true;
	return false;
}

bool Syntactic::tokenIsKeywordValue()
{
	if (pActualtoken->getToken() == "float" || pActualtoken->getToken() == "int" || pActualtoken->getToken() == "string" || pActualtoken->getToken() == "bool")
		return true;
	return false;
}

void Syntactic::insertNode(std::string &pName, int iCat, int iType, int iDim, CNode *pLocal, CNode *pNext)
{
	CNode *pActualNode;

	if (global)
		pActualNode = new CGlobalNode;
	else
		pActualNode = new CLocalNode;

	pActualNode->m_name = pName;
	pActualNode->m_iCategory = iCat;
	pActualNode->m_iType = iType;
	pActualNode->m_iDimention = iDim;
	if (global)
	{
		((CGlobalNode*)pActualNode)->pLocal = ((CLocalNode*)pLocal);
		((CGlobalNode*)pActualNode)->pNext = ((CGlobalNode*)pNext);
	}
	else
	{
		((CLocalNode*)pActualNode)->pLocal = ((CLocalNode*)pLocal);
		((CLocalNode*)pActualNode)->pNext = ((CLocalNode*)pNext);
	}

	for (auto &it : m_nodes)
	{
		if (it->m_name == pActualNode->m_name)
		{
			if (it->m_iCategory == pActualNode->m_iCategory)
				pStateMachine->pushError(SynE::E::DefVar, pName);
			else
			{
				if (it->m_iCategory == nodesCat::E::global)
				{
					if (((CGlobalNode*)it)->pNext == nullptr)
					{
						((CGlobalNode*)it)->pNext = (CGlobalNode*)pActualNode;
						break;
					}
				}
				else
				{
					if (((CGlobalNode*)it)->pNext == nullptr)
					{
						((CLocalNode*)it)->pNext = (CLocalNode*)pActualNode;
						break;
					}
				}
			}
		}
	}

	m_nodes.push_back(pActualNode);
	pStateMachine->symbolTable << pActualNode->createStrData() << "\r\n";

}

void Syntactic::insertToken(CToken tmpToken)
{
	iRecoveredErrors++;
	pActualtoken = pStateMachine->getTokens().insert(pActualtoken, tmpToken);
}



void Syntactic::getNextToken()
{
	if (std::distance(pActualtoken, pStateMachine->getTokens().end()) != 1)
		pActualtoken++;
}

void Syntactic::errorPanic(std::string find)
{
	while (pActualtoken->getToken() != find)
	{
		getNextToken();
	}
	return;
}

CToken * Syntactic::peekNextToken(int iPeek)
{
	std::list<CToken>::iterator tmpIter = pStateMachine->getTokens().begin();

	for (tmpIter; tmpIter != pStateMachine->getTokens().end(); tmpIter++)
	{
		if(!std::distance(tmpIter, pActualtoken))
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

void Syntactic::processTokens()
{
	if (pStateMachine->getTokens().empty())
		return;
	pActualtoken = pStateMachine->getTokens().begin();
	processProgram();
}

void Syntactic::processProgram()
{
		
	while (pActualtoken->getToken() == "var")
		processVars();

	global = false;

	while (pActualtoken->getToken() == "procedure")
		processProcedure();

	while (pActualtoken->getToken() == "function")
		processFunction();

	if(processMain())
		processBlock();

}

bool Syntactic::processMain()
{

	if (pActualtoken->getToken() != "main")
	{
		for (pActualtoken = pStateMachine->getTokens().begin(); std::distance(pActualtoken, pStateMachine->getTokens().end()) != 1; pActualtoken++)
		{
			if (pActualtoken->getToken() == "main")
				break;
		}
		if (pActualtoken->getToken() != "main")
		{
			pStateMachine->pushError(SynE::E::NoMain, "");
			return false;
		}
	}
	localVarName = pActualtoken->getToken();

	getNextToken();
	if (pActualtoken->getToken() != "(")
		insertToken(CToken("(", "agrupation", TokenID::E::agrupation));

	getNextToken();
	if (pActualtoken->getToken() != ")")
		insertToken(CToken("(", "agrupation", TokenID::E::agrupation));

	getNextToken();
	return true;
}

int Syntactic::processVarType()
{
	int iType;

	if (pActualtoken->getToken() == "float")
		iType = TokenID::Float;
	else if (pActualtoken->getToken() == "int")
		iType = TokenID::Int;
	else if (pActualtoken->getToken() == "string")
		iType = TokenID::String;
	else if (pActualtoken->getToken() == "bool")
		iType = TokenID::Bool;
	else
		pStateMachine->pushError();

	getNextToken();

	return iType;
}
#define MAX_VAR_DEC 20

void Syntactic::processVars()
{
	int iVarNum = 0, iType, iDim[MAX_VAR_DEC];
	std::string names[MAX_VAR_DEC];
	do
	{
		getNextToken();

		if (pActualtoken->getIDType() != TokenID::E::id)
			pStateMachine->pushError();

		names[iVarNum] = pActualtoken->getToken();

		getNextToken();
		if (pActualtoken->getToken() == "[")
			iDim[iVarNum] = processDimension();
		iVarNum++;

	} while (pActualtoken->getToken() == ",");

	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError(SynE::E::Expect, "':'");

	getNextToken();
	iType = processVarType() - MAXTYPES;

	if (iType < 0)
	{
		errorPanic(";");
		getNextToken();
		return;
	}

	for (int i = 0; i < iVarNum; i++)
		insertNode(names[i], global, iType, iDim[i], nullptr, nullptr);

	if (pActualtoken->getToken() != ";")
		pStateMachine->pushError();

	if(peekNextToken(1) != nullptr)
		getNextToken();
}

void Syntactic::processAssign()
{

	if (pActualtoken->getIDType() != TokenID::E::assign)
		pStateMachine->pushError();

	getNextToken();

	processExpresion();

}


void Syntactic::processProcedure()
{

	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		localVarName = pActualtoken->getToken();

	insertNode(localVarName, nodesCat::E::procedure, 0, 0, nullptr, nullptr);

	getNextToken();
	processParam();

	getNextToken();
	processBlock();
	getNextToken();

	localVarName.clear();
}

void Syntactic::processFunction()
{

	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		localVarName = pActualtoken->getToken();

	getNextToken();
	processParam();

	getNextToken();
	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError(SynE::E::Expect, "':' on return type of function");
	getNextToken();
	if (!tokenIsKeywordValue())
		pStateMachine->pushError(SynE::E::RetFunction, "");
	

	insertNode(localVarName, nodesCat::E::function, pActualtoken->getIDType() - MAXTYPES, 0, nullptr, nullptr);

	getNextToken();
	processBlock();
	getNextToken();

	localVarName.clear();
}

void Syntactic::processCall()
{
	getNextToken();

	if(peekNextToken(1)->getToken() != ")" && pActualtoken->getToken() != ")")
		processListExpres();
	else if (pActualtoken->getToken() != ")")
		getNextToken();

	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError(SynE::E::Expect, ")");
	getNextToken();
	if (pActualtoken->getToken() != ";")
		pStateMachine->pushError();
	//else
	//	getNextToken();

}

void Syntactic::processListExpres()
{
	getNextToken();
	do
	{
		if (pActualtoken->getToken() == ",")
			getNextToken();

		processExpresion();
		if(pActualtoken->getToken() != ")" && pActualtoken->getToken() != ",")
			getNextToken();
	} while (pActualtoken->getToken() == ",");
}

void Syntactic::processExpresion() 
{

	if (pActualtoken->getIDType() == TokenID::E::id || tokenIsValue())
	{
		getNextToken();

		if (pActualtoken->getToken() == "[")
		{
			getNextToken();
			getNextToken();
			getNextToken();
		}

		if (pActualtoken->getIDType() == TokenID::E::opArithmetic || pActualtoken->getIDType() == TokenID::E::opLogic || pActualtoken->getIDType() == TokenID::E::opRelational)
		{
			processOper();

			if (peekNextToken(1)->getToken() == "[")
			{
				getNextToken();
				getNextToken();
				getNextToken();
				getNextToken();
			}

			if (pActualtoken->getToken() == "(")
			{
				getNextToken();
				processExpresion();
				getNextToken();
				if (pActualtoken->getToken() != ")")
					pStateMachine->pushError(SynE::E::Expect, ")");

			}
			else if (pActualtoken->getToken() != ")")
			{
				if (tokenIsValue() || pActualtoken->getToken() == "-")
				{
					if (pActualtoken->getToken() == "-")
						getNextToken();
				}
				else
				{
					if (pActualtoken->getIDType() != TokenID::E::id)
						pStateMachine->pushError();
				}

			}
		}
		else if (pActualtoken->getToken() == "(")
			processCall();
		else if (pActualtoken->getIDType() == TokenID::E::assign)
			processAssign();

	}
	else if (pActualtoken->getToken() == "(")
	{
		getNextToken();
		processExpresion();

		getNextToken();

		if (pActualtoken->getIDType() == TokenID::E::opArithmetic || pActualtoken->getIDType() == TokenID::E::opLogic || pActualtoken->getIDType() == TokenID::E::opRelational)
		{
			processOper();

			if (peekNextToken(1)->getToken() == "[")
			{
				getNextToken();
				getNextToken();
				getNextToken();
				getNextToken();
			}

			if (pActualtoken->getToken() == "(")
			{
				getNextToken();
				processExpresion();
				getNextToken();
				if (pActualtoken->getToken() != ")")
					pStateMachine->pushError(SynE::E::Expect, ")");

			}

			else if (pActualtoken->getToken() != ")")
			{
				if (tokenIsValue() || pActualtoken->getToken() == "-")
				{
					if (pActualtoken->getToken() == "-")
						getNextToken();
				}
				else
				{
					if (pActualtoken->getIDType() != TokenID::E::id)
						pStateMachine->pushError();
				}

			}
		}

		else if (pActualtoken->getToken() == "(")
			processCall();
		else if (pActualtoken->getIDType() == TokenID::E::assign)
			processAssign();

		if (peekNextToken(1)->getToken() == ")")
		{
			getNextToken();
			if (peekNextToken(1)->getToken() == ";")
				getNextToken();
		}

	}
	else if (pActualtoken->getToken() == "!" && peekNextToken(1)->getIDType() == TokenID::E::id)
	{
		getNextToken();
		getNextToken();
	}


}

void Syntactic::processOper()
{

	switch (pActualtoken->getIDType())
	{
	case TokenID::E::opLogic:
	case TokenID::E::opArithmetic:
	case TokenID::E::opDimension:
	case TokenID::E::opRelational:
		getNextToken();
		return;
	}

	pStateMachine->pushError();
	getNextToken();
}

void Syntactic::processStatements()
{
	do
	{
		processStatement();
		getNextToken();
	} while (tokenIsStatement());


}

void Syntactic::processStatement()
{
	if (pActualtoken->getToken() == "return")
	{
		getNextToken();
		if (pActualtoken->getToken() != ";")
		{
			processExpresion();
			if (pActualtoken->getToken() != ";")
				pStateMachine->pushError();
		}
		else
		{
			pStateMachine->pushError(SynE::E::ReturnEmpty, "");
		}

		return;
	}
	else if (pActualtoken->getToken() == "if")
	{
		getNextToken();
		if (pActualtoken->getToken() != "(")
			insertToken(CToken("(", "agrupation", TokenID::E::agrupation));

		getNextToken();

		processExpresion();

		//getNextToken();

		if (pActualtoken->getToken() != ")")
			insertToken(CToken(")", "agrupation", TokenID::E::agrupation));
		getNextToken();
		processBlock();

		if (peekNextToken(1)->getToken() == "else")
		{
			getNextToken();
			getNextToken();
			processBlock();
		}

		return;
	}
	else if (pActualtoken->getToken() == "for") 
	{

		getNextToken();
		if(pActualtoken->getToken() != "(")
			insertToken(CToken("(", "agrupation", TokenID::E::agrupation));
		processExpresion();

		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		getNextToken();
		processExpresion();

		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		getNextToken();
		processExpresion();

		getNextToken();
		if (pActualtoken->getToken() != ")")
			insertToken(CToken("(", "agrupation", TokenID::E::agrupation));
		getNextToken();
		processBlock();
		return;
	}
	else if (pActualtoken->getToken() == "while")
	{
		getNextToken();
		if (pActualtoken->getToken() != "(")
			insertToken(CToken("(", "agrupation", TokenID::E::agrupation));

		processExpresion();
		if (pActualtoken->getToken() != ")")
			insertToken(CToken(")", "agrupation", TokenID::E::agrupation));
		getNextToken();
		processBlock();
		return;
	}
	else if (pActualtoken->getToken() == "switch")
	{
		getNextToken();
		if (pActualtoken->getToken() != "(")
			insertToken(CToken("(", "agrupation", TokenID::E::agrupation));

		getNextToken();
		if (pActualtoken->getIDType() != TokenID::E::Int)
			pStateMachine->pushError(SynE::E::SwitchInt, "");

		getNextToken();
		if (pActualtoken->getToken() != ")")
			insertToken(CToken(")", "agrupation", TokenID::E::agrupation));

		getNextToken();
		if (pActualtoken->getToken() != "{")
			insertToken(CToken("{", "agrupation", TokenID::E::agrupation));

		getNextToken();

		while (tokenIsValue() || pActualtoken->getToken() == "default")
		{
			getNextToken();
			if (pActualtoken->getToken() != ":")
			{
				pStateMachine->pushError(SynE::E::Expect, "':' on switch statement");
				errorPanic("}");
			}
			else
			{
				getNextToken();
				processBlock();
				getNextToken();
			}

		}

		if (pActualtoken->getToken() != "}")
			insertToken(CToken("}", "agrupation", TokenID::E::agrupation));

		return;

	}
	else if (pActualtoken->getToken() == "print" || pActualtoken->getToken() == "read")
	{
		getNextToken();
		if (pActualtoken->getToken() == "(")
		{
			getNextToken();
			if (pActualtoken->getIDType() == TokenID::E::id)
			{
				getNextToken();
				if (pActualtoken->getIDType() == TokenID::E::opDimension)
				{
					getNextToken();
					getNextToken();
					getNextToken();
				}
			}
			else if (pActualtoken->getIDType() == TokenID::E::String)
			{
				getNextToken();
			}
			else
			{
				pStateMachine->pushError();
				getNextToken();
			}

			if (pActualtoken->getToken() != ")")
				insertToken(CToken(")", "agrupation", TokenID::E::agrupation));
		}
		else
		{
			pStateMachine->pushError(SynE::E::Expect, "(");
		}

		return;
	}


	pStateMachine->pushError();
}

int Syntactic::processDimension()
{
	int iDim;
	getNextToken();
	if (pActualtoken->getIDType() == TokenID::E::Int)
	{
		iDim = atoi(pActualtoken->getToken().c_str());
		getNextToken();
		if (pActualtoken->getToken() != "]")
			pStateMachine->pushError(SynE::E::Expect, "]");

		getNextToken();
		return iDim;
	}
	pStateMachine->pushError();
	getNextToken();
	getNextToken();

	return 0;
}

void Syntactic::processParam()
{
	if (pActualtoken->getToken() != "(")
		pStateMachine->pushError(SynE::E::Expect, "(");

	getNextToken();

	if (pActualtoken->getToken() != ")")
		processGpoParams();

}

void Syntactic::processGpoParams()
{

	do
	{
		std::string a = peekNextToken(2)->getToken();
		if (peekNextToken(2)->getIDType() == TokenID::E::keyword)
		{
			getNextToken();
			if (pActualtoken->getToken() != ":")
				pStateMachine->pushError(SynE::E::Expect, "':'");

			getNextToken();
			if (pActualtoken->getIDType() != TokenID::E::keyword)
				pStateMachine->pushError();

			getNextToken();
			if (pActualtoken->getToken() == ";")
				getNextToken();

		}
		else if (pActualtoken->getIDType() == TokenID::E::id)
		{
			getNextToken();
			if (pActualtoken->getToken() != ",")
				pStateMachine->pushError();
		}

		if(pActualtoken->getToken() != ")")
			getNextToken();

	} while (pActualtoken->getToken() != ")");


}

void Syntactic::processBlock()
{
	if (pActualtoken->getToken() != "{")
		pStateMachine->pushError(SynE::E::Expect, "{");

	getNextToken();

	while (pActualtoken->getToken() != "}")
	{
		if (pActualtoken->getIDType() == TokenID::E::id && peekNextToken(1)->getToken() == "(")
			processCall();
		else if (pActualtoken->getIDType() == TokenID::E::id || tokenIsValue())
		{
			processExpresion();
			if (peekNextToken(1)->getToken() == ";")
				getNextToken();
			if (pActualtoken->getToken() != ";")
				pStateMachine->pushError(SynE::E::Expect, ";");
		}

		else if (pActualtoken->getToken() == "var")
			processVars();
		else if (pActualtoken->getIDType() == TokenID::E::keyword)
			processStatements();
		else if(pActualtoken->getToken() != "}")
			getNextToken();
	}
}

Syntactic::Syntactic(CFSM * pFSM)
{
	pStateMachine = pFSM;
	iRecoveredErrors = 0;
	global = true;
}

Syntactic::Syntactic()
{
}

Syntactic::~Syntactic()
{
	for (auto &it : m_nodes)
		delete it;
}