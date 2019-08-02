#pragma once
#include <string>
#define TREENODEPTR  int
#define TREENULLPTR -1
using namespace std;
class OTNode
{
private:
	TREENODEPTR left;
	string title;
	string name;
	TREENODEPTR par;
	TREENODEPTR right;

public:
	OTNode();
	~OTNode();
	/*Setters*/
	void setLeft(TREENODEPTR);
	void setTitle(string);
	void setName(string);
	void setPar(TREENODEPTR);
	void setRight(TREENODEPTR);

	/*Getters*/
	TREENODEPTR getLeft();
	string getTitle();
	string getName();
	TREENODEPTR getPar();
	TREENODEPTR getRight();

	/*Returns true if node is a leaf*/
	bool isLeaf();
	/*return true if node is a root*/
	bool isRoot();

};
