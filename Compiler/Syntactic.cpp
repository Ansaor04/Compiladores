#include "Syntactic.h"
#include "FSM.h"

void Syntactic::processTokens()
{
	processProgram();
}

void Syntactic::processProgram()
{
	do
	{
		processVars();
	} while (pActualtoken->getToken() != "var");

	global = false;

	do 
	{
		if (pActualtoken->getToken() == "procedure")
			processFunction();
		else if (pActualtoken->getToken() == "function")
			processProcCall();
	} while (pActualtoken->getToken() != "procedure" || pActualtoken->getToken() != "function");

	processMain();
	processBlock();

}

void Syntactic::processMain()
{
	if (pActualtoken->getToken() == "main")
		pStateMachine->pushError();
	if (pActualtoken->getToken() == "(")
		pStateMachine->pushError();
	if (pActualtoken->getToken() == ")")
		pStateMachine->pushError();
}

void Syntactic::insertNode()
{
	int type;

	if (pActualtoken->getToken() == "function")
		type = NodeType::function;
	//if (pActualtoken->getToken() == "")
	//	type = NodeType::param;
	if (pActualtoken->getToken() == "procedure")
		type = NodeType::procedure;
	if (pActualtoken->getIDType() == TokenID::E::id)
		type = NodeType::var;

	m_nodes.push_back(CNode{ pActualtoken->getToken(), type, global});
}

bool Syntactic::getNextToken()
{
	synIndex++;
	if (synIndex > pStateMachine->getTokens().size())
		return false;
	pActualtoken = &pStateMachine->getTokens()[synIndex];
	return true;
}

void Syntactic::processVarType()
{
	if (pActualtoken->getIDType() != TokenID::E::Float || pActualtoken->getIDType() != TokenID::E::Int)
		pStateMachine->pushError();
	else
		insertNode();
	getNextToken();
}

void Syntactic::processVars()
{
	do
	{
		getNextToken();

		if (pActualtoken->getIDType() != TokenID::E::id)
			pStateMachine->pushError();
		else
			insertNode();
		getNextToken();
		if (pActualtoken->getIDType() == TokenID::E::opDimension && pActualtoken->getToken() == "[")
			processDimension();


	} while (pActualtoken->getToken() == ",");

	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError();
	else
		insertNode();

	getNextToken();
	processVarType();

	if (pActualtoken->getToken() != ";")
		pStateMachine->pushError();
	else
		insertNode();
}

void Syntactic::processAssign()
{
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		insertNode();

	if (pActualtoken->getIDType() == TokenID::E::opDimension && pActualtoken->getToken() == "[")
		processDimension();

	if (pActualtoken->getIDType() == TokenID::E::assign)
		pStateMachine->pushError();
	else
		insertNode();

	processExpresion();

}

void Syntactic::processProcCall()
{
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();

	if (pActualtoken->getToken() != "(")
		pStateMachine->pushError();
	else
		insertNode();

	processListExpres();

	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError();
	else
		insertNode();
}

void Syntactic::processProcedure()
{
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		insertNode();
	getNextToken();
	processParam();

	getNextToken();
	processBlock();
}

void Syntactic::processFunction()
{
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		insertNode();
	getNextToken();
	processParam();

	getNextToken();
	if (pActualtoken->getToken() != ":")
		pStateMachine->pushError();
	else
		insertNode();
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::Float || pActualtoken->getIDType() != TokenID::E::Int || pActualtoken->getIDType() != TokenID::E::String)
		pStateMachine->pushError();
	else
		insertNode();

	processBlock();
}

void Syntactic::processFunctCall()
{
	if (pActualtoken->getIDType() != TokenID::E::id)
		pStateMachine->pushError();
	else
		insertNode();

	if (pActualtoken->getToken() != "(")
		pStateMachine->pushError();
	else
		insertNode();

	processListExpres();

	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError();
	else
		insertNode();
}

void Syntactic::processListExpres()
{
	do
	{
		processExpresion();
	} while (pActualtoken->getToken() != ",");
}

