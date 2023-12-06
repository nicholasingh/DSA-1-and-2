//Nicholas Singh
//DSA 1
//Project 2

//This program processes commands for creating and manipulating stacks
//and queues of integers, doubles, and strings. The program reads
//input from an input file and writes output to an output file by doing
//push and pop operations on created singly linked lists.

#include<iostream>
#include<fstream>
#include<list>
#include<string>
#include<sstream>
using namespace std;

//Base Class for implementing a simple linked list called SimpleList
template <class T>
class SimpleList{
private: //Private Node class with a field for data and a pointer to the next node
	struct Node {
		T data;
		Node* next;
        Node (T temp){
            data = temp;
        }
	};
          
protected: //Protected data members that we don't want others to access for the lists
    Node* head;
	Node* tail;
	string listName;
	void insertStart(T data);
    void insertEnd(T data);
    T removeStart();

public:
	SimpleList(): head(nullptr), tail(nullptr){}; //Initializing start and end nodes

	string getName() {
		return listName;
	}

	virtual void push(T data) = 0; //Public pure virtual member functions for push and pop
	virtual T pop() = 0;

	bool notEmpty() { //Checks if the list is empty
		return head;
	}
};

//Add a node to the start of a list
template <class T>
void SimpleList<T>::insertStart(T data){
	Node* newNode = new Node(data);
	newNode->data = data;
	newNode->next = head;
	head = newNode;
}

//Add a node to the end of a list
template <class T>
void SimpleList<T>::insertEnd(T data){
	Node* newNode = new Node(data);
	newNode->next = nullptr;
        if (head == nullptr){
            tail = newNode;
            head = newNode;
        }
        else{
            tail->next = newNode;
            tail = newNode;
        };
}

//Remove a node from the start
template <class T>
T SimpleList<T>::removeStart(){
		T value;
        value = head->data;
		Node* tempNode = head;
		head = head->next;
		delete tempNode;
		return value;
}

//Derived class from SimpleList that implements pop/push for Stacks
template <class T>
class Stack:public SimpleList<T> {
public:
	Stack(string name) {
		this->listName = name;
	}
	void push(T data) {
		this->insertStart(data);
	}
	T pop() {
		return this->removeStart();
	}
};

//Derived class from SimpleList that implements pop/push for Queues
template<class T>
class Queue:public SimpleList<T> {
public:
	Queue(string name){
		this->listName = name;
	}
	void push(T data) {this->insertEnd(data);
	}
	T pop() {
		return this->removeStart();
	}
};

//Function that looks through listnames of similar type and returns a pointer to the object if it's found or a nullptr if not
template <class T>
SimpleList<T>* search(list<SimpleList<T>*>& ltype, string listName){
	class list<SimpleList<T>*> ::iterator it;
	for (it = ltype.begin(); it != ltype.end(); ++it){
		if (listName == (*it)->getName()){
			return *it;
		}
	}
	return nullptr;
}

//Developed a class that implements the procedure by creating lists and the push/pop features
class Implement {
private:
    list<SimpleList<int> *> listSLi; // all integer stacks and queues
    list<SimpleList<double> *> listSLd; // all double stacks and queues
    list<SimpleList<string> *> listSLs; // all string stacks and queues

public:
    string ifile, ofile;
    ifstream input;
    ofstream output;
    
    //Uses the file stream to ask user for input and output so they can be opened easier
    Implement(){
    cout << "Enter name of input file: ";
    cin >> ifile;
    cout << "Enter name of output file: ";
    cin >> ofile;
    input.open(ifile);
    output.open(ofile);
	}

    //Checks to see if the file has reached the end (using this later to loop through file)
	bool fileEnd() {
		return input.eof();
    }

