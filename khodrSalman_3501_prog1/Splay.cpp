
#include "Header.h"

//Program Name: CIS 3501 Program 1
//Programmer Name: Khodr Salman
//Description: Create a BST, AVL, and Splay tree and run various operations on them to compare operations 
//Date Created: 2/21/21

/*
Description: This function returns the insert operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int Splay::getSplayInsertOps()
{
	return SplayInsertOp;
}
/*
Description: This function returns the search operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int Splay::getSplaySearchOps()
{
	return SplaySearchOp;
}

/*
Description: This function returns the delete operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int Splay::getSplayDeleteOps()
{
	return SplayDeleteOp;
}
/*
Description: This function clears the operation varibales for the splay class
Pre-condition: the operations must exist in the class
Post-condition: The operation varibales are reset
*/
void Splay::clearALL_SplayOps()
{
	SplayInsertOp = 0;
	SplaySearchOp = 0;
	SplayDeleteOp = 0;
}


/*
Description: This function creates a new node using digit/number passed in
Pre-condition: digit/number be set equal to a node pointer
Post-condition: a new empty node is created contsining the digit/number passed in
*/
node* Splay::newNode(int digit)
{
	node* temp = new node;
	temp->value = digit;
	temp->left = nullptr;
	temp->right = nullptr;
	temp->height = 0;
	temp->twin = 1;	//sets twin equal to one because there is one of it
	temp->parent = nullptr;

	return temp;
}

/*
Description: This function takes a digit and inserts it into the splay tree while calling other functions to splay it
Pre-condition: a valid digit must be sent in from the user with the correct action code
Post-condition: the digit is inserted into the tree and splayed using rotations
*/
void Splay::insertSplay(int key, ofstream& outFile)
{
	node* temp;
	node* curr;
	if (root == nullptr) //tree is empty
	{
		temp = newNode(key); //creates a new node
		root = temp;
		SplayInsertOp++;
		treeOperations[1][2]++;
		return;
	}
	curr = root;
	while (curr != nullptr) //loops through the tree finding its position
	{
		if (key < curr->value)
		{
			if (curr->left == nullptr) //position is found
			{
				SplayInsertOp++;
				treeOperations[1][2]++;
				temp = newNode(key);
				curr->left = temp;
				temp->parent = curr;
				splay(temp, 'I', outFile);
				return;
			}
			else {
				curr = curr->left; //moves to the left child
			}
		}
		else if (key > curr->value)
		{
			if (curr->right == nullptr) //position is found
			{
				SplayInsertOp++;
				treeOperations[1][2]++;
				temp = newNode(key);
				curr->right = temp;
				temp->parent = curr;
				splay(temp, 'I', outFile);
				return;
			}
			else { //moves to the right child
				curr = curr->right;
			}
		}
		else if (key == curr->value) //theres a twin
		{
			curr->twin++; //twin is incramented
			if (key == root->value)
				return;
			else
			{
				splay(curr, 'I', outFile); //splays the value
				return;
			}

		}
		else {
			splay(curr, 'I', outFile); //splays the last value anyways
			return;

		}

	}
	Splaytree_LevelAndPrint(root, outFile); //calls the printing function
}
/*
Description: This function calls uses the height function to print the tree, once height is obtained it uses it to space the digits away from eachother properly
Pre-condition: A pointer to the root must be passed in
Post-condition: The tree is printed using the height for the spacing
*/
void Splay::Splaytree_LevelAndPrint(node* root, ofstream& outFile)
{
	int h = getHeight(root);
	cout << "\n HEIGHT IN SPLAY TREE IS NOW -> " << h << endl;
	outFile << "\n HEIGHT IN SPLAY TREE IS NOW -> " << h << endl;
	int c = h * 2;


	for (int i = 1; i <= h; i++)	//loop through each level
	{
		outFile << endl;	//print new line every level
		cout << endl;
		Splay_PrintOneLevel(root, i, c, outFile);
	}
}
/*
Description: This function prints the tree one level (L) at a time
Pre-condition: a pointer to the root must exist
Post-condition: the tree is printed
*/
void Splay::Splay_PrintOneLevel(node* root, int L, int space, ofstream& outFile)
{
	if (root == nullptr)	
	{
		for (int i = 0; i < space + 1; i++)
		{
			outFile << " ";
			cout << " ";
		}
		return;
	}
	if (L == 1)	//base case, print the node
	{
		for (int i = 0; i < space; i++)	//correct spacing
		{
			outFile << " ";
			cout << " ";
		}
		outFile << root->value;
		cout << root->value;
		if (root->twin > 1) {
			outFile << "(" << root->twin << ")";
			cout << "(" << root->twin << ")";
		}
			
	}
	else if (L > 1)
	{
		Splay_PrintOneLevel(root->left, L - 1, space / 2, outFile);	//recursively call by sending right pointer, one less level, and spacing/2
		Splay_PrintOneLevel(root->right, L - 1, space - 1, outFile);	//recursively call by sending left pointer, one less level, and spacing -1	
	}
}
/*
Description: This function splays the pointer passed - calls correct rotation function 
Pre-condition: a pointer to the node that needs splaying it passed in
Post-condition: the node is splayed using rotations that it needs
*/
void Splay::splay(node* ptr, char C, ofstream& outFile)
{
	node* parent;
	node* grandparent;
	while (ptr->parent != nullptr)
	{
		parent = ptr->parent;
		grandparent = parent->parent;

		if (grandparent == nullptr)
		{
			outFile << "splay rotations ";
			cout << "splay rotations  ";
			zig(ptr, C, outFile); //does a left or right rotation
			return;
		}
		else if (grandparent->left == parent && parent->left == ptr)
		{
			outFile << "splay rotations  ";
			cout << "splay rotations  ";
			zigzig(ptr, C, outFile); // does a left/left or right/right rotation
		}
		else if (grandparent->right == parent && parent->right == ptr)
		{
			outFile << "splay rotations ";
			cout << "splay rotations  ";
			zigzig(ptr, C, outFile); 
		}
		else {
			outFile << "splay rotations  ";
			cout << "splay rotations  ";
			zigzag(ptr, C, outFile); //does a left/right or right/left rotation

		}
		root = ptr; //sets the root


	}


}
/*
Description: This functions gets the height of the tree
Pre-condition: a pointer to the node must be sent in and the tree must exist
Post-condition: The height is returned
*/
int Splay::getHeight(node* ptr)
{
	int left, right;
	if (ptr == nullptr) {
		return 0;
	}
	else {
		left = getHeight(ptr->left);
		ptr->left = nullptr; //had to do this due to stack overflow, if commented out it could cause logic error and stack overflow. 
							//essentially im saying once we finish with the left side, leave it null and do the right side 
		right = getHeight(ptr->right);
	}
	return left < right ? right + 1 : left + 1;
}