void Syntactic::processExpresion()
{
	processTerm();
	getNextToken();

	if (pActualtoken->getIDType() == TokenID::E::opArithmetic || pActualtoken->getIDType() == TokenID::E::opLogic || pActualtoken->getIDType() == TokenID::E::opRelational)
		processOper();
	else
		insertNode();

	if (pActualtoken->getIDType() == TokenID::E::id || pActualtoken->getToken() == "(")
		processExpresion();
	else
		insertNode();
}

void Syntactic::processTerm()
{
	if (pActualtoken->getToken() == "(")
	{
		processExpresion();
		getNextToken();
		if (pActualtoken->getToken() != ")")
			pStateMachine->pushError();
		else
			insertNode();
		return;
	}
	else if (pActualtoken->getIDType() == TokenID::E::id)
	{
		getNextToken();
		if (pActualtoken->getIDType() == TokenID::E::opDimension)
			processDimension();
		return;
	}
	else
		processFunctCall();

}

void Syntactic::processOper()
{
	if (pActualtoken->getIDType() == TokenID::E::opLogic)
	{
		insertNode();
		getNextToken();
		return;
	}
	if (pActualtoken->getIDType() == TokenID::E::opRelational)
	{
		insertNode();
		getNextToken();
		return;
	}
	if (pActualtoken->getIDType() == TokenID::E::opDimension)
	{
		insertNode();
		getNextToken();
		return;
	}
	if (pActualtoken->getIDType() == TokenID::E::opArithmetic)
	{
		insertNode();
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
		if (pActualtoken->getToken() != ";")
			pStateMachine->pushError();
		else 
			insertNode();
		getNextToken();
	} while (pActualtoken->getIDType() == TokenID::E::id);


}

void Syntactic::processStatement()
{
	if (pActualtoken->getToken() == "return")
	{
		insertNode();
		return;
	}
	else if (pActualtoken->getToken() == "if")
	{
		insertNode();
		return;
	}
	else if (pActualtoken->getToken() == "for")
	{
		insertNode();
		return;
	}
	else if (pActualtoken->getToken() == "while")
	{
		insertNode();
		return;
	}
	else if (pActualtoken->getToken() == "switch")
	{
		insertNode();
		return;
	}
	else if (pActualtoken->getIDType() == TokenID::E::assign)
	{
		insertNode();
		return;
	}
	processFunctCall();

}

void Syntactic::processDimension()
{
	getNextToken();
	if (pActualtoken->getIDType() != TokenID::E::Int)
	{
		getNextToken();
		if (pActualtoken->getToken() != "]")
			pStateMachine->pushError();
		else 
			insertNode();
		getNextToken();
		return;
	}
	pStateMachine->pushError();
	getNextToken();
	getNextToken();
}

void Syntactic::processParam()
{
	if (pActualtoken->getToken() != "(")
		pStateMachine->pushError();
	else
		insertNode();

	processGpoParams();

	if (pActualtoken->getToken() != ")")
		pStateMachine->pushError();
	else
		insertNode();
}

void Syntactic::processGpoParams()
{
	getNextToken();
	do
	{
		if (pActualtoken->getIDType() != TokenID::E::id)
			pStateMachine->pushError();
		else 
			insertNode();
		getNextToken();
		if (pActualtoken->getToken() == ":")
			pStateMachine->pushError();
		else
			insertNode();
		getNextToken();
		if (pActualtoken->getIDType() != TokenID::E::Float || pActualtoken->getIDType() != TokenID::E::Int || pActualtoken->getIDType() != TokenID::E::String)
			pStateMachine->pushError();
		else
			insertNode();
		getNextToken();

	} while (pActualtoken->getToken() == ";");


}

void Syntactic::processBlock()
{
	if (pActualtoken->getToken() != "{")
		pStateMachine->pushError();
	else
		insertNode();

	processExpresion();

	if (pActualtoken->getToken() != "}")
		pStateMachine->pushError();
	else
		insertNode();
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