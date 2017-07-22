#pragma once
#include <string>

namespace nodesType
{
	enum E
	{
		Int = 0,
		Float,
		String,
		Bool
	};
}

namespace nodesCat
{
	enum E
	{
		local = 0,
		global,
		function,
		procedure
	};
}

class CNode
{
public:
	std::string nodesCat[4] = { "global","local","function","procedure" };
	std::string nodesType[5] = { "NULL", "int","float","string","bool" };

	std::string m_name;
	int m_iCategory;
	int m_iType;
	int m_iDimention;
	virtual std::string createStrData() = 0;
};

struct NodeHash
{
	size_t operator()(const CNode& A) const
	{
		return std::hash<std::string>()(A.m_name) ^ std::hash<std::string>()(A.nodesCat[A.m_iCategory]);
	}
};