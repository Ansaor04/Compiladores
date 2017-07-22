#include "Syntactic.h"
#include "FSM.h"

bool Syntactic::tokenIsValue()
{
	//if (pActualtoken->getToken() == "float" || pActualtoken->getToken() == "int" || pActualtoken->getToken() == "string")
	//	return true;
	if (pActualtoken->getIDType() == TokenID::E::Float || pActualtoken->getIDType() == TokenID::Int || pActualtoken->getIDType() == TokenID::E::String)
		return true;
	return false;
}

void Syntactic::insertNode(std::string &pName, int iCat, int iType, int iDim, CNode *pLocal, CNode *pNext)
{
	return;

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

	m_nodes.push_back(pActualNode);
	pStateMachine->symbolTable << pActualNode->createStrData() << '\n';

	delete pActualNode;
}

#define MAXTYPES 8

void Syntactic::getNextToken()
{
	synIndex++;
	if (synIndex > pStateMachine->getTokens().size())
		pActualtoken = nullptr;
	else
		pActualtoken = &pStateMachine->getTokens()[synIndex];
}

void Syntactic::processTokens()
{
	pActualtoken = &pStateMachine->getTokens()[0];
	processProgram();
}

void Syntactic::processProgram()
{
		
	do 
	{
		if (pActualtoken->getToken() == "procedure")
			processProcedure();
		else if (pActualtoken->getToken() == "function")
			processFunction();
		else if(pActualtoken->getToken() == "var")
			processVars();
	} while (pActualtoken->getToken() == "procedure" || pActualtoken->getToken() == "function" || pActualtoken->getToken() == "var");

	global = false;

	processMain();
	processBlock();

}

void Syntactic::processMain()
{
	if (pActualtoken->getToken() != "main")
		pStateMachine->pushError();
	getNextToken();
	if (pActualtoken->getToken() != "(")
		pStateMachine->pushError();
	getNextToken();
	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError();
	getNextToken();
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
		if (pActualtoken->getIDType() == TokenID::E::opDimension && pActualtoken->getToken() == "[")
			iDim[iVarNum] = processDimension();
		iVarNum++;

	} while (pActualtoken->getToken() == ",");

	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError();

	getNextToken();
	iType = processVarType() - MAXTYPES;

	for (int i = 0; i < iVarNum; i++)
		insertNode(names[i], global, iType, iDim[i], nullptr, nullptr);

	if (pActualtoken->getToken() != ";")
		pStateMachine->pushError();
}

void Syntactic::processAssign()
{
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();

	if (pActualtoken->getIDType() == TokenID::E::opDimension && pActualtoken->getToken() == "[")
		processDimension();

	if (pActualtoken->getIDType() == TokenID::E::assign)
		pStateMachine->pushError();

	processExpresion();

}


void Syntactic::processProcedure()
{
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();

	insertNode(pActualtoken->getToken(), nodesCat::E::procedure, -1, 0, nullptr, nullptr);

	getNextToken();
	processParam();

	getNextToken();
	processBlock();
	getNextToken();
}

void Syntactic::processFunction()
{
	std::string name;

	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();

	name = pActualtoken->getToken();

	getNextToken();
	processParam();

	getNextToken();
	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError();

	getNextToken();
	if (pActualtoken->getToken() != "float" || pActualtoken->getToken() != "int" || pActualtoken->getToken() != "string")
		pStateMachine->pushError();

	insertNode(name, nodesCat::E::procedure, pActualtoken->getIDType() - MAXTYPES, 0, nullptr, nullptr);

	processBlock();
}

//void Syntactic::processProcCall()
//{
//	if (pActualtoken->getIDType() != TokenID::E::id)
//		pStateMachine->pushError();
//
//	getNextToken();
//
//	if (pActualtoken->getToken() != "(")
//		pStateMachine->pushError();
//
//	processListExpres();
//	getNextToken();
//
//	if (pActualtoken->getToken() != ")")
//		pStateMachine->pushError();
//
//}

void Syntactic::processCall()
{
	//if (pActualtoken->getIDType() != TokenID::E::id)
	//	pStateMachine->pushError();
	//getNextToken();
	//if (pActualtoken->getToken() != "(")
	//	pStateMachine->pushError();

	processListExpres();
	getNextToken();

	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError();

}

void Syntactic::processListExpres()
{
	getNextToken();
	do
	{
		processExpresion();
		getNextToken();
	} while (pActualtoken->getToken() == ",");
}

