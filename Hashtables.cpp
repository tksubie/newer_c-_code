/******************************************************************************

Thaine Koen

4/16/2023


A menu driven program that creates a hash table using an array. Gives the user the following options and should run in an infinite loop:

1) Insert key
2) Delete key
3) Display hash table
4) Find key

The program calculates the location of the key using a hash function.
The program also prompts the user when there is a collision and when the
hash table is full.

*******************************************************************************/



#include<iostream>
#include<vector>

using namespace std;

class dataElem {		//data element

private:

public:
	int elem = 0;		//data for hash table (key)

	dataElem() {};		//default constructor
	dataElem(int key) : elem(key) {};		//constructor

};

class hash_table : public dataElem {
private:
	vector<dataElem*> hashTable;		//hash table vector
	int tableSize;		//table size
	dataElem* pnull;		//null data item for deletion

public:

	hash_table(int size) : tableSize(size) {		//create hash table

		tableSize = size;
		hashTable.resize(tableSize);		//resize the vector
		for (int i = 0; i < tableSize; i++) { //fill vector with space with NULL
			hashTable[i] = NULL;
		}
		pnull = new dataElem(-1);		//make a deleted item -1
	}

	void print() {		//print the hash table
		cout << "-Hash Table-" << "\n";
		for (int i = 0; i < tableSize; i++) {
			if (hashTable[i] != NULL && hashTable[i]->elem != -1) {		//print populated values
				cout << hashTable[i]->elem << " ";
			}
			else {		//if the space is empty display empty
				cout << " empty ";
			}
		}
		cout << "\n";
	}

	int countElem() {		//count valid values
		int count = 0;

		for (int i = 0; i < tableSize; i++) {		//loop table
			if (hashTable[i] != NULL && hashTable[i]->elem != -1) {
				count++;
			}
		}
		return count;
	}

	int hashFunction(int key) {		//hash function
		return key % tableSize;
	}

	void insert(dataElem* tempdata) {

		if (countElem() == tableSize) {		//check if table is full
			cout << "The Hash Table is full. Delete Items.";
		}

		else {
			int key = tempdata->elem;	//extract key
			int hashValue = hashFunction(key);		//put key through hash function


			while (hashTable[hashValue] != NULL && hashTable[hashValue]->elem != -1) //loop untill find a null cell or a cell with -1 = empty
			{

				++hashValue;		//go next 
				hashValue %= tableSize;		//wraparound if needed
				cout << " *Collision* ";

			}
			hashTable[hashValue] = tempdata;  //insert
		}
	}

	dataElem* find(int key) {
		int hashValue = hashFunction(key);		//put the key through hash function



		while (hashTable[hashValue] != NULL)		//check the whole table
		{
			if (hashTable[hashValue]->elem == key)
				return hashTable[hashValue];

			++hashValue;		//go next
			hashValue %= tableSize;		//wraparound if needed

		}
		return NULL;
	}

	dataElem* Delete(int key) {
		int hashValue = hashFunction(key);		//put the key through hash function

		while (hashTable[hashValue] != NULL)		//check the whole table
		{
			if (hashTable[hashValue]->elem == key) {
				dataElem* temp = hashTable[hashValue]; //save
				hashTable[hashValue] = pnull;	//delete replace with tempnull
				return temp;
			}
			else {
				++hashValue;		//go next
				hashValue %= tableSize;		//wraparound if needed
			}
		}
		return NULL;		//not found, can't delete

	}
};

int main() {

	cout << "Create a Hash Table!" << "\n\n";
	int size;
	cout << "How big of a table would you like?" << "\n";
	cin >> size;

	hash_table* Week13HT = new hash_table(size);		//create hastable
	dataElem* temp;	//data pointer

	int x;		//menu selection
	bool valid = true;

	cout << "-Menu-" << "\n";
	cout << "1 - Insert key." << "\n";
	cout << "2 - Delete key. " << "\n";
	cout << "3 - Print Hash Table. " << "\n";
	cout << "4 - Find key. " << "\n";

	do {
		cout << "Menu Selection - ";
		cin >> x;

		switch (x) {

		case 1:
			//Insert key
			int d;	// data
			cout << "\n" << "Insert into the Hash Table" << "\n";
			cout << "Value - ";
			cin >> d;

			temp = new dataElem(d);

			Week13HT->insert(temp);
			cout << "\n";
			valid = true;
			break;

		case 2:
			//Delete key
			int fd; //key to delete
			cout << "Delete the key: " << "\n";
			cin >> fd;

			Week13HT->Delete(fd);
			cout << "\n";
			valid = true;
			break;

		case 3:
			//Display hash table

			Week13HT->print();
			cout << "\n";
			valid = true;
			break;

		case 4:
			//Find key
			int fk;		//key to be found
			cout << "Find the key: ";
			cin >> fk;


			if (Week13HT->find(fk) != NULL) {
				cout << fk << " Found";
			}
			else {
				cout << fk << " Not Found.";
			}

			cout << "\n";
			valid = true;
			break;

		default:
			std::cout << "Invalid input - program ended..." << "\n";
			valid = false;
		}
	} while (valid);

	return 0;
}
