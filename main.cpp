#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "LinkedList.h"
#include "LinkedListInterface.h"	

using namespace std;

#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define VS_MEM_CHECK _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#else
#define VS_MEM_CHECK
#endif		

int main(int argc, char* argv[]) {
	VS_MEM_CHECK	//implementing memory check

		if (argc < 3) {
			cerr << "Please provide name of input and output files";
			return 1;
		}
	cout << "Input file: " << argv[1] << endl;
	ifstream in(argv[1]);
	if (!in) {
		cerr << "Unable to open " << argv[1] << " for input";
		return 2;
	}
	cout << "Output file: " << argv[2] << endl;
	ofstream out(argv[2]);
	if (!out) {
		in.close();
		cerr << "Unable to open " << argv[2] << " for output";
		return 3;
	}

	LinkedList<string> myList;		//instantiation of templated linked list

	for (string line; getline(in, line);) {		//iterate through the file line by line to parce each line 
		string item1, item2;
		if (line.size() == 0) continue;
		out << endl << line;
		istringstream iss(line);
		iss >> item1;
		if (item1 == "Insert") {		//check for instances of "insert" and perform insertion function
			while (iss >> item2) {		//push the second word of the line into item2 and insert item2 to the linked list
				myList.push_front(item2);
			}
		}
		else if (item1 == "PrintList") {	//check for instances of "printlist" and perform toString function
			out << myList.toString();		//print out the linked list by calling toString function
		}
		else if (item1 == "Clear") {	//check for instances of "clear" and clear the linked list
			myList.clear();				//erase the entire linked list by calling the clear function
			out << " OK";
		}
		else if (item1 == "Iterate") {		//check for instances of "iterate" and perform iterate function
			LinkedList<string>::Iterator iter = myList.begin();		//set our iterator equal to the head of myList
			if (iter == myList.end()) {				//if the iterator is equal to NULL then output empty
				out << " Empty!";
			}
			else {
				while (iter != myList.end()) {
					out << endl << " [" << *iter << "]";		//if iterator is not NULL, then output each item the iterator points to until NULL
					++iter;
				}
			}
		}
		else if (item1 == "InsertAfter") {		//check for instances of "InsertAfter" and perform intertion after function
			string item3;
			iss >> item2;						//takes the second word as the word to insert after item3
			iss >> item3;						//takes the third word in the line for what position to insert item2 after
			LinkedList<string>::Iterator iterFirst = myList.begin();
			LinkedList<string>::Iterator iterLast = myList.end();
			LinkedList<string>::Iterator iterFound = myList.find(iterFirst, iterLast, item3);	//uses find function to locate iter position of word
			if (iterFound == iterLast) {
				out << " Not Found";
			}
			else {
				myList.insert_after(++iterFound, item2);		//call the inser_after function to put the new word after item3 in the linked list
				out << " OK";
			}
		}
		else if (item1 == "InsertBefore") {			//check for instances of "InsertBefore" and performs the insertion before function
			string item3;							//same system as above for insert before
			iss >> item2;
			iss >> item3;
			LinkedList<string>::Iterator iterFirst = myList.begin();
			LinkedList<string>::Iterator iterLast = myList.end();
			LinkedList<string>::Iterator iterFound = myList.find(iterFirst, iterLast, item3);
			if (iterFound == iterLast) {
				out << " Not Found";
			}
			else {
				myList.insert_after(iterFound, item2);
				out << " OK";
			}
		}
		else if (item1 == "Find") {		//checks for instances of "find" in the input file and performs the find function
			iss >> item2;				//takes this item as waht to find
			LinkedList<string>::Iterator iterFirst = myList.begin();
			LinkedList<string>::Iterator iterLast = myList.end();
			LinkedList<string>::Iterator iterFound = myList.find(iterFirst, iterLast, item2);	//calls the find function similar as above
			if (iterFound == iterLast) {
				out << " Not Found";
			}									//outputs Not Found if NULL was returned, else outputs OK if found
			else {
				out << " OK";
			}
		}
		else if (item1 == "Erase") {			//checks for instances of "erase" and performs erase function on linked list
			iss >> item2;				//takes in the word that is called to be erased
			LinkedList<string>::Iterator iterFirst = myList.begin();
			LinkedList<string>::Iterator iterLast = myList.end();
			LinkedList<string>::Iterator iterFound = myList.find(iterFirst, iterLast, item2);	//calls find to get position of word to be erased
			if (iterFound == iterLast) {
				out << " Not Found";
			}
			else {				//outputs Not Found if NULL was returned from find function, else calls erase
				myList.erase(iterFound);
				out << " OK";
			}
		}
		else if (item1 == "Replace") {		//checks for isntances of "replace" and performs replace function
			string item3;
			iss >> item2;
			iss >> item3;
			LinkedList<string>::Iterator iterFirst = myList.begin();
			LinkedList<string>::Iterator iterLast = myList.end();
			LinkedList<string>::Iterator iterFound = myList.find(iterFirst, iterLast, item2);
			myList.replace(iterFirst, iterLast, item2, item3);		//after finding position of iterator with find, calls replace with old and new items
			out << " OK";
		}
	}
	in.close();

	return 0;
}
