#include "stdafx.h"
#include "OrgTree.h"

//Constructor
OrgTree::OrgTree()
{
	arrSize = 10;
	arrayTree = new OTNode[arrSize];
}// End of constructor

 // Destructor
OrgTree::~OrgTree()
{
	delete[] arrayTree;
}// End Destructor

 /*Creates a root node for the tree. If the tree already
 has a root, the entire tree becomes a subtree of the new root. Runtime theta n*/
void OrgTree::addRoot(string newRootTitle, string newRootName)
{
	if (treeSize == 0) {
		arrayTree[0].setTitle(newRootTitle);
		arrayTree[0].setName(newRootName);
	}
	else {
		//Resize array if needed
		resize();
		// Set new root to parent of old root
		TREENODEPTR oldRoot = getRoot();
		arrayTree[oldRoot].setPar(treeSize);
		//Set leftchild to the old root. Set name and title
		arrayTree[treeSize].setLeft(oldRoot);
		arrayTree[treeSize].setTitle(newRootTitle);
		arrayTree[treeSize].setName(newRootName);
	}
	treeSize++;
	realTreeSize++;
}// ENd of addRoot

 /*Returns the number of employees in the tree. Runtime Theta 1.*/
int OrgTree::getSize()
{
	return treeSize;
}// End of getSize

 /*Returns a pointer to the root node in the tree. Runtime theta n*/
TREENODEPTR OrgTree::getRoot()
{
	TREENODEPTR root = TREENULLPTR;
	int i = 0;
	while (arrayTree[i].getPar() != TREENULLPTR) {
		i++;
	}
	root = i;
	return root;
}// End of getRoot


 /*Returns a pointer to the leftmost child of the node passed
 to the function. If the node has no children, returns TREENULLPTR. runtime theta of 1*/
TREENODEPTR OrgTree::leftMostChild(TREENODEPTR node)
{
	return arrayTree[node].getLeft();
}// End of leftMostChild

 /* Returns a pointer to the right sibling of the node passed to the function.
 If the node has no right sibling, returns TREENULLPTR. runtime theta of 1*/
TREENODEPTR OrgTree::rightSibling(TREENODEPTR node)
{
	return arrayTree[node].getRight();
}// End of rightSibling

 /* print out the subtree starting at the node pointed to by subTreeRoot.Runtime with printHelp function
 is theta of n*/
void OrgTree::printSubTree(TREENODEPTR subTreeRoot)
{
	int w = 0;
	
	printHelp(w, subTreeRoot);

}// End of printSubTree

 /*returns a TREENODEPTR to the node listing the given
 title (exact string match with the title string in a TreeNode object).
 If the title is not found, the function will return TREENULLPTR.
 For simplicity, you may assume that all titles in the company are unique.
 average runtime is theta n*/
