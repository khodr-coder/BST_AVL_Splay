#include "Header.h"

//Program Name: CIS 3501 Program 1
//Programmer Name: Khodr Salman
//Description: Create a BST, AVL, and Splay tree and run various operations on them to compare operations 
//Date Created: 2/21/21

int main()
{
	BST BSTobject;
	AVL AVLobject;
	Splay SplayObject;

	int totalOperations[3] = { 0,0,0 };
	int BSTTotal = 0, AVLTotal = 0, SplayTotal = 0;
	
	
	ofstream BSToutput, AVLoutput, SplayOutput, sumfile;
	ifstream ifs1, ifs2;
	string dataFile, actionFile, outputBST, outputAVL, outputSplay, outputSum, testName;

	char yn;
	do {
		
		cout << "\n Enter the name of your input file 1 and input file 2 -> ";
		cin >> dataFile >> actionFile;

		cout << "\n Enter the name of your BST outputfile, AVL outputfile, Splay output file and summary output file -> ";
		cin >> outputBST >> outputAVL >> outputSplay >> outputSum;

		cout << "\n Finally Enter the name of your test -> "; 
		cin >> testName;
		

		char C;
		int num;
		ifs1.open(dataFile);
		
		//check all files being open 
		if (!ifs1.is_open())	
		{
			cout << "Error opening " << dataFile << endl;
			exit(1);
		}

		ifs2.open(actionFile);	
		if (!ifs2.is_open())
		{
			cout << "Error opening " << actionFile << endl;
			exit(1);
		}

		BSToutput.open(outputBST);	
		if (!BSToutput.is_open())
		{
			cout << "Error opening " << outputBST << endl;
			exit(1);
		}

		AVLoutput.open(outputAVL);	
		if (!AVLoutput.is_open())
		{
			cout << "Error opening " << outputAVL << endl;
			exit(1);
		}

		SplayOutput.open(outputSplay);	
		if (!SplayOutput.is_open())
		{
			cout << "Error opening " << outputSplay << endl;
			exit(1);
		}

		sumfile.open(outputSum);	
		if (!sumfile.is_open())
		{
			cout << "Error opening " << outputSum << endl;
			exit(1);
		}

		
			while (!ifs1.eof())	// take input until end of file
			{
				//takes in the input
				ifs1 >> num;
				
				BSToutput << "\n ____________________________________________\n"; cout << "\n ____________________________________________\n";
				BSToutput << "BST insert operation " << num << endl; cout << "BST insert operation " << num << endl;
				
				AVLoutput << "\n ____________________________________________\n"; cout << "\n ____________________________________________\n";
				AVLoutput << "AVL insert operation " << num << endl; cout << " AVL insert operation " << num << endl;
				
				SplayOutput << "\n ____________________________________________\n"; cout << "\n ____________________________________________\n";
				SplayOutput << "splay insert operation " << num << endl; cout << "splay insert operation" << num << endl;
				

				BSTobject.insert(num, BSTobject.root);	//calls function to insert the digit  //calls function to print the tree
				BSToutput << endl << "bst insert operations count -> " << BSTobject.getBSTInsertOps() << endl;
				cout << endl << "bst insert operations count -> " << BSTobject.getBSTInsertOps() << endl;
				BSTobject.BSTtree_LevelAndPrint(BSTobject.root, BSToutput);

				AVLobject.insertAVL(num, AVLoutput);		//calls function to insert the digit  //calls function to print the tree
				AVLoutput << endl << "AVL insert operations count -> " << AVLobject.getAVLInsertOps() << endl;
				cout << endl << "AVL insert operations count -> " << AVLobject.getAVLInsertOps() << endl;
				AVLobject.AVLtree_LevelAndPrint(AVLobject.root, AVLoutput);

				SplayObject.insertSplay(num, SplayOutput);		//calls function to insert the digit  //calls function to print the tree
				SplayOutput << endl << "splay insert operations count ->" << SplayObject.getSplayInsertOps() << endl;
				cout << endl << " splay insert operations count ->" << SplayObject.getSplayInsertOps() << endl;
				SplayObject.Splaytree_LevelAndPrint(SplayObject.root, SplayOutput);

			}
			while (!ifs2.eof())
			{
				BSToutput << "\n ____________________________________________\n";
				AVLoutput << "\n ____________________________________________\n";
				SplayOutput << "\n ____________________________________________\n";
				cout << "\n ____________________________________________\n";
				AVLobject.clearALL_AVLOps();
				SplayObject.clearALL_SplayOps();
				BSTobject.clearALL_BSTops();

				ifs2 >> C >> num;
				if (C == 'I')
				{
					BSToutput << "BST insert operation " << num << endl; cout << "\nBST insert operation " << num << endl;
					AVLoutput << "AVL insert operation " << num << endl; cout << " \nAVL insert operation " << num << endl;
					SplayOutput << "splay insert operation " << num << endl; cout << "\nsplay insert operation" << num << endl;

					BSTobject.insert(num, BSTobject.root);	//calls function to insert the digit  
					BSToutput << endl << "bst insert operations count -> " << BSTobject.getBSTInsertOps() << endl;
					cout << "\n bst insert operations count -> " << BSTobject.getBSTInsertOps() << endl;
					BSTobject.BSTtree_LevelAndPrint(BSTobject.root, BSToutput);//calls function to print the tree

					AVLobject.insertAVL(num, AVLoutput);		//calls function to insert the digit 
					AVLoutput << endl << "AVL insert operations count -> " << AVLobject.getAVLInsertOps() << endl;
					cout << "\n AVL insert operations count -> " << AVLobject.getAVLInsertOps() << endl;
					AVLobject.AVLtree_LevelAndPrint(AVLobject.root, AVLoutput); //calls function to print the tree

					SplayObject.insertSplay(num, SplayOutput);		//calls function to insert the digit 
					SplayOutput << endl << "splay insert operations count ->" << SplayObject.getSplayInsertOps() << endl;
					cout << " \n splay insert operations count ->" << SplayObject.getSplayInsertOps() << endl;
					SplayObject.Splaytree_LevelAndPrint(SplayObject.root, SplayOutput); //calls function to print the tree


				}
				else if (C == 'S')
				{
					int L = 0; // tree level tracker

					BSToutput << "\n ____________________________________________\n";
					AVLoutput << "\n ____________________________________________\n";
					SplayOutput << "\n ____________________________________________\n";
					cout << "\n ____________________________________________\n";

					BSToutput << " BST search operation " << num << endl;	cout << "\n BST search operation " << num << endl;
					AVLoutput << " AVL search operation  " << num << endl; cout << "\n AVL search operation  " << num << endl;
					SplayOutput << " Splay search operation  " << num << endl; cout << "\n Splay search operation  " << num << endl;

					node* parent = BSTobject.getRoot();	//sets pointer equal to varibale
					BSTobject.SearchBST(num, BSTobject.getRoot(), L, parent, BSToutput); //calls function to search for the digit
					if (parent == nullptr) {
						cout << "\n parent is null ";
					}
					else {
						BSToutput << "BST parent " << parent->value << endl << "level " << L << endl;
						cout << " \n BST parent " << parent->value << endl << "level " << L << endl;
					}
					BSToutput << "\BST search operations count -> " << BSTobject.getBSTSearchOps() << endl;
					cout<< " \nBST search operations count -> " << BSTobject.getBSTSearchOps() << endl;
					BSTobject.BSTtree_LevelAndPrint(BSTobject.getRoot(), BSToutput);	//calls function to print the tree

					node* searchAVL = AVLobject.searchAVL(num, 'S', AVLoutput); //calls function to search for the digit
					if (searchAVL == nullptr) {
						cout << "\n not found";
					}
					else {
						AVLoutput << "found " << searchAVL->value << endl << "level " << L << endl;
						cout << " \n found " << searchAVL->value << endl << "level " << L << endl;
					}
					AVLoutput << "\nAVL search operations count -> " << AVLobject.getAVLSearchOps() << endl;
					cout << " \nAVL search operations count -> " << AVLobject.getAVLSearchOps() << endl;
					AVLobject.AVLtree_LevelAndPrint(AVLobject.root, AVLoutput); //calls function to print the tree

					node* searchSplay = SplayObject.splaySearch(num, 'S', SplayOutput); //calls function to search for the digit
					if (searchSplay == nullptr) {
						cout << "\n not found " << endl;
					}
					else {
						cout << "\n found " << searchSplay->value << endl;
						SplayOutput << "found " << searchSplay->value << endl << "level " << L << endl;
					}
					SplayOutput << "\nsplay search operations count -> " << SplayObject.getSplaySearchOps() << endl;
					cout << " \nsplay search operations count -> " << SplayObject.getSplaySearchOps() << endl;
					SplayObject.Splaytree_LevelAndPrint(SplayObject.root, SplayOutput); //calls function to print the tree


				}
				else if (C == 'D')
				{
					BSToutput << "BST delete operation " << num << endl; cout  << "BST delete operation " << num << endl;
					AVLoutput << "AVL delete operation " << num << endl; cout << "AVL delete operation " << num << endl;
					SplayOutput << "Splay delete operation " << num << endl; cout << "Splay delete operation " << num << endl;
					
					node* temp = BSTobject.DeleteBST(BSTobject.getRoot(), num); //calls function to delete digit
					BSToutput << "BST delete operation count-> " << BSTobject.getBSTDeleteOps() << endl;
					cout << "BST delete operation count -> " << BSTobject.getBSTDeleteOps() << endl;
					BSTobject.BSTtree_LevelAndPrint(BSTobject.getRoot(), BSToutput); //calls function to print the tree

					AVLobject.deleteAVL(num, AVLoutput);
					AVLoutput << " AVL delete operation count-> " << AVLobject.getAVLDeleteOps() << endl;	//calls function to delete digit
					cout << " AVL delete operation count-> " << AVLobject.getAVLDeleteOps() << endl;
					AVLobject.AVLtree_LevelAndPrint(AVLobject.root, AVLoutput); //calls function to print the tree

					SplayObject.deleteNode_Splay(num, 'D', SplayOutput); //calls function to delete digit
					SplayOutput << "Splay delete operation count-> " << SplayObject.getSplayDeleteOps() << endl;
					cout << " Splay delete operation count-> " << SplayObject.getSplayDeleteOps() << endl;
					SplayObject.Splaytree_LevelAndPrint(SplayObject.root, SplayOutput); //calls function to print the tree

				}
				else {
					AVLoutput << "Invalid action code" << endl;
					BSToutput << "Invalid action code" << endl;
					SplayOutput << "Invalid action code" << endl;
					cout << "Invalid action code ";
				}

			}
			BSToutput << "		Summary Table" << endl << "		" << testName << endl;	BSToutput << "	BST	AVL	Splay" << endl;
			AVLoutput << "		Summary Table" << endl << "		" << testName << endl;	AVLoutput << "	BST	AVL	Splay" << endl;
			SplayOutput << "		Summary Table" << endl << "		" << testName << endl;	SplayOutput << "	BST	AVL	Splay" << endl;
			sumfile << "		Summary Table" << endl << "		" << testName << endl;	sumfile << "\n	BST	AVL	Splay" << endl;
			for (int i = 0; i < 3; i++)
			{
				if (i == 0) {
					BSToutput << "Search	"; AVLoutput << "Search	"; SplayOutput << "Search	"; sumfile << "Search	";
				}
				if (i == 1) {
					BSToutput << "Insert	"; AVLoutput << "Insert	"; SplayOutput << "Insert	"; sumfile << "Insert	";
				}
				if (i == 2) {
					BSToutput << "Delete	"; AVLoutput << "Delete	"; SplayOutput << "Delete	"; sumfile << "Delete	";
				}
					
				for (int j = 0; j < 3; j++)
				{
					BSToutput << treeOperations[i][j] << "	";
					AVLoutput << treeOperations[i][j] << "	";
					SplayOutput << treeOperations[i][j] << "	";
					sumfile << treeOperations[i][j] << "	";
				}
				BSToutput << endl; AVLoutput << endl; SplayOutput << endl; sumfile << endl;
			}

			BSTTotal = treeOperations[0][0] + treeOperations[1][0] + treeOperations[2][0];	//adds up totals of the tests
			AVLTotal = treeOperations[0][1] + treeOperations[1][1] + treeOperations[2][1];
			SplayTotal = treeOperations[0][2] + treeOperations[1][2] + treeOperations[2][2];

			BSToutput << "-------------------------------------------------" << endl;
			BSToutput << "Total	" << BSTTotal << "	" << AVLTotal << "	" << SplayTotal << endl;

			AVLoutput << "-------------------------------------------------" << endl;
			AVLoutput << "Total	" << BSTTotal << "	" << AVLTotal << "	" << SplayTotal << endl;

			SplayOutput << "-------------------------------------------------" << endl;
			SplayOutput << "Total	" << BSTTotal << "	" << AVLTotal << "	" << SplayTotal << endl;

			sumfile << "-----------------------------------------------" << endl;
			sumfile << "Total	" << BSTTotal << "	" << AVLTotal << "	" << SplayTotal << endl << endl;
			sumfile << "\n-------------------ALL TOTALS------------------";
			sumfile << "\n---------------------BELOW---------------------\n" << endl;
		
		int testNum = 0;
		cout << "Do you want to do another test? Enter 'Y' for yes and 'N' for no" << endl;
		cin >> yn;
		if (cin.fail()) {
			cout << "enter a Y for yes or N for no ";
			cin.ignore(100, '\n');
		}

		//print to summary file
		sumfile << "		Summary" << endl << "		Operation Counts" << endl << endl;		//prints the overall summary table to the summary file
		sumfile << "Test#	TestName	BST	AVL	Splay" << endl;
		sumfile << testNum + 1 << "	" << testName << "	" << BSTTotal << "	" << AVLTotal << "	" << SplayTotal << endl;
		testNum++;
		totalOperations[0] += BSTTotal;	//adds totals into an array to keep track
		totalOperations[1] += AVLTotal;
		totalOperations[2] += SplayTotal;
	} while (yn == 'Y' || yn == 'y');
	sumfile << "-----------------------------------------------" << endl;
	sumfile << "Total			" << totalOperations[0] << "	" << totalOperations[1] << "	" << totalOperations[2] << endl;	//prints totals

	//close all the files
	ifs1.close();
	ifs2.close();
	BSToutput.close();
	AVLoutput.close();
	SplayOutput.close();
	sumfile.close();
	return 0;
}

