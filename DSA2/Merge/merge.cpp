#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Global matrix for dynamic programming approach
int matrix[1001][1001];

// Function to determine if C is a valid merge of A and B
string mergeCheck(string A, string B, string C){
    int lengthA = A.length();
    int lengthB = B.length();
    int lengthC = C.length();

    // Check if the total length of A and B matches C
    if (lengthA + lengthB != lengthC){
        return "*** NOT A MERGE ***";
    }
    else {
        // Initialize matrix to 0
        matrix[0][0] = 1;

        for (int j = 0; j <= lengthB; j++){
            for (int i = 0; i <= lengthA; i++){
                if (matrix[i][j]){
                    if (A[i] == C[i + j] && !matrix[i + 1][j]){
                        matrix[i + 1][j] = 2;
                    }
                    if (B[j] == C[i + j] && !matrix[i][j + 1]){
                        matrix[i][j + 1] = 3;
                    }
                }
            }
        }

        // Modify C to make chars from A uppercase for the right merge
        if (matrix[lengthA][lengthB]){
            while (lengthA > 0 && lengthB >= 0){
                if (matrix[lengthA][lengthB] == 2){
                    C[lengthA + lengthB - 1] = toupper(C[lengthA + lengthB - 1]);
                    lengthA--;
                }
                else{
                    lengthB--;
                }
            }
            return C;
        }
        else{
            return "*** NOT A MERGE ***";
        }
    }
}

// Function to open and check input/output files
void openFiles(ifstream& input, ofstream& output) {
    string inFile, outFile;
    cout << "Enter name of input file: ";
	cin >> inFile;
    cout << "Enter name of output file: ";
	cin >> outFile;

    input.open(inFile);

    if (!input.is_open()) {
        cout << "Unable to open input file." << endl;
        exit(1);
    }

    output.open(outFile);

    if (!output.is_open()) {
        cout << "Unable to open output file." << endl;
        input.close();
        exit(1);
    }
}

int main() {
    ifstream input;
    ofstream output;
    openFiles(input, output);

    string A, B, C;
    while (input >> A >> B >> C) {
        for (int i = 0; i < A.size() + 1; i++) {
            for (int j = 0; j < B.size() + 1; j++) {
                matrix[i][j] = 0;
            }
        }
        output << mergeCheck(A, B, C) << '\n';
    }
    
    input.close();
    output.close();
    return 0;
}