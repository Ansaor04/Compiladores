#pragma once
#include <string>

namespace NodeType
{
	enum E 
	{
		var = 0,
		function,
		procedure,
		param,
	};
}

struct CNode
{
	std::string name;
	int type;
	bool local;

};

