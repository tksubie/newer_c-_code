/******************************************************************************
Thaine Koen
Due: 4/28/2023

A supermarket has 9 cashiers. A customer arrives every 3 seconds and a customer 
leaves every 6 seconds from a random queue. The goal of the program is to put the 
next arriving customer in the shortest queue out of the 9 cashier queues. The 
program loops infinitely to simulate the passing of a certain amount 
of time. 

*******************************************************************************/

#include <iostream>
#include <vector>

class queue {
private:
	
	int *cashier;		//pointer array for the cashier queue
	int msize;		//size of queue
	int front;		//beginning value
	int rear;		//end value
	int elems;		//number of elements

public:

	queue(int size) : msize(size), front(0), rear(-1), elems(0) {		//constructor
		cashier = new int[msize];		
	}

	bool isFull() {		//is the queue full?
		return elems == msize;
	}

	bool isEmpty() {		//is the queue empty?
		return (elems == 0);
	}
		
	int getSize() {		//get the size of the queue
		return elems;
	}

	int insert(int customer) {		//insert at the rear
		
		if (!isFull()) {		//insert if not full
			rear = (rear + 1) % msize;		//insert at the end of the cashier line
			elems++;
			cashier[rear] = customer;
			return 1;
			}
		else {
			return 0;
		}
	}

	int remove() {		//remove item from the queue at the front

		if (!isEmpty()) {		//delete if not empty
			front = (front + 1) % msize;		//remove from the front of the queue
			elems--;
			return 1;
		}
		else {
			return 0;
		}
	}

	void print() {
		if (isEmpty()) {		//if empty
			std::cout << "Line is empty." << "\n";
		}
		else {		//if not print

			for (int i = 0; i < getSize(); i++) {
				std::cout << "*";
			}
			std::cout << "\n";
		}
	}
};

int main() {

	const int counters = 9;		//have 9 counters

	queue* cashiers[counters];

	int maxCust = 10;		//max number of customers at a cashier

	for (int i = 0; i < counters; i++) {
		cashiers[i] = new queue(maxCust);
	}

	int numCust = 0;
	int time = 10;		//time passing
	int timestamp = 1;

	while (numCust < time) {
		numCust++;			//increase num of customers as time increases
		int addCust = 0; //insert customer
		int count = 0;		//counter

		while (count < counters) {		//loop until shortest queue is found and add customer 
			int smallestqueue = count;

			for (int i = count + 1; i < counters; i++) {
				if (cashiers[i]->getSize() < cashiers[smallestqueue]->getSize()) {
					smallestqueue = i;
				}
			}

			addCust = cashiers[smallestqueue]->insert(numCust);		//add customer
			

			if (addCust == 1) //if the customer is added break the loop
				break;
			
			count++;
		}

			int timeSpent = 1;		//delay


			for (int i = 0; i < timeSpent; i++) {	//loop every second

				std::cout << " ** Customer added ** timestamp = " << timestamp << " sec" << "\n";

				for (int i = 0; i < counters; i++) {		//loop and print cashiers up to 9

					std::cout << "\n" << "Cashier " << (i + 1) << " - ";
					cashiers[i]->print();
				}

				int randCashier = rand() % (counters - 1); //random range of 0 to 9 for cashier picking of deletion

				if (cashiers[randCashier]->remove() != 0) {

					std::cout << "\n" << "** Customer leaves ** timestamp = " << (timestamp + 1) << " sec" << "\n";

					for (int i = 0; i < counters; i++) {		//print the cashiers
						std::cout << "\n" << "Cashier " << (i + 1) << " - ";
						cashiers[i]->print();
					}
				}
			}
		
		timestamp++;
	}


	return 0;
}