/*
Description: This function does a zig (left) or zag(right) rotation on the pointer thats passed in
Pre-condition: The pointer needs to have a zig/zag condition
Post-condition: The zig/zag rotation is done on the pointer
*/
void Splay::zig(node* ptr, char C, ofstream& outFile)
{
	node* parent;
	node* leftChild;
	node* rightChild;
	node* sibling;

	parent = ptr->parent;
	if (parent->left == ptr) //does a right rotation
	{
		outFile << "zag- " << endl;
		cout << "zag- " << endl;
		leftChild = ptr->left;
		rightChild = ptr->right;
		sibling = parent->right;

		//switches the values to make the rotation
		ptr->parent = nullptr;
		ptr->right = parent;
		parent->parent = ptr;
		parent->left = rightChild;

		root = ptr;

		if (rightChild != nullptr)
		{
			rightChild->parent = parent;
		}
	}
	else //does a left rotation
	{
		//switched the values to make the rotation
		outFile << "zig- " << endl;
		cout << "zig- " << endl;
		leftChild = ptr->left;
		rightChild = ptr->right;
		sibling = parent->left;

		ptr->parent = nullptr;
		ptr->left = parent;
		parent->parent = ptr;
		parent->right = leftChild;

		root = ptr; //sets the root

		if (rightChild != nullptr)
		{
			rightChild->parent = parent;
		}
	}

	//incraments the operations depending on the action code
	if (C == 'I') {
		SplayInsertOp++;
		treeOperations[1][2]++;
		cout << " Insert operation found in Splay::zig -- SplayInsertOp is now --> " << SplayInsertOp;
	}
	if (C == 'D') {
		SplayDeleteOp++;
		treeOperations[2][2]++;
		cout << " delete operation found in Splay::zig -- SplayDeleteOp is now --> " << SplayDeleteOp;
	}
	if (C == 'S') {
		treeOperations[0][2]++;
		SplaySearchOp++;
		cout << " search operation found in Splay::zig -- SplaySearchOp is now --> " << SplaySearchOp;
	}
	
}


