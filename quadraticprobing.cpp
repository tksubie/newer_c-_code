/******************************************************************************

Thaine Koen

4/22/2023

The program demonstrates quadratic hash probing when a collision occurs.

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
		pnull = new dataElem(-1);		//make a deleted item -1 which is initial values for table
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
		int col = 0;		//counting collisions

		if (countElem() == tableSize) {		//check if table is full
			cout << "The Hash Table is full. Delete Items.";
		}

		else {
			for (int key = 0; key < tableSize; key++) {		//go through the hash table
				key = tempdata->elem;	//extract key
				int hashValue = hashFunction(key);		//put key through hash function

				if (hashTable[hashValue] == NULL || hashTable[hashValue]->elem == -1) {		//if no collisions
					hashTable[hashValue] = tempdata;  //insert
					
				}

				else {  //collisions

					col++;
					for (int j = 0; j < tableSize; j++) {		//go through hash table with quadratic hash

						int quadhashing = (hashValue + (j * j)) % tableSize;		//find new hash value

						if (hashTable[quadhashing] == NULL || hashTable[quadhashing]->elem == -1) {
							hashTable[quadhashing] = tempdata;		//insert value
							break;
						}



					}
				}
			}
			cout << "There were " << col << " collisions.";
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