#pragma once
#include "Reading.h"
#include "Variable.h"
#include "Procedure.h"
#include "Function.h"
#include "Coment.h"
#include "Assign.h"
#include "Constant.h"
#include "Delimitator.h"
#include "Reserved.h"
#include "Agrupation.h"
#include "OpAritmetic.h"
#include "OpLogic.h"
#include "OpRelational.h"
#include "Error.h"
#include "Token.h"
#include "Syntactic.h"
#include <fstream>
#include <vector>

namespace CompilerPhase
{
	enum E
	{
		lexic = 0,
		syntactic,
		semantic,
	};
}

class CFSM
{
private:
	CState *m_pActualState;
	CReading Read;
	CVariable Var;
	CProcedure Proc;
	CFunction Funct;
	CComent Coment;
	CAssign Assign;
	CConstant Const;
	CDelimitator Delim;
	CReserved Reser;
	CAgrupation Agrup;
	COpAritmetic Arit;
	COpLogic Logic;
	COpRelational Relat;
	CError Error;



	CState *m_States[14] = { &Read, &Var, &Proc, &Funct, &Coment, &Assign, &Const, &Delim, &Reser, &Agrup, &Arit, &Logic, &Relat, &Error};

	std::vector<int> m_Stack;
	std::vector<CToken> m_Tokens;
	std::string filename;



public:
	int iLine, iNumPhase;
	bool bHasErrors;
	std::ofstream lexFile, symbolTable, syntactic, errorFile;
	Syntactic *Syn;
	CToken tmpToken;

	char *pChar;
	void update();
	void pushState(int iState);
	void popState();
	void pushString();
	void pushChar();
	void pushError();
	void openFile(int iType);
	void closeFile();

	void setMode(int iType);
	std::vector<CToken> &getTokens() { return m_Tokens; }

	CFSM();
	~CFSM();
};

