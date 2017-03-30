#include "stdafx.h"
#include <iostream>
#include "HNTreeNode.h"
using namespace std;

string HNTreeNode::getCharacter() const 
{
	return m_character;
}

HNTreeNode::HNTreeNode(string character,int Length)
{
	if (character.size() == Length)
		m_character.assign(character);
	else 
		cout<<"error";
}

HNTreeNode* HNTreeNode::findChild(string& nextCharacter)
{
	_TreeMapIterator TreeMapIt = m_map.find(nextCharacter);    //����map/unordered_map���в���
	return (TreeMapIt == m_map.end()) ? NULL :&TreeMapIt->second;
	return NULL;
}

HNTreeNode* HNTreeNode::insertChild(string& nextCharacter,int Length)
{
	if(!findChild(nextCharacter))    //��ӽڵ㣬�����ؽڵ�λ��
	{
		m_map.insert(pair<string, HNTreeNode>(nextCharacter, HNTreeNode(nextCharacter,Length)));
		return &(m_map.find(nextCharacter)->second);
	}
	return NULL;
}

