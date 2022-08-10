/*
 * 2250_proj_5.cpp
 *
 *  Created on: May 2, 2021
 *      Author: Kayla
 */

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

class BinaryTree {
	private:
		struct TreeNode{
			//stores a letter or combination of letters to a node
			string chars = " ";
			//int count for letter or combination frequency
			int count = 1;
			//current node's left pointer
			TreeNode *left;
			//current node's right pointer
			TreeNode *right;
		};

		//root pointer
		TreeNode *root;

		//private binary tree operations
		void insert(TreeNode *&, TreeNode *&);
		void destroySubTree(TreeNode *);
		void displayInOrder(TreeNode *) const;

	public:
		//constructor
		BinaryTree()
			{ root = nullptr; }

		//destructor
		~BinaryTree()
			{ destroySubTree(root); }

		//public binary tree operations
		void insertNode(string);
		bool searchNode(string);
		void displayInOrder() const
			{ displayInOrder(root); }
};

//function to validate file name and open file
void openFile(fstream &);

int main()
{
	//creates binary tree object
	BinaryTree myTree;
	//holds current character from read file
	char temp;
	//string to hold file text
	string text = "";
	//variables to hold user entered substring length and text length
	int sub = 0, textLen = 0;
	//stores file name for text document to be processed
	fstream dataFile;
	//calls open file function
	openFile(dataFile);

	//takes the text from dataFile and puts all of the non whitespace characters in a string
	while (dataFile >> temp)
	{
		if (!isalpha(temp) || temp == '\0')
			continue;
		else
			text += tolower(temp);
	}

	//sets textLen variable
	textLen = text.length();

	//prompts user to enter the length of subsequences to test for
	cout << "What length of subsequences would you like to test for?\n";
	cin >> sub;
	//verify subsequence length is valid
	while (sub < 1)
	{
		cout << "Please enter a valid subsequence length (1 or greater).\n";
		cin >> sub;
	}

	//nested for loop to test the text; outer loop increments the subsequence length and inner
	//loop parses through the text from the document
	for (int i = 1; i <= sub; i++)
	{
		for (int j = 0; j < textLen; j++)
		{
			//holds the current subsequence string
			string substr = "";
			string test = "";
			//handles operations for subsequences of length 1
			if (i == 1)
			{
				substr += text[j];
				if (myTree.searchNode(substr) == true || substr == "")
					continue;
				else
					myTree.insertNode(substr);
			}
			//handles operations for subsequences with length greater than 1
			else
			{
				//builds subsequences from text for testing
				for (int k = 1; k <= i; k++)
				{
					if ((j+i) < textLen)
					{
						substr += text[j + k];
						test += text[j + k];
					}
				}
				//if the current substring matches the string being test, adds the substring to the tree if it does
				//not already have a node or increments the existing node
				if (substr == test)
				{
					if (myTree.searchNode(substr) == true || substr == "")
						continue;
					else
						myTree.insertNode(substr);
				}
			}
		}
	}

	//displays the completed binary tree
	myTree.displayInOrder();

	//closes file after operations complete
	dataFile.close();

	return 0;
}

//prompts user to enter file name and tests that file opens correctly; will prompt user to
//enter valid file name if it encounters an error
void openFile(fstream &myFile)
{
	//string to hold user entered file name
	string fileName = " ";

	cout << "Please enter the file name (without file type extension).\n";

	cin >> fileName;

	//adds .txt extension to user entered file name
	fileName += ".txt";

	myFile.open(fileName, ios::in);

	//if user enters invalid file name, prompts user to enter a valid file name
	while (!myFile)
	{
		cout << "Error opening " << fileName << ".\n"
				<< "Please enter a valid file name (without file type extension) and try again.\n";

		cin >> fileName;
		fileName += ".txt";

		myFile.open(fileName, ios::in);
	}

	cout << fileName << " successfully opened.\n";
}

void BinaryTree::insert(TreeNode *&nodePtr, TreeNode*&newNode)
{
	if (nodePtr == nullptr)
		nodePtr = newNode; 					//inserts the new node
	else if (newNode->chars < nodePtr->chars)
		insert(nodePtr->left, newNode);		//search the left branch
	else
		insert(nodePtr->right, newNode);	//search the right branch
}

void BinaryTree::insertNode(string str)
{
	TreeNode *newNode = nullptr;	//points to a new node

	//creates a new node to store string str
	newNode = new TreeNode;
	newNode->chars = str;
	newNode->left = newNode->right = nullptr;

	//inserts the node
	insert(root, newNode);
}

void BinaryTree::destroySubTree(TreeNode *nodePtr)
{
	if (nodePtr)
	{
		if (nodePtr->left)
			destroySubTree(nodePtr->left);
		if (nodePtr->right)
			destroySubTree(nodePtr->right);
		delete nodePtr;
	}
}

bool BinaryTree::searchNode(string str)
{
	TreeNode *nodePtr = root;

	while (nodePtr)
	{
		if (nodePtr->chars == str)
		{
			//incrememts the count for the node when a matching substring is found before returning true
			nodePtr->count++;
			return true;
		}
		else if (str < nodePtr->chars)
			nodePtr = nodePtr->left;
		else
			nodePtr = nodePtr->right;
	}

	return false;
}

void BinaryTree::displayInOrder(TreeNode *nodePtr) const
{
	if (nodePtr)
	{
		displayInOrder(nodePtr->left);
		cout << nodePtr->chars << ": \t" << nodePtr->count << endl;
		displayInOrder(nodePtr->right);
	}
}