TREENODEPTR OrgTree::find(string title)
{
	bool found = false;
	TREENODEPTR node;
	int i = 0;
	while (i < treeSize && found == false) {
		if (arrayTree[i].getTitle() == title) {
			node = i;
			found = true;
		}
		i++;
	}
	return node;
}
/*reads an organization tree from a file.
The file will contain one tree node per line, except for lines
containing only ')' characters, which mark the ends of subtrees.
 If the file is found and read successfully, this function
will return true. If the file is not found or the file is improperly formatted,
the function will return false. Runtime is theta n*/
bool OrgTree::read(string filename)
{
	TREENODEPTR temp = 0;
	string title, name;
	bool result = false;
	ifstream myfile (filename);
	if (!myfile.is_open()) {
		cerr << "Couldn't open file!" << endl;
		return 1;
	}
	else {
		while (!myfile.eof()) {
			if (myfile.peek() == ')') {
				myfile.ignore(256, '\n');
				temp = arrayTree[temp].getPar();
			}
			else {
				getline(myfile, title, ',');
				getline(myfile, name, '\n');
				if (treeSize == 0) {
					addRoot(title, name);
					temp = 0;
				}
				else {
					hire(temp, title, name);
					temp = find(title);
				}
			}
		}
	}

	return result;
}
/*write out the OrgTree to a file, using the same file format described in the read() function above.
The average runtime for this function is theta n*/
void OrgTree::write(string filename)
{
	ofstream myfile;
	myfile.open(filename);
	writeHelp(myfile, getRoot());
	myfile << ')' << endl;
}
/* Hire an employee. The employee should be added to the tree as the last child of the node pointed to by TREENODEPTR.
The average runtime for this function is theta of n.
*/
void OrgTree::hire(TREENODEPTR pp, string newTitle, string newName)
{
	//temp pointer
	TREENODEPTR temp;
	// check to resize the array
	resize();
	//If left child ptr is null
	if (arrayTree[pp].getLeft() == TREENULLPTR) {
		arrayTree[pp].setLeft(treeSize);
		arrayTree[treeSize].setName(newName);
		arrayTree[treeSize].setTitle(newTitle);
		arrayTree[treeSize].setPar(pp);
		
	}
	//If left-child is not null
	else {
		temp = arrayTree[pp].getLeft();
		while (arrayTree[temp].getRight() != TREENULLPTR) {
			temp = arrayTree[temp].getRight();
		}
		arrayTree[temp].setRight(treeSize);
		arrayTree[treeSize].setTitle(newTitle);
		arrayTree[treeSize].setName(newName);
		arrayTree[treeSize].setPar(pp);
		
	}
	realTreeSize--;
	treeSize++;
}
/*Fire the employee who's title matches the argument to this function.
If the title is found the employee's node in the tree is deleted and the
function returns true. All employees of the fired employee now work directly
for the fired employee's boss (e.g. all children of the deleted node become
children of the deleted node's parent). The average runtime for this functioon is
theta of n. */
bool OrgTree::fire(string formerTitle)
{
	bool result = false;
	TREENODEPTR fired = find(formerTitle);
	if (fired != -1 && !arrayTree[fired].isRoot()) {// if FIRED is found and not the root
		realTreeSize--;
		result = true;
		TREENODEPTR par = arrayTree[fired].getPar();
		if (fired == arrayTree[par].getLeft()) {//If fired is a leftChild
			if (arrayTree[fired].getLeft() != TREENULLPTR) {//if fired HAS a left child
				int temp = arrayTree[fired].getLeft();
				while (temp != TREENULLPTR) {//Make fired's children now its parent's children
					arrayTree[temp].setPar(par);
					temp = arrayTree[temp].getRight();
				}
				arrayTree[par].setLeft(arrayTree[fired].getLeft());
				 temp = arrayTree[fired].getLeft();
				while (temp != TREENULLPTR) {//Make fired's former sibling it right most child's right sibling
					if (arrayTree[temp].getRight() == TREENULLPTR) {
						arrayTree[temp].setRight(arrayTree[fired].getRight());
						temp = TREENULLPTR;
					}else
					temp = arrayTree[temp].getRight();
				}
			}
			else {
				arrayTree[par].setLeft(arrayTree[fired].getRight());//If fired has no children make its right sibling the left child
			}
		}
		else {
			int temp = arrayTree[par].getLeft();
			while (temp != TREENULLPTR) {
				if (arrayTree[temp].getRight() == fired) {
					arrayTree[temp].setRight(arrayTree[fired].getRight());
					temp = TREENULLPTR;
				}
				else {
					temp = arrayTree[temp].getRight();
				}
			}
			int temp2 = arrayTree[par].getLeft();
			while (temp2 != TREENULLPTR) {
				if (arrayTree[temp2].getRight() == TREENULLPTR) {
					arrayTree[temp2].setRight(arrayTree[fired].getLeft());
					temp2 = TREENULLPTR;

				}
				else {
					temp2 = arrayTree[temp2].getRight();
				}
			}
				 int temp3 = arrayTree[fired].getLeft();
				while (temp3 != TREENULLPTR) {
					arrayTree[temp3].setPar(par);
					temp3 = arrayTree[temp3].getRight();
				}
					
			

		}
		arrayTree[fired].setTitle(" ");
		arrayTree[fired].setName(" ");
		arrayTree[fired].setLeft(TREENULLPTR);
		arrayTree[fired].setRight(TREENULLPTR);
	}
	return result;
}//end fire

void OrgTree::resize()
{
	if (treeSize == arrSize) {
		arrSize = arrSize * 2;
		OTNode* newArray = new OTNode[arrSize];
		for (int i = 0; i < treeSize; i++) {
			newArray[i] = arrayTree[i];
		}
		arrayTree = newArray;
		newArray = NULL;
		delete newArray;
	}//end resize
}
// Recursive preorder print method. Average runtime is theta n
void OrgTree::printHelp(int w, TREENODEPTR ptr)
{
	
	//Print the Node
	cout.width(w);
	cout << right << " " << arrayTree[ptr].getTitle() << ", " << arrayTree[ptr].getName() << endl;
	if (!arrayTree[ptr].isLeaf()) {
		TREENODEPTR temp = arrayTree[ptr].getLeft();
		while (temp != TREENULLPTR) {
			int	widthAdjust = 10;
			printHelp(w + widthAdjust, temp);
			temp = arrayTree[temp].getRight();

		}

	}
}
/*/Helper preorder traversal functioon for the write function. Theta n*/
void OrgTree::writeHelp(ofstream& myfile, TREENODEPTR ptr)
{
	myfile << arrayTree[ptr].getTitle() << ", " << arrayTree[ptr].getName() << endl;
	if (!arrayTree[ptr].isLeaf()) {
		TREENODEPTR temp = arrayTree[ptr].getLeft();
		while (temp != TREENULLPTR) {
			
			writeHelp(myfile, temp);
			myfile << ')' << endl;
			temp = arrayTree[temp].getRight();

		}
		
	}
	

}