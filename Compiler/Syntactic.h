#pragma once
#include "Token.h"
#include "Node.h"
#include <vector>

class CFSM;

class Syntactic
{
	CToken *pActualtoken;
	CFSM *pStateMachine;
	int synIndex;

	bool global;
public:

	CToken *getActualToken() { return pActualtoken; }
	std::vector<CNode> m_nodes;
	void insertNode();

	bool getNextToken();
	void processTokens();

	void processProgram();
	void processMain();

	void processVars();
	void processAssign();
	void processProcCall();
	void processProcedure();
	void processFunction();
	void processFunctCall();

	void processListExpres();
	void processExpresion();
	void processTerm();
	void processOper();
	void processStatements();
	void processStatement();

	void processVarType();
	void processParam();
	void processGpoParams();
	void processDimension();
	void processBlock();

	Syntactic(CFSM * pFSM);
	Syntactic();
	~Syntactic();
};

