#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "OtNode.h"
#define TREENODEPTR  int
#define TREENULLPTR -1
/*This general tree is implemented with an array. the highest runtime for any operation is theta
n. The overhead for this tree is (5/2n)n (2n being the title and name for the position)*/
using namespace std;
class OrgTree
{
private:
	unsigned int treeSize;
	unsigned int arrSize;
	OTNode* arrayTree;
	void resize();
	void printHelp(int, TREENODEPTR);
	void writeHelp(ofstream&, TREENODEPTR);
	int realTreeSize;
public:
	OrgTree();
	void addRoot(string, string);
	int getSize();
	TREENODEPTR getRoot();
	TREENODEPTR leftMostChild(TREENODEPTR);
	TREENODEPTR rightSibling(TREENODEPTR);
	void printSubTree(TREENODEPTR);
	TREENODEPTR find(string);//next function to define
	void hire(TREENODEPTR, string, string);
	bool read(string);
	void write(string);
	bool fire(string);
	
	//TODO DEFINE READ/WRITE FUNCTIONS

	~OrgTree();

};


