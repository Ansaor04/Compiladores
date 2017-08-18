#pragma once
#include "Token.h"
#include "GlobalNode.h"
#include "LocalNode.h"
#include <unordered_map>

class CFSM;

class Syntactic
{

	CFSM *pStateMachine;
	std::list<CToken>::iterator pActualtoken;

public:

	CToken *getActualToken() { return &(*pActualtoken); }
	std::vector<CNode*> m_nodes;
	std::string localVarName;
	bool global;
	int iRecoveredErrors;

	void insertNode(std::string &pName, int iCat, int iType, int iDim, CNode *pLocal, CNode *pNext);
	void insertToken(CToken tmpToken);
	bool tokenIsValue();
	bool tokenIsStatement();
	bool tokenIsKeywordValue();
	void getNextToken();
	void errorPanic(std::string find);
	CToken *peekNextToken(int iPeek);

	void processTokens();

	void processProgram();
	bool processMain();

	void processVars();
	void processAssign();
	void processCall();
	void processProcedure();
	void processFunction();

	void processListExpres();
	void processExpresion();
	void processOper();
	void processStatements();
	void processStatement();

	int processVarType();
	void processParam();
	void processGpoParams();
	int processDimension();
	void processBlock();



	Syntactic(CFSM * pFSM);
	Syntactic();
	~Syntactic();
};

