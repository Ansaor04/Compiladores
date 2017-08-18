#pragma once

#include "Token.h"
#include "GlobalNode.h"
#include "LocalNode.h"
#include <unordered_map>
#include <map>
class CFSM;

class Semantic
{
public:
	CFSM *pStateMachine;
	std::vector<CNode*> *pNodes;
	std::vector<std::map< bool, CToken>> vecTrees;
	bool bHasReturn;
	int iReturnType;

	std::string functName;
	std::list<CToken>::iterator pActualtoken;

	void skipTo(std::string find, bool extraJump);
	void getNextToken();
	CToken * peekNextToken(int iPeek);

	bool isStatement();
	bool isCall();
	bool isAssign();
	bool isOperator();

	bool varExist();

	void checkTokens();

	void checkProgram();
	void checkMain();
	void checkFunction();
	void checkProcedure();
	void checkAsign();
	int checkCall();
	void checkDimention();
	void checkStatements();
	int checkExpresion();
	void Expresion(std::map<bool, CToken> &tree);

	bool checkVarDecl();
	void checkBlock();

	Semantic(CFSM * pFSM);
	Semantic();
	~Semantic();
};