/*
Description: This function does double left rotation or double right roation on the pointer thats passed in
Pre-condition : The pointer needs to be sent in from the splay function
Post-condition : The rotation is done on the pointer
*/
void Splay::zigzig(node* ptr, char C, ofstream& outFile) //there is something wrong with this function but i dongt know wha ti is yet 
{
	node* parent;
	node* grandparent;
	node* temp1, * temp2, * temp3, * temp4;

	parent = ptr->parent;
	grandparent = parent->parent;

	if (parent->left == ptr) //does a right rotation
	{
		outFile << "zag- ";
		cout << "zag- ";
		temp1 = ptr->left;
		temp2 = ptr->right;
		temp3 = parent->right;
		temp4 = grandparent->right;

		ptr->parent = grandparent->parent;
		ptr->right = parent;
		//switches the nodes to make the rotation
		parent->parent = ptr;
		parent->left = temp2;
		parent->right = grandparent;
		grandparent->parent = parent;
		grandparent->left = temp3;

		//the parent is empty
		if (ptr->parent != nullptr)
		{
			if (ptr->parent->left == grandparent)
			{
				ptr->parent->left = ptr;
			}
			else
			{
				ptr->parent->right = ptr;
			}
		}

		if (temp2 != nullptr)
			temp2->parent = parent;
		if (temp3 != nullptr)
			temp3->parent = grandparent;
	}
	else //does a left rotation
	{
		outFile << "zig- ";
		cout << "zig- ";
		temp1 = grandparent->left;
		temp2 = parent->left;
		temp3 = ptr->left;
		temp4 = ptr->right;

		ptr->parent = grandparent->parent;
		ptr->left = parent;
		//switches around the nodes to make that rotation

		parent->parent = ptr;
		parent->left = grandparent;
		parent->right = temp3;
		grandparent->parent = parent;
		grandparent->right = temp2;

		if (ptr->parent != nullptr)
		{
			if (ptr->parent->left == grandparent)
			{
				ptr->parent->left = ptr;
			}
			else
			{
				ptr->parent->right = ptr;
			}
		}

		if (temp2 != NULL)
			temp2->parent = grandparent;
		if (temp3 != NULL)
			temp3->parent = parent;
	}
	//incraments the operation depending on the action code
	if (C == 'I') {
		SplayInsertOp++;
		treeOperations[1][2]++;
		cout << " Insert operation found in Splay::zigzig -- SplayInsertOp is now --> " << SplayInsertOp;
	}
	if (C == 'S') {
		SplaySearchOp++;
		treeOperations[0][2]++;
		cout << " search operation found in Splay::zigzig -- SplaySearchOp is now --> " << SplaySearchOp;
	}
	if (C == 'D') {
		SplayDeleteOp++;
		treeOperations[2][2]++;
		cout << " delete operation found in Splay::zigzig -- SplayDeleteOp is now --> " << SplayDeleteOp;
	}
	root = ptr;

}


/*
Description: This function does a left-right or right-left rotation on the pointer thats passed in
Pre-condition : The pointer needs to be sent in from the splay function
Post-condition : The rotation is done on the pointer
*/
void Splay::zigzag(node* ptr, char code, ofstream& print)
{
	node* temp1, * temp2, * temp3, * temp4;
	node* parent = ptr->parent;
	node* grandparent = parent->parent;

	if (parent->right == ptr) //does a right left rotation
	{
		print << "zag-zig - ";
		cout << "zag-zig - ";
		temp1 = parent->left;
		temp2 = ptr->left;
		temp3 = ptr->right;
		temp4 = grandparent->right;

		ptr->parent = grandparent->parent;
		ptr->left = parent;
		ptr->right = grandparent;

		//the double rotation 
		parent->parent = ptr;
		parent->right = temp2;
		//sets new node and parent
		grandparent->parent = ptr;
		grandparent->left = temp3;

		if (ptr->parent != nullptr)
		{
			if (ptr->parent->left == grandparent)
				ptr->parent->left = ptr;
			else
				ptr->parent->right = ptr;
		}
		if (temp2 != nullptr)
			temp2->parent = parent;
		if (temp3 != nullptr)
			temp3->parent = grandparent;
	}
	else
	{
		print << "zig-zag - "; //does a left right rotation
		cout << "zig-zag - ";
		temp1 = grandparent->left;
		temp2 = ptr->left;
		temp3 = ptr->right;
		temp4 = parent->right;

		ptr->parent = grandparent->parent;
		ptr->left = grandparent;
		ptr->right = parent;
		//switches around the nodes to make the rotation
		parent->parent = ptr;
		parent->left = temp3;

		//sets the new node and its parent
		grandparent->parent = ptr;
		grandparent->right = temp2;


		if (ptr->parent != nullptr)
		{
			if (ptr->parent->left == grandparent)
				ptr->parent->left = ptr;
			else
				ptr->parent->right = ptr;
		}
		if (temp2 != nullptr)
			temp2->parent = grandparent;
		if (temp3 != nullptr)
			temp3->parent = parent;
	}

	//incraments the operations depending on the action code
	if (code == 'I') {
		SplayInsertOp += 2;
		treeOperations[1][2] += 2;
		cout << " insert operation found in Splay::zigzag \n-- SplayInsertOp -> " << SplayInsertOp;
	}
		
	if (code == 'S') {
		SplaySearchOp += 2;
		treeOperations[0][2] += 2;
		cout << " search operation found in Splay::zigzag \n-- SplaySearchOp -> " << SplaySearchOp;
	}
		
	if (code == 'D') {
		SplayDeleteOp += 2;
		treeOperations[2][2] += 2;
		cout << " delete operation found in Splay::zigzag \n-- SplayDeleteOp -> " << SplayDeleteOp;
	}
		
}

