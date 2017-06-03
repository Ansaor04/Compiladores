#pragma once
#include <string>

class CFSM;

namespace States
{
	enum E
	{
		Reading = 0,
		Variable,
		Procedure,
		Function,
		Comment,
		Assign,
		Constant,
		Delimitator,
		Reserved,
		Agrupation,
		OpAritmetic,
		OpLogic,
		OpRelational,

		Error
	};
}


bool isDigit(char &a);
bool isLetter(char &a);
bool isAlphanumeric(char &a);
bool stringCompare(std::string str, char * pcSource);

class CState
{
public:
	CFSM * pStateMachine;
	int iNextState;
	const std::string keyWords[6] = { " ", "var ", "procedure ", "function ", "/*" , "=" };
	const std::string reservedWords[11] = { "float", "int", "string", "bool", "main", "for", "while", "if", "else", "switch", "return" };
	const std::string operatorAritmetic[6] = { "+", "-", "*", "/", "%", "^"};
	const std::string operatorLogic[3] = { "&&", "||", "!"};
	const std::string operatorRelational[6] = { "==", "<=", ">=", "!=", "<", ">" };	
	virtual void onEnter() = 0;
	virtual void onExit() = 0;
	//CState();
	//virtual ~CState();
};
