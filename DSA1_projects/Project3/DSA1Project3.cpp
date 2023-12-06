// THIS IS THE PROVIDED CODE FOR PROGRAM #3, DSA 1, SPRING 2023

#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cctype>
#include <cstdlib>

using namespace std;

// A simple class; each object holds four public fields
class Data {
public:
  string lastName;
  string firstName;
  string ssn;
};

// Load the data from a specified input file
void loadDataList(list<Data *> &l, const string &filename) {

  ifstream input(filename);
  if (!input) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // The first line indicates the size
  string line;
  getline(input, line);
  stringstream ss(line);
  int size;
  ss >> size;

  // Load the data
  for (int i = 0; i < size; i++) {
    getline(input, line);
    stringstream ss2(line);
    Data *pData = new Data();
    ss2 >> pData->lastName >> pData->firstName >> pData->ssn;
    l.push_back(pData);
  }

  input.close();
}

// Output the data to a specified output file
void writeDataList(const list<Data *> &l, const string &filename) {

  ofstream output(filename);
  if (!output) {
    cerr << "Error: could not open " << filename << "\n";
    exit(1);
  }

  // Write the size first
  int size = l.size();
  output << size << "\n";

  // Write the data
  for (auto pData:l) {
    output << pData->lastName << " " 
	         << pData->firstName << " " 
	         << pData->ssn << "\n";
  }

  output.close();
}

// Sort the data according to a specified field
// (Implementation of this function will be later in this file)
void sortDataList(list<Data *> &);

// The main function calls routines to get the data, sort the data,
// and output the data. The sort is timed according to CPU time.
int main() {
  string filename;
  cout << "Enter name of input file: ";
  cin >> filename;
  list<Data *> theList;
  loadDataList(theList, filename);

  cout << "Data loaded.\n";

  cout << "Executing sort...\n";
  clock_t t1 = clock();
  sortDataList(theList);
  clock_t t2 = clock();
  double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;

  cout << "Sort finished. CPU time was " << timeDiff << " seconds.\n";

  cout << "Enter name of output file: ";
  cin >> filename;
  writeDataList(theList, filename);

  return 0;
}

// -------------------------------------------------
// YOU MAY NOT CHANGE OR ADD ANY CODE ABOVE HERE !!!
// -------------------------------------------------

// You may add global variables, functions, and/or
// class defintions here if you wish.

//Nicholas Singh
//DSA 1
//Project 3

static Data* arrayPtrs[1020000];

//Comparing all three arguments for T1 and T2
inline bool compare3(Data *object1, Data *object2){
 
    int field1 = (object1->lastName).compare(object2->lastName);
    int field2 = (object1->firstName).compare(object2->firstName);
    int field3 = (object1->ssn).compare(object2->ssn);

      if(field1 == 0){
          if(field2 == 0){
              return (field3 < 0);
          }
          else {
            return field2 < 0;
          }
      }
      return (field1 < 0);

}

//Comparing firstname and lastname only (used to make T1 and T2 similar to T3)
inline bool compare2(Data *object1, Data *object2){
    int field1 = (object1->lastName).compare(object2->lastName);
    int field2 = (object1->firstName).compare(object2->firstName);
      if(field1 == 0){
          return (field2 < 0);
      }
      return (field1 < 0);
}

//Comparing ssn only for T3
inline bool compare1(Data *object1, Data *object2){
      return ((object1 -> ssn).compare(object2 -> ssn)) < 0;
}

//Using different conditional statements to figure out which T it is
int testCaseCheck(list<Data *> &l){

    auto it1 = next(l.begin(), 10000);
    auto it2 = next(l.begin(), 1);
    auto it3 = next(l.begin(), 2);

    //Lastname at the top = lastname at the bottom and random firstname = firstname at the bottom, then it is T4

    if ((l.front() -> lastName == (*it1) -> lastName) && ( (*it1) -> firstName == l.back() -> firstName )){

        return 4;

      } else if((l.front() -> lastName != (*it1) -> lastName) &&  ((*it2) -> firstName == l.front() -> firstName ) && ((*it3) -> firstName == l.front() -> firstName )){
          //If the lastname at the top is not equal to the lastname at the bottom 
          //and if the first two consecutive first names after the firstname at the top are equal, then it is T3

        return 3;

      }else {
        //Otherwise there is no pattern, and just sort the array with quicksort
        
        return 12;
    }

}

// inline void sort1_2(list<Data *> &l){

// list<Data *>:: iterator it;
//   int i = 0;
//   for(it=  l.begin(); it != l.end(); it++){
//     arrayPtrs[i++] = (*it);
//   }