/*
Description: find the minimum number of the tree
Pre-condition: the root of the tree must be passed in
Post-condition: a pointer to the minimum is returned
*/
node* Splay::treeMin(node* ptr)
{
	node* curr = ptr;
	while (curr->left != nullptr) //loops until the minimum is found
	{
		curr = curr->left;
	}
	return curr;
}

/*
Description: find the maximum number of the tree
Pre-condition: the root of the tree must be passed in 
Post-condition: a pointer to the maximum is returned
*/
node* Splay::treeMax(node* ptr)
{
	node* curr = ptr;
	while (curr->right != nullptr) //loops until the maximum is found
	{
		curr = curr->right;
	}
	return curr;
}

/*
Description: This function searches for the digit passed in
Pre-condition: the key must be passed in 
Post-condition: the function will return the node
*/ 
node* Splay::splaySearch(int key, char C, ofstream& outFile)
{
	node* val = nullptr,  *curr = root,  *prev = nullptr;

	while (curr != nullptr)
	{
		prev = curr;
		if (key < curr->value) //case where the key is less than the nodes value
		{
			if (C == 'S') {
				SplaySearchOp++;
				treeOperations[0][2] ++;
				cout << " search found in searchSplay -- SplaySearchOp -> " << SplaySearchOp;
			}

			if (C == 'I') {
				SplayInsertOp++;
				treeOperations[1][2] += 2;
				cout << " insert found in searchSplay -- SplayInsertOp -> " << SplayInsertOp;
			}
				
			if (C == 'D') {
				SplayDeleteOp++;
				treeOperations[2][2] ++;
				cout << " delete found in searchSplay -- SplayDeleteOp -> " << SplayDeleteOp;
			}
				
			curr = curr->left;
		}
		else if (key > curr->value) //case where the key is larger than the pointers value
		{
			if (C == 'S') {
				SplaySearchOp++;
				treeOperations[0][2] ++;
				cout << " search found in searchSplay -- SplaySearchOp -> " << SplaySearchOp;
			}

			if (C == 'I') {
				SplayInsertOp++;
				treeOperations[1][2] += 2;
				cout << " insert found in searchSplay -- SplayInsertOp -> " << SplayInsertOp;
			}

			if (C == 'D') {
				SplayDeleteOp++;
				treeOperations[2][2] ++;
				cout << " delete found in searchSplay -- SplayDeleteOp -> " << SplayDeleteOp;
			}
			curr = curr->right;
		}
		else {
			val = curr; //something to do with this line, maube change the if statememtns at the bottom 
			break;
		}
	}

	//splays the last accessed node
	if (val != nullptr) {
		cout << "found " << val->value;
		splay(val, C, outFile);
	}	
	else if (prev != nullptr) {
		cout << " not in tree -- splaying" << prev->value;
		splay(prev, C, outFile);
	}
		
	return val;
}

/*
Description: This function deletes a node from the splay tree
Pre-condition: A number must be passed in
Post-condition: If the node exists, its deleted, if not then error message
*/
void Splay::deleteNode_Splay(int key, char C, ofstream& outFile)
{
	node* ptr = nullptr;
	ptr = splaySearch(key, C, outFile);
	if (ptr == nullptr) //the tree is empty
	{
		outFile << "not in tree" << endl;
		cout << " not in tree " << endl;
		return;
	}
	node* left, * right, * min, * max;
	
	if (ptr->twin > 1) //theres a twin
	{
		ptr->twin--;
		splay(ptr, C, outFile);
		return;
	}

	left = ptr->left;
	right = ptr->right;

	if (left == nullptr && right == nullptr) //theres a leaf node
	{
		SplayDeleteOp++;
		treeOperations[2][2]++;
		if (ptr->twin > 1)
		{
			ptr->twin--;
			return;
		}
		else  //deleted the pointer
		{
			delete ptr;//double check
			return;
		}
	}

	else if (left == nullptr) //one leaf
	{
		min = treeMin(right);
		ptr->right->parent = nullptr;
		delete ptr;
		splay(min, C, outFile);
		root = min;
	}
	else if (right == nullptr) //one leaf
	{
		max = treeMax(left);
		ptr->left->parent = nullptr;
		delete ptr;
		splay(max, C, outFile);
		root = max;
	}
	else {
		max = treeMax(left);
		delete ptr;
		root = max;
		splay(max, C, outFile);
		max->right = right;
		right->parent = max;
	}

}