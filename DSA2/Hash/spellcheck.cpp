//Nicholas Singh
//DSA 2

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include "hash.h"
using namespace std;

void loadDictionary(const string& dictFile, hashTable* hash) {
    ifstream dictionary;
    dictionary.open(dictFile);
    if (dictionary.fail()){
        cerr << "Error: Failed to open dictionary file" << endl;
        _Exit(10);
    }

    //Convert all capital letters in dictionary file to lowercase
    string line;
    int i;
    while (getline(dictionary, line)){
        for (i = 0; i <= line.length(); i++){
            line[i] = tolower(line[i]);
        }
        hash->insert(line, nullptr);
    }
    dictionary.close();
}

void spellCheck(const string& inputFile, const string& outputFile, hashTable* hash) {
    ifstream input;
    ofstream output;
    input.open(inputFile);
    if (input.fail()){
        cerr << "Error: Failed to open input file"<< endl;
        _Exit(10);
    }

    output.open(outputFile);
    if (output.fail()){
        cerr << "Error: Failed to open output file"<< endl;
        _Exit(10);
    }

    // Convert all letters to lowercase
    string word = "";
    string line;
    int i;
    unsigned long lineNo = 1;
    char c;
    int asciiValue;

    while (getline(input, line)) {
        for (int i = 0; i <= line.length(); i++){ //check every word letter by letter
            c = tolower(line[i]);
            asciiValue = c;
            if ((asciiValue >= 48) && (asciiValue <= 57) || (asciiValue >= 97) && (asciiValue <= 122) || (asciiValue == 39) || (asciiValue == 45)){ //ignore special characters
                word += c;
            }
            else if ((word.length() > 0)){
                if (word.length() > 20){ //max length of a word is 20 characters
                    output << "Long word at line " << lineNo << ", starts: " << word.substr(0, 20) << endl;
                }
                else if (hash->contains(word) == false){    //report unknown words
                    output << "Unknown word at line " << lineNo << ": " << word << endl;
                }
                word = "";
            }
        }
        lineNo++;
    }

    input.close();
    output.close();
}

int main(){
    string dictFile, inputFile, outputFile;

    cout << "Enter name of dictionary: ";
    cin >> dictFile;

    clock_t start = clock();
    hashTable *hash = new hashTable(50000);
    loadDictionary(dictFile, hash);
    clock_t end = clock();
    cout << "Total time (in seconds) to load dictionary: " << ((double) (end-start)) / CLOCKS_PER_SEC << endl;

    cout << "Enter name of input file: ";
    cin >> inputFile;

    cout << "Enter name of output file: ";
    cin >> outputFile;

    start = clock();
    spellCheck(inputFile, outputFile, hash);
    end = clock();
    cout << "Total time (in seconds) to check document: " << ((double) (end-start)) / CLOCKS_PER_SEC << endl;

    return 0;
}