
/******************************************************************************
Thaine Koen
04/2/2023

Program where the user can insert nodes into the tree with a key and value and then
the user can see if a key value has a value or not in an infinite loop. The user
can also traverse Inorder and PREorder with the tree as well as view the tree as 
a two dimensional view in the output.
*******************************************************************************/

#include <iostream>
#define COUNT 6

class node {
public:

	
	int data;	//data in node

	node* left;		//node left child
	node* right;	//node right child

	node() : data(0), left(NULL), right(NULL) {};		//constuctor

	~node() {		//deconstructor

		std::cout << data << " - deconstructor";
	};


	void printNode() {		//print the node information

		std::cout << "[ " << data << " ]";
	}

};

class tree {

private:

	node* root;		//pointer for the root of the tree

public:

	tree() : root(NULL) {};		// constructor


	void insertNode( int userdata) {		//insert a node into the tree
		node* newNode = new node;		//create new node
		newNode->data = userdata;

		if (root == NULL) {
			root = newNode;
		}
		else {

			node* current = root;		//make current root
			node* parent;		//keep track of where in the tree 


			while (true) {		//loop while current has a value

				parent = current;

				if (userdata < current->data) {		//if user key is less than current key travese left

					current = current->left;

					if (current == NULL) {		//if the left final traverse current equals null input new node
						parent->left = newNode;
						return;
					}
				}

				else {		//if the user key is greater traverse right
					current = current->right;

					if (current == NULL) {		//if the final traverse ends up being null add new node
						parent->right = newNode;
						return;

					}

				}

			}
		}
	}


	node* findNode(int userdata) {
		node* current = root;		//put root into new node

		if (current == NULL) {
			std::cout << "The tree is empty." << "\n";
			return current;
		}

		while (current->data != userdata) {		//continue loop if the key does not equal user given key


			if (userdata < current->data) {		//if the user key is less then the current key, traverse to the left
				current = current->left;

			}
			else {
				current = current->right;		//if the user key is more then the current key, traverse to the right

			}

			if (current == NULL) {		//if no child and not found
				std::cout << "Not Found." << "\n";
				return NULL;
			}

		}
		std::cout << "FOUND node ";
		current->printNode();		//print the node data
		std::cout << "\n";
		return current;		//return current for the given key


	}
	

	void inorder(node* treenode) {		//inorder - LEFT ROOT RIGHT
		if (treenode == NULL) {
			return;
		}

		inorder(treenode->left);		//LEFT

		treenode->printNode();		//print data ROOT
		std::cout << " - ";

		inorder(treenode->right);		//RIGHT
	}

	void printinorder() {		//print inorder
		inorder(root);
	}

	void preorder(node* treenode) {		//pre order - ROOT LEFT RIGHT
		if (treenode == NULL) {		//check if null
			return;
		}

		treenode->printNode();		//print data ROOT

		std::cout << " - ";

		inorder(treenode->left);	//LEFT

		inorder(treenode->right);		//RIGHT
	}
	
	void printpreorder() {		//print preorder
		preorder(root);
	}
	

	void print2D(node* root, int space)		// Function to print binary tree in 2D using inorder
	{
		if (root == NULL) {
			return;
		}

			space += COUNT;		// Increase distance between levels

			print2D(root->right, space);		//RIGHT


			std::cout << '\n';		// Print current node after space

			for (int i = COUNT; i < space; i++)		//print node
				std::cout << " ";
			root->printNode();

			print2D(root->left, space);		//LEFT
		
	}

	void printtree() {		//print the tree with space initialized at 0
		print2D(root,0);
	}
};


int main() {

	tree* week10 = new tree;		//create pointer of week10 tree
	int x;		//menu selection
	bool valid;


	std::cout << "Insert and find a node in the Binary Tree!" << "\n\n";

	do {
		std::cout << "1 - Insert a Node (must be an integer)." << "\n";
		std::cout << "2 - Find a Node by its data value. " << "\n";
		std::cout << "3 - print INorder traversal of the tree. " << "\n";
		std::cout << "4 - print PREorder traversal of the tree. " << "\n";
		std::cout << "5 - print the tree. " << "\n";
		std::cout << "Menu Selection - ";
		std::cin >> x;

		switch (x) {

		case 1:
			//insert a node with a key value and data value
			int d;	// data
			std::cout << "\n" << "Insert an integer into the tree.(first value input will be ROOT)" << "\n";
			std::cout << "Value - ";
			std::cin >> d;

			week10->insertNode(d);
			std::cout << "\n";
			valid = true;
			break;

		case 2:
			//find a node by the key given
			int fd; //find data
			std::cout << "\n" << "To find an integer in the tree, input data item to be found." << "\n";
			std::cout << "Data # - ";
			std::cin >> fd;

			week10->findNode(fd);
			std::cout << "\n";
			valid = true;
			break;

		case 3:
			//print in order traversal
			std::cout << "- INorder traversal - ";
			week10->printinorder();
			std::cout << "\n";
			valid = true;
			break;

		case 4:
			//print preorder traversal
			std::cout << "- PREorder traversal- ";
			week10->printpreorder();
			std::cout << "\n";
			valid = true;
			break;

		case 5:
			//print tree
			std::cout << "- DISPLAY in 2d - ";
			week10->printtree();
			std::cout << "\n";
			valid = true;
			break;

		default:
			std::cout << "Invalid input - program ended..." << "\n";
			valid = false;
		}
	} while (valid);


	return 0;
}