void Syntactic::processExpresion() //
{
	getNextToken();
	if (pActualtoken->getIDType() == TokenID::E::id || tokenIsValue())
	{
		getNextToken();
		if (pActualtoken->getIDType() == TokenID::E::opArithmetic || pActualtoken->getIDType() == TokenID::E::opLogic || pActualtoken->getIDType() == TokenID::E::opRelational || pActualtoken->getIDType() == TokenID::E::assign)
		{
			processOper();
			if (pActualtoken->getToken() == "(")
			{
				processExpresion();
				getNextToken();
				if (pActualtoken->getToken() != ")")
					pStateMachine->pushError();
			}
			else
			{
				if (!tokenIsValue())
					pStateMachine->pushError();
				else if (pActualtoken->getIDType() != TokenID::E::id)
					pStateMachine->pushError();
			}
		}
		else if (pActualtoken->getToken() == "(")
			processCall();
		return;
	}
	//processTerm();

}

void Syntactic::processTerm() //
{
	//if (pActualtoken->getToken() == "(")
	//{
	//	processExpresion();
	//	getNextToken();
	//	if (pActualtoken->getToken() != ")")
	//		pStateMachine->pushError();
	//	return;
	//}
	//else if (pActualtoken->getIDType() == TokenID::E::id)
	//{
	//	getNextToken();
	//	if (pActualtoken->getIDType() == TokenID::E::opDimension)
	//		processDimension();
	//	return;
	//}
	//else
	//	processFunctCall();

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
	} while (pActualtoken->getIDType() == TokenID::E::keyword);


}

void Syntactic::processStatement()
{
	if (pActualtoken->getToken() == "return")
	{
		getNextToken();
		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		return;
	}
	else if (pActualtoken->getToken() == "if")
	{
		getNextToken();
		if (pActualtoken->getToken() != "(")
			pStateMachine->pushError();

		processExpresion();
		getNextToken();
		if (pActualtoken->getToken() != ")")
			pStateMachine->pushError();
		getNextToken();
		processBlock();

		return;
	}
	else if (pActualtoken->getToken() == "for") 
	{

		getNextToken();
		processExpresion();
		getNextToken();
		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		getNextToken();
		processExpresion();
		getNextToken();
		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		getNextToken();
		processExpresion();

		getNextToken();
		if (pActualtoken->getToken() != ")")
			pStateMachine->pushError();
		getNextToken();
		processBlock();
		return;
	}
	else if (pActualtoken->getToken() == "while")
	{
		getNextToken();
		if (pActualtoken->getToken() != "(")
			pStateMachine->pushError();

		processExpresion();
		getNextToken();
		if (pActualtoken->getToken() != ")")
			pStateMachine->pushError();
		getNextToken();
		processBlock();
		return;
	}
	else if (pActualtoken->getToken() == "switch")
	{
		return;
	}

	pStateMachine->pushError();
}

int Syntactic::processDimension()
{
	int iDim;
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::Int)
	{
		iDim = atoi(pActualtoken->getToken().c_str());
		getNextToken();
		if (pActualtoken->getToken() != "]")
			pStateMachine->pushError();

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
		pStateMachine->pushError();

	getNextToken();

	if (pActualtoken->getToken() != ")")
		processGpoParams();

}

void Syntactic::processGpoParams()
{
	getNextToken();
	do
	{
		if (pActualtoken->getIDType() != TokenID::E::id)
			pStateMachine->pushError();

		getNextToken();
		if (pActualtoken->getToken() == ":")
			pStateMachine->pushError();

		getNextToken();
		if (pActualtoken->getIDType() != TokenID::E::Float || pActualtoken->getIDType() != TokenID::E::Int || pActualtoken->getIDType() != TokenID::E::String)
			pStateMachine->pushError();

		getNextToken();

	} while (pActualtoken->getToken() == ";");


}

void Syntactic::processBlock()
{
	if (pActualtoken->getToken() != "{")
		pStateMachine->pushError();

	getNextToken();

	while (pActualtoken->getToken() != "}")
	{
		if (pActualtoken->getIDType() == TokenID::E::id || tokenIsValue())
		{
			processExpresion();
			getNextToken();
			if (pActualtoken->getToken() != ";")
				pStateMachine->pushError();
		}

		else if (pActualtoken->getToken() == "var")
			processVars();
		else if (pActualtoken->getIDType() == TokenID::E::keyword)
			processStatements();

		getNextToken();
	}
}

Syntactic::Syntactic(CFSM * pFSM)
{
	pActualtoken = nullptr;
	pStateMachine = pFSM;
	synIndex = 0;
	global = true;
}

Syntactic::Syntactic()
{
}

Syntactic::~Syntactic()
{
}