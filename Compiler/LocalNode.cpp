#include "LocalNode.h"


std::string CLocalNode::createStrData()
{
	std::string result = nodesCat[m_iCategory] + ',' + nodesType[m_iType] + ',';
	result += m_iDimention;
	result += ',' + m_name;

	if (pLocal != nullptr)
		result += ',' + pLocal->createStrData();
	if (pNext != nullptr)
		result += ',' + pNext->createStrData();
	return result;
}

CLocalNode::CLocalNode()
{
}


CLocalNode::~CLocalNode()
{
}
