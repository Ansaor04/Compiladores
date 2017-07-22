#pragma once
#include "Node.h"

class CLocalNode;

class CGlobalNode : public CNode
{
public:
	void *pVar;
	CLocalNode *pLocal;
	CGlobalNode *pNext;

	std::string createStrData();
	CGlobalNode();
	~CGlobalNode();
};

