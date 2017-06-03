#pragma once
#include <string>

namespace TokenID
{
	enum  E
	{
		id = 0,
		delimitator,
		opDimension,
		opLogic,
		opArithmetic,
		opRelational,
		assign,
		agrupation,
		keyword,
		Int,
		Float,
		String
	};
}

class CToken
{

	std::string m_phrase;
	std::string m_type;
public:
	void setType(int iTokenType);
	void clearToken() { m_phrase.clear(); m_type.clear(); }
	std::string &getType() { return m_type; }
	std::string &getToken() { return m_phrase; }
	CToken();
	~CToken();
};

