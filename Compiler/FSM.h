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
#include "Semantic.h"
#include <fstream>
#include <vector>
#include <list>

namespace CompilerPhase
{
	enum E
	{
		lexic = 0,
		syntactic,
		semantic,
	};
}

namespace SynE
{
	enum E
	{
		DefVar = 0,
		Expect,
		NoMain,
		SwitchInt,
		ReturnEmpty,
		RetFunction,
		DimensionArray,
		VarNotDefined,
		WrongReturn,
		IncompAssign,
		ReturnMismatch,
		statementBool,
		statementNonBool,
		arrayNegative,
		noExpresion,
		custom,
		undeclared,
	};
}

#define MAXTYPES 8		//para construir la tabla de simbolos

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
	std::list<CToken> m_Tokens;

public:
	int iLine, iNumPhase;
	bool bHasErrors;
	std::ofstream lexFile, symbolTable, syntactic, errorFile;
	std::string filename;
	Syntactic *Syn;
	Semantic *Sem;
	CToken tmpToken;

	char *pChar;
	void update();
	void pushState(int iState);
	void popState();
	void pushString();
	void pushChar();
	void pushError();
	void pushError(int iError, std::string info);
	void openFile(int iType);
	void closeFile();

	void setMode(int iType);
	void reset();
	std::list<CToken> &getTokens() { return m_Tokens; }

	CFSM();
	~CFSM();
};