    //Function that creates lists but first uses the search function to see if it exists first
	void createList(char match, string name) {
		string type;
		input >> type;
		output << "PROCESSING COMMAND: create " << name << " " << type << "\n";

		//Searches and creates list for ints
        if (match == 'i'){
			SimpleList<int>* find = search(listSLi, name);
			if (find==nullptr){
                SimpleList<int>* pSLi;
                if (type == "stack"){
                    pSLi = new Stack<int>(name);}
                else {
                    pSLi = new Queue<int>(name);}
                listSLi.push_front(pSLi);
			}
			else{
                output << "ERROR: This name already exists!"<<"\n";	}
		}

        //Searches and creates list for doubles
		else if (match == 'd') {
            SimpleList<double>* find = search(listSLd, name);
			if (find==nullptr){
                SimpleList<double>* pSLd;
                if (type == "stack"){
                    pSLd = new Stack<double>(name);}
                else {
                    pSLd = new Queue<double>(name);}
                listSLd.push_front(pSLd);
			}
			else{
                output << "ERROR: This name already exists!"<<"\n";}
		}

        //Searches and creates list for strings
		else {
            SimpleList<string>* find = search(listSLs, name);
			if (find==nullptr){
                SimpleList<string>* pSLs;
                if (type == "stack"){
                    pSLs = new Stack<string>(name);}
                else {
                    pSLs = new Queue<string>(name);}
                listSLs.push_front(pSLs);
			}
			else{
                output << "ERROR: This name already exists!"<< "\n";}
		}
	}

    //Pop function for all the types
    void pop(char match, string name) {
        output << "PROCESSING COMMAND: pop " << name << "\n";

		//Specificlly for ints
        if (match == 'i'){
            SimpleList<int>* find = search(listSLi, name);
            if (find != nullptr){
                if (find->notEmpty()){
                    output << "Value popped: " << find->pop() << "\n";}
                else{
                    output << "ERROR: This list is empty!" << "\n";}
                }
            else{
                 output << "ERROR: This name does not exist!" << "\n";}
            }

	    //Specificlly for doubles
        else if (match == 'd') {
            SimpleList<double>* find = search(listSLd, name);
            if (find != nullptr){
                if (find->notEmpty()){
                    output << "Value popped: " << find->pop() << "\n";}
                else{
                    output << "ERROR: This list is empty!" << "\n" ;}
                }
            else{
                 output << "ERROR: This name does not exist!" << "\n" ;}
            }

        //Specificlly for strings
        else if (match == 's') {
            SimpleList<string>* find = search(listSLs, name);
            if (find!=nullptr){
                if (find->notEmpty()){
                    output << "Value popped: " << find->pop() << "\n";}
                else {
                    output << "ERROR: This list is empty!" << "\n";}
                }
            else{
                output << "ERROR: This name does not exist!" << "\n";}
        }
    }

    //Push function for all the types
	void push(char match, string name){
		output << "PROCESSING COMMAND: push " << name << " ";

		//Specificlly for ints
		if (match == 'i') {
			int data;
			input >> data;
			output << data << "\n";
			SimpleList<int>* find= search(listSLi, name);
			if (find != nullptr) {
				find->push(data);
			}
			else {
				output << "ERROR: This name does not exist!"<<"\n";}
		}

		//Specificlly for doubles
		else if (match == 'd') {
			double data;
			input >> data;
			output << data << "\n";
			SimpleList<double>* find = search(listSLd, name);
			if (find != nullptr) {
				find->push(data);}
			else {
				output << "ERROR: This name does not exist!"<<"\n";}
		}

		//Specificlly for strings
		else if(match == 's'){
			string data;
			input >> data;
			output << data << "\n";
			SimpleList<string>* find = search(listSLs, name);
			if (find != nullptr){
				find->push(data);}
			else {
				output << "ERROR: This name does not exist!"<<"\n";}
		}
	}
};

int main() {
	Implement file;
	if (file.input.is_open()){
		while (!file.fileEnd()){ //Loops through the file until the end 
            char match;
			string command, name;
			file.input >> command;
			file.input >> name;
            string firstLetter = name.substr(0, 1); //Finds the letter with the corresponding match of type
            if (firstLetter == "i") {
				match = 'i';}
			else if (firstLetter == "d") {
				match = 'd';}
			else {
				match = 's';}
			if (command == "create") {
				file.createList(match, name);}
            else if (command == "pop") {
				file.pop(match, name);}
            else if (command == "push") {
				file.push(match, name);}
		}
		file.input.close();
	}
	else{
        file.output << "TARGET INPUT FILE: READ ERROR" << "\n";
	}
}