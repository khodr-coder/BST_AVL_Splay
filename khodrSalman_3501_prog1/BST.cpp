
#include "Header.h"

//Program Name: CIS 3501 Program 1
//Programmer Name: Khodr Salman
//Description: Create a BST, AVL, and Splay tree and run various operations on them to compare operations 
//Date Created: 2/21/21

int treeOperations[3][3] = { {0,0,0},
							 {0,0,0},
						     {0,0,0} };


/*
Description: This function clears the operation varibales for the BST class
Pre-condition: the operations must exist in the class
Post-condition: The operation varibales are reset
*/
void BST::clearALL_BSTops()
{
	BSTInsertOp = 0;
	BSTSearchOp = 0;
	BSTDeleteOp = 0;
}

/*
Description: This function sets the root to val passed in 
Pre-condition: a pointer must be passed in
Post-condition: the root is set equal to the pointer
*/
void BST::setRoot(node* val)
{
	root = val;
}
/*
Description: This function returns the root of tree
Pre-condition: the root must exist even if it is null
Post-condition: the root is returned 
*/
node* BST::getRoot()
{
	return root;
}

/*
Description: This function returns the insert operations variable of the class
Pre-condition: the variable must exist
Post-condition: the integer is returned
*/
int BST::getBSTInsertOps()
{
	return BSTInsertOp;
}
/*
Description: This function returns the search operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned 
*/
int BST::getBSTSearchOps()
{
	return BSTSearchOp;
}
/*
Description: This function returns the delete operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned 
*/
int BST::getBSTDeleteOps()
{
	return BSTDeleteOp;
}
/*
Description: This function is used for inserting, it calls the insert function and sends the digit/number passed in 
Pre-condition: A value must be passed in
Post-condition: The insert function is called sending root and the digit/number passed in 
*/
void BST::InsertBST(int digit)
{
	insert(digit, root);


}
/*
Description: This function is used for inserting a digit/number in the tree
Pre-condition: the tree must exist
Post-condition: the location is found and the key is inserted
*/
void BST::insert(int number, node*& ptr)
{
	node* curr = ptr;
	node* prev = curr;
	node* temp;
	temp = newNode(number);
	if (curr == nullptr)	//if the root is empty
	{
		BSTInsertOp++;
		treeOperations[1][0]++;
		ptr = temp;
	}

	else {
		while (curr != nullptr)
		{
			BSTInsertOp++;
			prev = curr;
			if (curr->value > number)
			{
				treeOperations[1][0]++;
				curr = curr->left;	//location is moved to the left child
			}
			else if (curr->value < number)
			{
				treeOperations[1][0]++;
				curr = curr->right;//location is moved to the right child
			}
			else if (curr->value == number)
			{
				treeOperations[1][0]++;
				curr->twin++; //incramenting the twin
				break;
			}

		}
		if (prev->value < number)
		{
			BSTInsertOp++;
			treeOperations[1][0]++;
			prev->right = temp;	//sets the value
		}
		else if (prev->value > number)
		{
			BSTInsertOp++;
			treeOperations[1][0]++;
			prev->left = temp;	//sets the value
		}

	}
}
/*
Description: This function creates a new node using digit/number passed in 
Pre-condition: digit/number be set equal to a node pointer
Post-condition: a new empty node is created contsining the digit/number passed in
*/
node* BST::newNode(int digit)
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
Description: This functions gets the height of the tree
Pre-condition: a pointer to the node must be sent in and the tree must exist 
Post-condition: The height is returned
*/
int BST::getHeight(node* ptr)
{
	//return ptr->height;
	
	int left, right;
	if (ptr == nullptr) {
		return 0;
	}
	else {
		left = getHeight(ptr->left);
		right = getHeight(ptr->right);
	}
	return left < right ? right + 1 : left + 1;
}
/*
Description: This function calls uses the height function to print the tree, once height is obtained it uses it to space the digits away from eachother properly 
Pre-condition: A pointer to the root must be passed in
Post-condition: The tree is printed using the height for the spacing
*/
void BST::BSTtree_LevelAndPrint(node* root, ofstream& outFile)
{
	int h = getHeight(root);
	cout << "\n height in BST tree is now " << h << endl;
	outFile << "\n height in BST tree is now " << h << endl;
	int c = h * 2;


	for (int i = 1; i <= h; i++)	//loop through each level
	{
		outFile << endl;	//print new line every level
		cout << endl;
		BST_PrintOneLevel(root, i, c, outFile);
	}
}
/*
Description: This function prints the tree one level (L) at a time 
Pre-condition: a pointer to the root must exist
Post-condition: the tree is printed 
*/
void BST::BST_PrintOneLevel(node* root, int L, int spaces, ofstream& outFile)
{
	if (root == nullptr)	
	{
		for (int i = 0; i < spaces + 1; i++)
		{
			outFile << " ";
			cout << " ";
		}
		return;
	}
	if (L == 1)	//base case, print the node
	{
		for (int i = 0; i < spaces; i++)	//correct spacing
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
		BST_PrintOneLevel(root->left, L - 1, spaces / 2, outFile);	//recursively call by sending right pointer, one less level, and spacing/2
		BST_PrintOneLevel(root->right, L - 1, spaces - 1, outFile);	//recursively call by sending left pointer, one less level, and spacing -1	
	}
}
/*
Description: This function looks for a key in the tree 
Pre-condition: a key number must be sent in as well as location and level (L) 
Post-condition: the key is searched for
*/
void BST::SearchBST(int findMe, node* loc, int& L, node*& parent, ofstream& outFile)
{
	node* temp;
	if (!loc) //node is empty
	{
		outFile << "Value not in tree" << endl;
		cout << "Value not in tree" << endl;

	}
	else if (loc->value == findMe)
	{
		treeOperations[0][0]++;	//finds the value
		BSTSearchOp++;
		return;
	}
	else if (loc->value > findMe) // the key number is less
	{
		treeOperations[0][0]++;
		BSTSearchOp++;
		temp = loc->left;
		SearchBST(findMe, temp, ++L, temp->parent, outFile);
	}
	else if (loc->value < findMe) //key number is greater
	{
		treeOperations[0][0]++;
		BSTSearchOp++;
		temp = loc->right;
		SearchBST(findMe, temp, ++L, temp->parent, outFile);
	}

}
/*
Description: delete a node in the bst tree using the min, and 2 temp pointers
Pre-condition: a key number  to be deleted is passed in
Post-condition:  delete is done if the node exists, if not -> error message
*/
node* BST::DeleteBST(node* deleteMe, int num)
{
	node* MINt;
	node* temp1;
	node* temp2;

	if (deleteMe == nullptr) //only digit in the tree
	{
		return deleteMe;
	}

	if (num < deleteMe->value) //number is less
	{
		treeOperations[2][0]++;
		BSTDeleteOp++;
		deleteMe->left = DeleteBST(deleteMe->left, num); //call the delete function
	}

	else if (num > deleteMe->value) //number is greater than
	{
		treeOperations[2][0]++;
		BSTDeleteOp++;
		deleteMe->right = DeleteBST(deleteMe->right, num); // call the delete function
	}

	else { //deleting the key
		if (deleteMe->twin <= 1)
		{
			if (deleteMe->left == nullptr) //only one child
			{
				temp1 = deleteMe->right;
				delete deleteMe;
				return temp1;
			}
			else if (deleteMe->right == nullptr) //only one child
			{
				temp2 = deleteMe->left;
				delete deleteMe;
				return temp2;
			}
			BSTDeleteOp++;
			MINt = minv(root->right); //find minimum value
			deleteMe->value = MINt->value;
			MINt = nullptr;
		}
		else {
			BSTDeleteOp++;
			treeOperations[2][0]++;
			deleteMe->twin--;
		}
	}

}
/*
Description: This function finds the minimum value of the tree 
Pre-condition: the tree must not be empty,. and location is passed in 
Post-condition: a pointer to the minimum value is returned as temp
*/
node* BST::minv(node* loc)
{
	node* temp;
	temp = loc;
	while ((temp != nullptr) && (temp->left != nullptr)) //loops through the tree until min is found
	{
		BSTDeleteOp++;
		temp = temp->left;
	}
	return temp;

}