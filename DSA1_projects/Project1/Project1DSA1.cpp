// Nicholas Singh
//The code below was created with the goal of receiving an input file that has a list of foobars
//with specifc types (foobar, foo, and bar). The order of the names is important because the
//bottom of the list represents the first position and goes up from there. Depending on the type of foobar,
//some are stronger than others. Foobars have a normal strength as their position, foos have a strength of 
//their position * 3, and bars have a strength of their position + 15. This program loops through the input
//file to determine each foobars' strength and then outputs the list with their matching strength into the 
//output file provided by the user. Specifcally to know how this code works with classes, objects, vectors,
//and pointers, you can see below.

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Foobar { //creating the superclass "Foobar"
public:
    Foobar(string name) : name(name), position(0) {} //constructor in base class to set the name and also the position to 0

    string getName() const { //get the name of the foobars
        return name;
    }

    int getPosition() const { //gets the current poisition that the foobar is in
        return position;
    }

    void setPosition(int pos) { //set the position of each Foobar object to its index in the vector foobars in reverse order
        position = pos;
    }

    virtual int getStrength() const { //used with the getPosition to calculate the strength of each foobar
        return position; //same as getPosition because the default of Foobar is its current position
    }

private: //name of each foobar and its current position in a line stored in private
    string name;
    int position;
};

class Foo : public Foobar { //creating subclass, Foo, of Foobar
public:
    Foo(string name) : Foobar(name) {} 

    int getStrength() const override { //Override the base class and establishing that each foo type has strength of position * 3
        return getPosition() * 3;
    }
};

class Bar : public Foobar { //creating subclass, Bar, of Foobar
public:
    Bar(string name) : Foobar(name) {}

    int getStrength() const override { //Override the base class and establishing that each bar type has strength of position + 15
        return getPosition() + 15;
    }
};

//Function that takes an input filename as an argument and returns a vector of foobar pointers
vector<Foobar *> readInputFile(const string &inputFileName) {
    vector<Foobar *> foobars;
    ifstream inputFile(inputFileName);
    if (!inputFile) { //Error checking if input file isn't valid
        cerr << "Error: Unable to open input file " << inputFileName << endl;
        return foobars;
    }
    string line;
    while (getline(inputFile, line)) { //get each line of input file
        istringstream iss(line);
        string type, name;
        iss >> type >> name; //gets the type (foobar, foo, bar) and name (name of the foobar)
        //matches the type from each line and adds it to the foobars vector with its name
        if (type == "foo") {
            foobars.push_back(new Foo(name));
        } else if (type == "bar") {
            foobars.push_back(new Bar(name));
        } else {
            foobars.push_back(new Foobar(name));
        }
    }
    inputFile.close();
    return foobars;
}

//Function to loop through the vector backwards to update the position of each foobar
void updateFoobarStrengths(vector<Foobar *> &foobars) {
    int numOfFoobars = foobars.size();
    for (int i = 0; i < numOfFoobars; i++) {
        foobars[i]->setPosition(numOfFoobars - i);
    }
}

//Function to loop through and write output of names and strengths to output file
void writeOutputFile(const string &outputFileName, vector<Foobar *> &foobars) {
    ofstream outputFile(outputFileName);
    if (!outputFile) { //Error checking if output file isn't valid
        cerr << "Error: Unable to open output file " << outputFileName << endl;
        return;
    }
    for (Foobar* foobar : foobars) {
        outputFile << foobar->getName() << " " << foobar->getStrength() << "\n"; //instructing how to write each line in the output file
    }
    outputFile.close();
}

int main() {
    //Prompting user to enter input and output file names for program's use
    string inputFileName, outputFileName;
    cout << "Enter the name of the input file: ";
    cin >> inputFileName;
    cout << "Enter the name of the output file: ";
    cin >> outputFileName;

    //Order of the functions created earlier and being called in their needed use
    vector<Foobar *> foobars = readInputFile(inputFileName);
    updateFoobarStrengths(foobars);
    writeOutputFile(outputFileName, foobars);

    return 0;
}