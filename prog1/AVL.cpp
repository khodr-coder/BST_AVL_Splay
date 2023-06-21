
#include "Header.h"
//Program Name: CIS 3501 Program 1
//Programmer Name: Khodr Salman
//Description: Create a BST, AVL, and Splay tree and run various operations on them to compare operations 
//Date Created: 2/21/21

/*
Description: This function creates a new node using digit/number passed in
Pre-condition: digit/number be set equal to a node pointer
Post-condition: a new empty node is created contsining the digit/number passed in
*/
node* AVL::newNode(int digit)
{
	node* temp = new node;
	temp->value = digit;
	temp->left = nullptr;
	temp->right = nullptr;
	temp->height = 0;
	temp->twin = 1;	//sets twin equal to one because there is one of it in the tree, if there is more than 1 it will display 1+1, so 2
	temp->parent = nullptr;

	return temp;
}

/*
Description: This function clears the operation varibales for the AVL class
Pre-condition: the operations array must exist 
Post-condition: The operation varibales are reset
*/
void AVL::clearALL_AVLOps()
{
	AVLInsertOp = 0;
	AVLSearchOp = 0;
	AVLDeleteOp = 0;
}

/*
Description: This function returns the insert operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int AVL::getAVLInsertOps()
{
	return AVLInsertOp;
}
/*
Description: This function returns the search operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int AVL::getAVLSearchOps()
{
	return AVLSearchOp;
}

/*
Description: This function returns the delete operations variable
Pre-condition: the the variable must exist
Post-condition: the integer is returned
*/
int AVL::getAVLDeleteOps()
{
	return AVLDeleteOp;
}


/*
Description: This function calls uses the height function to print the tree, once height is obtained it uses it to space the digits away from eachother properly
Pre-condition: A pointer to the root must be passed in
Post-condition: The tree is printed using the height for the spacing
*/
void AVL::AVLtree_LevelAndPrint(node* root, ofstream& outFile)
{
	int h = getHeight(root);
	cout << "\n height in AVL tree is now " << h << endl;
	outFile << "\n height in AVL tree is now " << h << endl;
	int c = h * 2;


	for (int i = 1; i <= h; i++)	//loop through each level
	{
		outFile << endl;	//print new line every level
		cout << endl;
		AVL_PrintOneLevel(root, i, c, outFile);
	}
}
/*
Description: This functions gets the height of the tree
Pre-condition: a pointer to the node must be sent in and the tree must exist
Post-condition: The height is returned
*/
int AVL::getHeight(node* ptr)
{
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
void AVL::AVL_PrintOneLevel(node* root, int L, int space, ofstream& outFile)
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
		AVL_PrintOneLevel(root->left, L - 1, space / 2, outFile);	//recursively call by sending right pointer, one less level, and spacing/2
		AVL_PrintOneLevel(root->right, L - 1, space - 1, outFile);	//recursively call by sending left pointer, one less level, and spacing -1	
	}
}


/*
Description: This function takes a digit and inserts it into the AVL tree and uses balanceChecker function to balance it
Pre-condition: the number passed in must be VALID
Post-condition: the digit is inserted into the tree and rotated
*/
void AVL::insertAVL(int key, ofstream& outFile)
{
	node* temp;
	node* curr;
	if (root == nullptr) //nothing in the tree
	{
		AVLInsertOp++;
		treeOperations[1][1]++;
		temp = newNode(key);
		root = temp;
	}
	else
	{
		AVLInsertOp++;
		treeOperations[1][1]++;
		temp = newNode(key);
		curr = root;
		while (curr != nullptr) //loops while the tree is not empty
		{
			if (curr->value > key)	//key is smaller
			{
				if (curr->left == nullptr) //node is null
				{
					AVLInsertOp++;
					treeOperations[1][1]++;
					curr->left = temp;
					temp->parent = curr;
					break; 
				}
				else {
					AVLInsertOp++;
					treeOperations[1][1]++;
					curr = curr->left;
				}
			}
			else if (curr->value < key)// the value is larger
			{
				if (curr->right == nullptr)	//the node is null
				{
					AVLInsertOp++;
					treeOperations[1][1]++;
					curr->right = temp;	//sets child
					temp->parent = curr;	//sets parent
					break;
				}
				else {
					AVLInsertOp++;
					treeOperations[1][1]++;
					curr = curr->right;
				}
			}
			else if (curr->value == key)	//theres a twin
			{
				curr->twin++;
				temp = curr;
				break;
			}
		}

		balanceChecker(temp, 'I', outFile); //checks the balance
	}
}