//   sort(arrayPtrs, arrayPtrs + i, compare2);

//   int j = 0;
//   for(it = l.begin(); it != l.end(); it++)
//   {
//     (*it) = arrayPtrs[j++];
//   }
// }


// Partition the array into two sub-arrays and return the index of the pivot element
int partition(Data** arr, int low, int high) {
    // Choose the pivot element
    int mid = low + (high - low) / 2;
    if (compare2(arr[high], arr[low])) {
        swap(arr[low], arr[high]);
    }
    if (compare2(arr[mid], arr[low])) {
        swap(arr[mid], arr[low]);
    }
    if (compare2(arr[high], arr[mid])) {
        swap(arr[mid], arr[high]);
    }
    Data* pivot = arr[mid];

    // Partition the array
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (compare2(arr[i], pivot));
        do {
            j--;
        } while (compare2(pivot, arr[j]));
        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

// Sort the array using the quicksort algorithm
void quicksort(Data** arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quicksort(arr, low, pivotIndex);
        quicksort(arr, pivotIndex + 1, high);
    }
}

inline void sort1_2(list<Data*>& l) {
    int n = l.size();
    for (int i = 0; i < n; i++) {
        arrayPtrs[i] = l.front();
        l.pop_front();
    }
    quicksort(arrayPtrs, 0, n - 1);
    for (int i = 0; i < n; i++) {
        l.push_back(arrayPtrs[i]);
    }
}


//Using provided sort algorithm to sort T3
//The lastnames and first names are already sorted
//Until the first names are equal, sort the ssns using the sort algorithm 
//Sorting ssns block by block while the first names stays the same instead of sorting the whole list
inline void sort3(list<Data *> &l){

  list<Data *>:: iterator it;
    int i = 0;
    for(it = l.begin(); it != l.end(); it++){
      arrayPtrs[i++] = (*it);
    }

  int iterator = 0;
  int currentStart = 0;
  int total = l.size();

  while (currentStart < total){
        while (arrayPtrs[currentStart]->firstName == arrayPtrs[iterator]->firstName){
          iterator++;
          if(iterator> (total-1)){
            break;
          }
        }
        sort(arrayPtrs + currentStart, arrayPtrs + iterator, compare1);
        currentStart = iterator;
  }

  int j = 0;
  for(it = l.begin(); it != l.end(); it++){
    (*it) = arrayPtrs[j++];
  }

}

//Radix sort for T4

//Function to get maximum value in arr[]
int getMax(const int arr[], int n){
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

//Static array is created to hold the sorted list which is copied into the passed array to the function as a parameter
int output[1020000];
 
//A function to do counting sort of arr[] according to the digit represented by exp.
void countSort(int arr[], int n, int exp){
    
    int i, count[10] = {0};
 
    //Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    //Change count[i] so that count[i] now contains actual position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    //Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    //Copy the output array to arr[], so that arr[] now contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
//The main function to that sorts arr[] of size n using radix sort
void radixsort(int arr[], int n){
    //Find the maximum number to know number of digits
    int max = getMax(arr, n);
 
    //Do counting sort for every digit. Note that instead of passing digit number, exp is passed. exp is 10^i
    //where i is current digit number
    for (int exp = 1; max / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

//Converts the third parameter into an integer by neglecting the dashes (-) and dropping leading 0s in the first three digit
int intOfSSN(Data* data){
        string ssnstring = (data->ssn.substr(0,3) + data->ssn.substr(4,2) + data->ssn.substr(7,4));
    return stoi(ssnstring);
}

//Converts the integers ssns into string ssn just as they were in the file by adding back the dashes (-) and adding leading 0s 
string strOfSSN(int ssn){
   
    string s = to_string(ssn);
    while(!(s.length() == 9)){
        s = "0" + s;
    }
    s.insert(3, "-");
    s.insert(6, "-");
    return s;

}

int loadArr[1020000];

// radix sort to sort Test case #4
inline void sort4(list<Data *> &l){

    int i = 0, lSize = l.size();
        for(auto data:l){
            if(i == lSize)
                break;
            loadArr[i++] = intOfSSN(data);
        }
        radixsort(loadArr, lSize);

        i = 0;
        for(auto data2:l){
            if(i == lSize)
                break;
            data2->ssn = strOfSSN(loadArr[i++]);
        }

}

void sortDataList(list<Data *> &l) {

  //Using testCaseCheck function to determine which sorting function to use
  int testCase = testCaseCheck(l);
 
  if (testCase == 4){

    sort4(l);

  } else if (testCase == 3){

    sort3(l);
    
  } else{

    sort1_2(l);
    sort3(l);
  }
}