#ifndef HEADER_HPP
#define HEADER_HPP

//Program Name: CIS 3501 Program 1
//Programmer Name: Khodr Salman
//Description: Create a BST, AVL, and Splay tree and run various operations on them to compare operations 
//Date Created: 2/21/21

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
extern int treeOperations[3][3]; // wouldnt work if i declared the array in this file for some reason

struct node {
	int value;
	int height;
	node* left;
	node* right;
	int twin = 1;
	node* parent = nullptr;

};



class BST {
private:
	int BSTInsertOp = 0;
	int BSTDeleteOp = 0;
	int BSTSearchOp = 0;

public:
	node* root;
	void setRoot(node*);
	int getBSTInsertOps(); //return number of insert operations 
	int getBSTSearchOps();
	int getBSTDeleteOps();
	void InsertBST(int);
	void SearchBST(int, node*, int&, node*&, ofstream&);
	void insert(int, node*&);
	node* newNode(int);
	int getHeight(node*);
	void BSTtree_LevelAndPrint(node*, ofstream&);
	void BST_PrintOneLevel(node*, int, int, ofstream&);
	node* DeleteBST(node*, int);
	node* minv(node*);
	node* getRoot();
	void clearALL_BSTops();
};




class Splay { 
private:
	int SplayInsertOp = 0;
	int SplayDeleteOp = 0;
	int SplaySearchOp = 0;

public:
	node* root;	
	node* newNode(int);
	int getSplayInsertOps();
	int getSplayDeleteOps();
	int getSplaySearchOps();
	int getHeight(node*);
	void insertSplay(int key, ofstream&);
	void splay(node*, char, ofstream&);
	void zig(node*, char, ofstream&);
	void zigzig(node*, char, ofstream&);
	void zigzag(node*, char, ofstream&);
	void deleteNode_Splay(int, char, ofstream&);
	void Splay_PrintOneLevel(node*, int, int, ofstream&);
	node* splaySearch(int, char, ofstream&);
	node* treeMin(node*);
	node* treeMax(node*);
	void clearALL_SplayOps();
	void Splaytree_LevelAndPrint(node*, ofstream&);
};

class AVL : public Splay {
private:
	int AVLInsertOp = 0;
	int AVLSearchOp = 0;
	int AVLDeleteOp = 0;
public:
	node* root;
	int getAVLInsertOps();
	int getAVLSearchOps();
	int getAVLDeleteOps();
	node* newNode(int);
	void insertAVL(int, ofstream&);
	void balanceChecker(node*, char, ofstream&);
	void height(node*);
	void checkHeightandRotate(node*, char, ofstream&);
	int getBalance(node*, node*);
	void rightRotation(node*, char, ofstream&);
	void leftRotation(node*, char, ofstream&);
	void setRoot(node*);
	int getHeight(node*);
	void AVLtree_LevelAndPrint(node*, ofstream&);
	void rightLeftRotation(node*, char, ofstream&);
	void leftRightRotation(node*, char, ofstream&);
	node* searchAVL(int, char, ofstream&);
	void deleteAVL(int, ofstream&);
	void clearALL_AVLOps();
	void AVL_PrintOneLevel(node*, int, int, ofstream&);
};


#endif //! HEADER_HPP