/*
Description: This function checks balance using checkHeightandRotate function 
Pre-condition: a pointer must be passed in
Post-condition: The tree is balanced using checkHeightandRotate and height()
*/
void AVL::balanceChecker(node* ptr, char C, ofstream& outFile)
{
	node* temp = ptr;
	if (temp == root)
	{
		checkHeightandRotate(temp, C, outFile);	//checks the tree height
	}
	else {
		while (temp != nullptr)	//loops through checking every node
		{
			height(temp);
			temp = temp->parent;
			if (temp != nullptr)
			{
				checkHeightandRotate(temp, C, outFile); //checks the tree height
			}
		}
	}
}

/*
Description: This function checks the height of the tree/node passed in
Pre-condition: The node must be passed in
Post-condition: The height of the tree is printed and set to the node 
*/
void AVL::height(node* ptr)
{
	int left = -1;
	int right = -1;
	if (ptr->left != nullptr)
	{
		left = ptr->left->height;//finds the height of the child
	}
	if (ptr->right != nullptr)
	{
		right = ptr->right->height;
	}
	if (right > left) //takes the larger height
		ptr->height = right + 1;
	else
		ptr->height = left + 1;

	cout << " height inside AVL::height is  -> " << ptr->height;
}

/*
Description: This function checks the balance of the node calls correct rotation 
Pre-condition: A node must be passed in
Post-condition: The tree is balanced using correct rotation
*/
void AVL::checkHeightandRotate(node* ptr, char C, ofstream& outFile)
{
	//there is an issue with this function but i dont know what it is 

	if (getBalance(ptr->right, ptr->left) == 2)	//checks the balance
	{
		if (getBalance(ptr->right->right, ptr->right->left) < 0)
		{
			outFile << "LR case " << endl; cout << "LR case" << endl;
			outFile << "rotating "; cout << "rotating ";
			rightLeftRotation(ptr, C, outFile); //calls lr rotation
		}
		else
		{
			outFile << "RR case " << endl; cout << "RR case " << endl;
			outFile << "rotating "; cout << "rotating " << endl;
			leftRotation(ptr, C, outFile); //calls rr rotation
		}

		height(ptr);
	}
	else if (getBalance(ptr->right, ptr->left) == -2)
	{
		if (getBalance(ptr->left->right, ptr->left->left) > 0)
		{
			outFile << "RL case " << endl; cout << "RL case " << endl;
			outFile << "rotating "; cout << "rotating ";
			leftRightRotation(ptr, C, outFile);
			//calls left right rotation
		}
		else
		{
			outFile << "LL case " << endl; cout << "LL case " << endl;
			outFile << "Rotations: "; cout << "Rotations: ";
			rightRotation(ptr, C, outFile);
			//calls right rotation
		}
		height(ptr); //checks the height
	}
}


/*
Description: This function gets the balance of the tree/node sent in
Pre-condition: A node pointer for the tree must be sent in
Post-condition: The tree is checked for balance
*/
int AVL::getBalance(node* right, node* left)
{
	int R, L;
	node* temp;
	if (right == nullptr)
		R = -1;	//checks the balance of the nodes
	else
		R = right->height;

	if (left == nullptr)
		L = -1;
	else
		L = left->height;

	return R - L;
}

/*
Description: This function does a right rotation on the node sent in
Pre-condition: a node that needs a right rotation is sent in using a pointer
Post-condition: A right rotation is done
*/
void AVL::rightRotation(node* ptr, char C, ofstream& outFile)
{
	outFile << "right rotation ";
	cout << "right rotation ";
	node* temp, * parentTemp, * child, * gChild;
	child = ptr->left;
	gChild = child->left;
	temp = child->right;
	parentTemp = ptr->parent;
	child->right = ptr;
	ptr->parent = child;	//switches positions of the nodes to make a right rotation
	ptr->left = temp;
	child->parent = parentTemp;
	if (parentTemp != nullptr)
		parentTemp->left = child;

	if (C == 'I') {	//incraments the operations
		AVLInsertOp++;
		treeOperations[1][1]++;
		cout << "\n insert in AVL leftRot -- AVLInsertOp is now -> " << AVLInsertOp;
	}
	if (C == 'S') {	//incraments the operations
		AVLSearchOp++;
		treeOperations[0][1]++;
		cout << "\n delete in AVL leftRot -- AVLInsertOp is now -> " << AVLSearchOp;
	}
	else if (C == 'D') {
		AVLDeleteOp++;
		treeOperations[2][1]++;
		cout << "\n delete in AVL leftRot -- AVLDeleteOp is now -> " << AVLDeleteOp;
	}
	setRoot(ptr); //sets the root back to what the new root is (if there is one)
}

