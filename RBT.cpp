
/******************************************************************************
Thaine Koen
04/8/2023

Inserting the following keys 
(30,28,21,11,17,4) into a Red Black Tree.  Then the user can choose to output and gives a 
color-coded diagram of the tree.
*******************************************************************************/

#include <iostream>
#define COUNT 10

using namespace std;


class node {
public:
    enum Color { red, black };		//enum for red and black in the RBT

	int data;	//data in node
	enum Color color;		//color for node red or black

	node* parent;	//node parent
	node* left;		//node left child
	node* right;	//node right child

	node() : color(red), data(0), parent(NULL), left(NULL), right(NULL) {};		//constuctor


	~node() {		//deconstructor

		std::cout << data << " - deconstructor";
	};


	const char* getColorName(enum Color color)		//function to print color name from enum
	{
		switch (color)
		{
		case red: return "Red";
		case black: return "Black";
		}
	}

	void printNode() {		//print the node information
	

		std::cout << "[ " << getColorName(color) << ", " << data << " ]";
	}

};

class tree : public node {

private:

	node* root;		//pointer for the root of the tree
    node* tempNULL;       //tempnull pointer

public:

    tree() : tempNULL(NULL), root(NULL) {};		// constructor
        
      
    void insert(int z)		//insert a value into the tree
    {
		node* temproot = root;
		node * tempNULL = NULL;

        node* tempnode = new node;
		tempnode->data = z;
		tempnode->left = NULL;
		tempnode->right = NULL;
		tempnode->color = red;
        
        if (root == NULL)		//if root is NULL insert value into root
        {
            root = tempnode;
			tempnode->parent = NULL;
        }
        else                   //if root is not null
        {
            while (temproot != NULL)
            {
				tempNULL = temproot;
                if (temproot->data < tempnode->data)		//if new data is greater than the root go right
					temproot = temproot->right;
                else   //else go left
					temproot = temproot->left;
            }
			tempnode->parent = tempNULL;		 
            if (tempNULL->data < tempnode->data)		//if tempnode greater than tempnull
				tempNULL->right = tempnode;		//make tempnode right child
            else
				tempNULL->left = tempnode;
        }
        insertfix(tempnode);		//call to fix the insertion
    }

    void insertfix(node* temp)		//create the red black tree and fix the insertion
    {
        node* u;
        if (root == temp)		//if root is temp then make it black
        {
            temp->color = black;
            return;
        }
        while (temp->parent != NULL && temp->parent->color == red)		//do while parent of new node is red
        {
            node* grandparent = temp->parent->parent;
            if (grandparent->left == temp->parent)
            {
                if (grandparent->right != NULL)		//if right is not null check
                {
                    u = grandparent->right;
                    if (u->color == red)		//if color of right child is red
                    {
                        temp->parent->color = black;	//set children as black
                        u->color = black;		//set children as black
						grandparent->color = red;		//set color to red
                        temp = grandparent;
                    }
                }
                else 
                {
                    if (temp->parent->right == temp)		//if temp is right
                    {
                        temp = temp->parent;
                        leftrotate(temp);
                    }
                    temp->parent->color = black;	//set color of temp parent to black
					grandparent->color = red;		//grandparent red
                    rightrotate(grandparent);		//right rotate
                }
            }
            else
            {
                if (grandparent->left != NULL)		//if left is not null check
                {
                    u = grandparent->left;
                    if (u->color == red)		//if color of child is red
                    {
                        temp->parent->color = black;	//children to black
                        u->color = black;		//children to black
						grandparent->color = red;		//set to red
                        temp = grandparent;
                    }
                }
                else
                {
                    if (temp->parent->left == temp) //if temp is left child, then make parent temp
                    {
                        temp = temp->parent;
                        rightrotate(temp);     //rotate right
                    }
                    temp->parent->color = black;	//set color of temp parent to black
					grandparent->color = red;		//grandparent red
                    leftrotate(grandparent);		//left rotate
                }
            }
            root->color = black;		//root is always black
        }
    }
    
	void leftrotate(node* newNode)		//rotate left
	{
		if (newNode->right == NULL)
			return;
		else
		{
			node* temp = newNode->right;
			if (temp->left != NULL)
			{
				newNode->right = temp->left;		//change right child of newnode to left child of temp
				temp->left->parent = newNode;
			}
			else
				newNode->right = NULL;

			if (newNode->parent != NULL) {

				temp->parent = newNode->parent;		//temp parent is now newnode parent
			}

			if (newNode->parent == NULL) { //if parent of newnode is null set temp as root

				root = temp;
			}

			else
			{
				if (newNode == newNode->parent->left) {		//if newnode is a left child 

					newNode->parent->left = temp;		//left child of newnode is temp
				}
				else
					newNode->parent->right = temp;		//else is a right child of newnode is temp
			}
			temp->left = newNode;
			newNode->parent = temp;
		}
	}
	void rightrotate(node* newNode)		//rotate right
	{
		if (newNode->left == NULL) {
			return;
		}
		else
		{
			node* temp = newNode->left;
			if (temp->right != NULL)		
			{
				newNode->left = temp->right;		//change left child of newnode to right child of temp
				temp->right->parent = newNode;
			}
			else
				newNode->left = NULL;

			if (newNode->parent != NULL) {		
				temp->parent = newNode->parent;		//temp parent is now newnode parent
			}
			if (newNode->parent == NULL) { //if parent of newnode is null set temp as root
				root = temp;
			}
			else
			{
				if (newNode == newNode->parent->left) {
					newNode->parent->left = temp;		//left child of newnode is temp
				}
				else
					newNode->parent->right = temp;		//else is a right child of newnode is temp
			}
			temp->right = newNode;
			newNode->parent = temp;
		}
	}


	void print2D(node* root, int space)		// Function to print binary tree in 2D
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
		print2D(root, 0);
	}
};


int main() {

	tree* week12 = new tree;		//create pointer of week12 tree
	int x;		//menu selection
	bool valid;


	std::cout << "Insert and find a node in the Binary Tree!" << "\n\n";

	do {
		std::cout << "1 - Insert a Node." << "\n";
		std::cout << "2 - Display Red Black Tree. " << "\n";
		std::cout << "Menu Selection - ";
		std::cin >> x;

		switch (x) {

		case 1:
			//insert a node with a key value and data value
			int v;	//value
			std::cout << "\n" << "Insert an integer into the tree." << "\n";
			std::cout << "Value - ";
			std::cin >> v;
		

			week12->insert(v);
			std::cout << "\n";
			valid = true;
			break;

		case 2:
			//Print the tree
			
			week12->printtree();
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