#include "GlobalNode.h"
#include "LocalNode.h"



std::string CGlobalNode::createStrData()
{
	std::string result = m_name + ',' + nodesCat[m_iCategory] + ',' + nodesType[m_iType] + ',';
	result += m_iDimention;
	result += ", null,";
	if (pLocal != nullptr)
		result += ',' + pLocal->createStrData();
	if (pNext != nullptr)
		result += ',' + pNext->createStrData();
	return result;
}

CGlobalNode::CGlobalNode()
{
}


CGlobalNode::~CGlobalNode()
{
}