/*
Description: This function does a left rotation
Pre-condition: a node that needs a left rotation is passed in 
Post-condition: A left rotation is done
*/
void AVL::leftRotation(node* ptr, char C, ofstream& outFile)
{
	outFile << "left rotation ";
	cout << "left rotation ";
	node* temp, * parentTemp, * child, * gChild;
	child = ptr->right;
	gChild = child->right;
	temp = child->left;
	parentTemp = ptr->parent;
	child->left = ptr;
	ptr->parent = child;	//switches positions of the nodes to make a left rotation
	ptr->right = temp;
	child->parent = parentTemp;
	if (parentTemp != nullptr)
		parentTemp->right = child;

	if (C == 'I') {	//incraments the operations
		AVLInsertOp++;
		treeOperations[1][1]++;
		cout << "\n insert in AVL leftRot -- AVLInsertOp is now -> " << AVLInsertOp;
	}
	if (C == 'S') {	//incraments the operations
		AVLSearchOp++;
		treeOperations[0][1]++;
		cout << "\n search in AVL leftRot -- AVLInsertOp is now -> " << AVLSearchOp;
	}
	else if (C == 'D') {
		AVLDeleteOp++;
		treeOperations[2][1]++;
		cout << "\n delete in AVL leftRot -- AVLDeleteOp is now -> " << AVLDeleteOp;
	}
	setRoot(ptr); //sets the root equal to the highest node
}


/*
Description: This function does a rightleft rotation
Pre-condition: a node that needs a rightleft rotation is passed in 
Post-condition: A rightleft rotation is done
*/
void AVL::rightLeftRotation(node* ptr, char C, ofstream& outFile)
{
	outFile << "right left ";
	cout << "right left ";
	node* tempL, * tempR, * parentTemp, * child, * gChild;
	child = ptr->right;
	gChild = child->left;

	tempL = gChild->left;
	tempR = gChild->right;
	parentTemp = ptr->parent;
	ptr->parent = gChild;	//switches the positions to do a right left rotation
	gChild->left = ptr;
	gChild->right = child;
	child->parent = gChild;
	gChild->parent = parentTemp;
	if (parentTemp != nullptr)
		parentTemp->right = gChild;
	child->left = tempR;
	ptr->right = tempL;

	//incraments operations depending on what the action code is
	if (C == 'I') {	//incraments the operations
		AVLInsertOp++;
		treeOperations[1][1]++;
		cout << "\n insert in AVL leftRot -- AVLInsertOp is now -> " << AVLInsertOp;
	}
	if (C == 'S') {	//incraments the operations
		AVLSearchOp++;
		treeOperations[0][1]++;
		cout << "\n search in AVL leftRot -- AVLInsertOp is now -> " << AVLSearchOp;
	}
	else if (C == 'D') {
		AVLDeleteOp++;
		treeOperations[2][1]++;
		cout << "\n delete in AVL leftRot -- AVLDeleteOp is now -> " << AVLDeleteOp;
	}

	setRoot(gChild);
}

/*
Description: This function does a leftright rotation 
Pre-condition: a node that needs a leftright rotation is passed in
Post-condition: A leftright rotation is done
*/
void AVL::leftRightRotation(node* ptr, char C, ofstream& outFile)
{
	outFile << "left right ";
	cout << "left right ";
	node* tempL, * tempR, * parentTemp, * child, * gChild;
	child = ptr->left;
	gChild = child->right;

	tempL = gChild->right;
	tempR = gChild->left;
	parentTemp = ptr->parent;
	ptr->parent = gChild;	//switches positions to make the left right rotation
	gChild->right = ptr;
	gChild->left = child;
	child->parent = gChild;
	gChild->parent = parentTemp;
	if (parentTemp != nullptr)
		parentTemp->left = gChild;
	child->right = tempR;
	ptr->left = tempL;

	//incraments operations depending on what the action code is
	if (C == 'I') {	//incraments the operations
		AVLInsertOp++;
		treeOperations[1][1]++;
		cout << "\n insert in AVL leftRot -- AVLInsertOp is now -> " << AVLInsertOp;
	}
	if (C == 'S') {	//incraments the operations
		AVLSearchOp++;
		treeOperations[0][1]++;
		cout << "\n search in AVL leftRot -- AVLInsertOp is now -> " << AVLSearchOp;
	}
	else if (C == 'D') {
		AVLDeleteOp++;
		treeOperations[2][1]++;
		cout << "\n delete in AVL leftRot -- AVLDeleteOp is now -> " << AVLDeleteOp;
	}

	setRoot(gChild);
}
/*
Description: This function searched for a key in the tree and returns it as a pointer
Pre-condition: a key number must be sent in
Post-condition: a pointer to the node is returned if it exists.
*/
node* AVL::searchAVL(int key, char C, ofstream& outFile)
{
	int height = 0;
	node* val = nullptr, * curr = root, * prev = nullptr;
	while (curr != nullptr)
	{
		prev = curr;
		if (key < curr->value) //case where the key is less than the pointers value
		{
			height++;
			if (C == 'S') {
				AVLSearchOp++;
				treeOperations[0][1] ++;
				cout << "\n Search operation in searchAVL -- AVLSearchOp is now -> " << AVLSearchOp;
			}
			if (C == 'D') {
				AVLDeleteOp++;
				treeOperations[2][1] ++;
				cout << "\n delete operation in searchAVL -- AVLDeleteOp is now -> " << AVLDeleteOp;
			}
			curr = curr->left; //moves the key to the left child
		}
		else if (key > curr->value) //case where the key is larger than the pointers value
		{
			height++;
			if (C == 'S') {
				AVLSearchOp++;
				treeOperations[0][1] ++;
				cout << "\n Search operation in searchAVL -- AVLSearchOp is now -> " << AVLSearchOp;
			}
			if (C == 'D') {
				AVLDeleteOp++;
				treeOperations[2][1] ++;
				cout << "\n delete operation in searchAVL -- AVLDeleteOp is now -> " << AVLDeleteOp;
			}
			curr = curr->right; //moves the key to the pointers right child
		}
		else { //other cases
			if (curr->value == key && curr->twin > 1)
			{
				curr->twin--;	//decrement the twin varibale
				return curr;
			}
			if (C == 'S') {
				AVLSearchOp++;
				treeOperations[0][1] ++;
				cout << "\n Search operation in searchAVL -- AVLSearchOp is now -> " << AVLSearchOp;
			}
			if (C == 'D') {
				AVLDeleteOp++;
				treeOperations[2][1] ++;
				cout << "\n delete operation in searchAVL -- AVLDeleteOp is now -> " << AVLDeleteOp;
			}
			val = curr;
			break;
		}
	}
	if (val== nullptr)	//not in tree
	{
		outFile << " \n Not Found " << endl;
		cout << " \n not found" << endl;
	}
	else { //in tree and print value
		outFile << "FOUND value ->" << prev->value << endl;	
		cout << "\nFOUND AVL value ->" << prev->value << endl;	
	}
		
	outFile << "Level: " << height << endl; //print level
	cout << "Level: " << height << endl;
	return val;
}

