#include "Token.h"

void CToken::setType( int iTokenType)
{
	m_iType = iTokenType;

	switch (iTokenType)
	{
	case TokenID::E::id:
		m_type = "id";
		break;
	case TokenID::E::delimitator:
		m_type = "delimitator";
		break;
	case TokenID::E::opDimension:
		m_type = "dimension operator";
		break;
	case TokenID::E::opLogic:
		m_type = "logic operator";
		break;
	case TokenID::E::opArithmetic:
		m_type = "arithmetic operator";
		break;
	case TokenID::E::opRelational:
		m_type = "relational operator";
		break;
	case TokenID::E::assign:
		m_type = "assignation";
		break;
	case TokenID::E::agrupation:
		m_type = "agrupation";
		break;
	case TokenID::E::keyword:
		m_type = "keyword";
		break;
	case TokenID::E::Int:
		m_type = "int";
		break;
	case TokenID::E::Float:
		m_type = "float";
		break;
	case TokenID::E::String:
		m_type = "string";
		break;
	case TokenID::E::Bool:
		m_type = "bool";
		break;
	}
}

CToken::CToken(std::string data, std::string type, int iType)
{
	m_phrase = data;
	m_type = type;
	m_iType = iType;
}

CToken::CToken()
{
}


CToken::~CToken()
{
}
