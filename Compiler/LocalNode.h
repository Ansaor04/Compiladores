#pragma once
#include "Node.h"


class CLocalNode : public CNode
{
public:
	CLocalNode *pLocal;
	CLocalNode *pNext;
	std::string createStrData();
	CLocalNode();
	~CLocalNode();
};