/*
Description: This function sets the root varibale 
Pre-condition: the tree must not be empty
Post-condition: the root varibale is set to the root
*/
void AVL::setRoot(node* ptr)
{
	node* next, * curr;
	next = curr = ptr;
	while (next != nullptr)	//loops until the root 
	{
		curr = next;
		next = next->parent;
	}

	root = curr; //sets the root
}

/*
Description: deletes a node AVL tree
Pre-condition: a key number to be deleted is passed in
Post-condition: A delete is done if the node exists, if not then error
*/
void AVL::deleteAVL(int key, ofstream& outFile)
{
	node* ptr = searchAVL(key, 'D', outFile);
	node* left, * right, * min = nullptr, * max = nullptr, * parentTemp = nullptr;

	if (ptr == nullptr)
	{
		outFile << "not in tree" << endl; //digit is not in the tree
		cout << "not in tree" << endl; //digit is not in the tree
		return;
	}
	parentTemp = ptr->parent;
	left = ptr->left;
	right = ptr->right;

	if (left == nullptr && right == nullptr) //leaf node
	{
		if (ptr->twin > 1)
		{
			ptr->twin--;
			return;
		}
		else
		{
			AVLDeleteOp++;
			treeOperations[2][1]++;
			if (parentTemp->left == ptr)
			{
				parentTemp->left = nullptr;
				delete ptr;

			}
			else if (parentTemp->right == ptr)
			{
				parentTemp->right = nullptr;
				delete ptr;
			}
			else
				delete ptr;
			return;
		}
	}

	else if (left == nullptr) //one child
	{
		AVLDeleteOp++;
		treeOperations[2][1]++;
		min = treeMin(right);	//find the min
		min->parent = parentTemp;
		parentTemp->left = min;
	}
	else if (right == nullptr)//one child
	{
		AVLDeleteOp++;
		treeOperations[2][1]++;
		max = treeMax(left);
		max->parent = parentTemp;
		parentTemp->right = max;
	}
	else { //two children
		AVLDeleteOp++;
		treeOperations[2][1]++;
		if (ptr->twin > 1)
		{
			ptr->twin--;
			return;
		}
		max = treeMax(left); //find the max 

		max->right = right;
		right->parent = max;
		if (max != left)
		{
			max->left = left;
			left->parent = max;
		}
		else
		{
			max->left = nullptr;
		}
		max->parent = parentTemp;
	}
	AVLDeleteOp++;
	treeOperations[2][1]++;
	delete ptr;
	if (min == nullptr)
	{
		setRoot(max); //sets the root using the max
		balanceChecker(max, 'D', outFile); //checks the balance
	}
	else
	{
		setRoot(min); //sets the root using the min
		balanceChecker(min, 'D', outFile); //checks the balance
	}

}