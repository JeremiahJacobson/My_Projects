#include "stdafx.h"
#include "OtNode.h"


OTNode::OTNode()
{
	left = TREENULLPTR;
	title = " ";
	name = " ";
	par = TREENULLPTR;
	right = TREENULLPTR;
}


OTNode::~OTNode()
{
}
//////////SETTERS/////////
void OTNode::setLeft(TREENODEPTR lc)
{
	left = lc;
}

void OTNode::setTitle(string t)
{
	title = t;
}

void OTNode::setName(string n)
{
	name = n;
}

void OTNode::setPar(TREENODEPTR p)
{
	par = p;
}

void OTNode::setRight(TREENODEPTR r)
{
	right = r;
}
///////////////GETTERS//////////////
TREENODEPTR OTNode::getLeft()
{
	return left;
}

string OTNode::getTitle()
{
	return title;
}

string OTNode::getName()
{
	return name;
}

TREENODEPTR OTNode::getPar()
{
	return par;
}

TREENODEPTR OTNode::getRight()
{
	return right;
}
/////////////ISLEAF/////////////////////////
bool OTNode::isLeaf()
{
	bool result = true;
	if (left != TREENULLPTR) {
		result = false;
	}
	return result;
}

bool OTNode::isRoot()
{
	bool result = false;
	if (getPar() == TREENULLPTR) {
		result = true;
	}
	return result;
}
