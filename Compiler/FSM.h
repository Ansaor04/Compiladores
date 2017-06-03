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
#include <fstream>
#include <vector>

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
	std::ofstream lexFile;
	std::vector<int> m_Stack;
public:
	CToken actualToken;
	char *pChar;
	void update();
	void pushState(int iState);
	void popState();
	void pushString();
	void pushChar();
	void openFile(char * pfilename);
	void closeFile();
	CFSM();
	~CFSM();
};

