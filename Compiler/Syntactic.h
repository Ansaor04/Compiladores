#pragma once
#include "Token.h"
#include "GlobalNode.h"
#include "LocalNode.h"
#include <unordered_map>

class CFSM;

class Syntactic
{
	CToken *pActualtoken;
	CFSM *pStateMachine;
	int synIndex;

	bool global;
public:

	CToken *getActualToken() { return pActualtoken; }
	//std::unordered_map<NodeHash,CNode, int> m_nodes;
	std::vector<CNode*> m_nodes;

	void insertNode(std::string &pName, int iCat, int iType, int iDim, CNode *pLocal, CNode *pNext);
	bool tokenIsValue();
	void getNextToken();


	void processTokens();

	void processProgram();
	void processMain();

	void processVars();
	void processAssign();
	void processCall();
	void processProcedure();
	void processFunction();
	//void processFunctCall();

	void processListExpres();
	void processExpresion();
	void processTerm();
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

