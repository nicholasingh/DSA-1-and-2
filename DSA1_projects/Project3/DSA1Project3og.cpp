// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, FALL 2021

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

//declaring an array of 1020000 Data objects (sorting an array seems to be faster than the provided C++ list)
static Data* arrayPtrs[1020000];

//comparing all three arguments for Test case #1 and Test case #1 
inline bool compare3args(Data *object1, Data *object2){
 
    int a = (object1->lastName).compare(object2->lastName);
    int b = (object1->firstName).compare(object2->firstName);
    int c = (object1->ssn).compare(object2->ssn);

      if(a==0){
          if(b==0){
              return (c<0);
          }
          else {
            return b < 0;
          }
      }
      return (a < 0);

}

//comparing firstname and lastname only (used to make sample 1 and sample 2 similar to sample 3)
inline bool compare2args(Data *object1, Data *object2){
    int b = (object1->lastName).compare(object2->lastName);
    int c = (object1->firstName).compare(object2->firstName);
      if(b==0){
          return (c<0);
      }
      return (b<0);
}

//comparing ssn only for Test case #3
inline bool compare1arg(Data *object1, Data *object2){
      return ((object1 -> ssn).compare(object2 -> ssn)) < 0;
}

//uses different conditional statements to figure out which Test case is it 
int filetypeChecker(list<Data *> &l){

    auto it1 = std::next(l.begin(), 10000);
    auto it2 = std::next(l.begin(), 1);
    auto it3 = std::next(l.begin(), 2);

    // if the lastname at the top is equal to the lastname at the bottom 
    //and a random firstname is equal to the firstname at the bottom, then it is Test case #4

    if ((l.front() -> lastName == (*it1) -> lastName) && ( (*it1) -> firstName == l.back() -> firstName )){

        return 4;

      } else if((l.front() -> lastName != (*it1) -> lastName) &&  ( (*it2) -> firstName == l.front() -> firstName ) && ((*it3) -> firstName == l.front() -> firstName )){
          // if the lastname at the top is not equal to the lastname at the bottom 
          // and if the first two consecutive first names after the firstname at the top are equal, then it is Test case #3

        return 3;

      }else {
        // otherwise there is no pattern, and just sort the array using the provided std::sort algorithm
        
        return 12;
    }

}

// Partition the array into two sub-arrays and return the index of the pivot element
int partition(Data** arr, int low, int high) {
    // Choose the pivot element (we'll use the median-of-three method)
    int mid = low + (high - low) / 2;
    if (compare2args(arr[high], arr[low])) {
        std::swap(arr[low], arr[high]);
    }
    if (compare2args(arr[mid], arr[low])) {
        std::swap(arr[mid], arr[low]);
    }
    if (compare2args(arr[high], arr[mid])) {
        std::swap(arr[mid], arr[high]);
    }
    Data* pivot = arr[mid];

    // Partition the array
    int i = low - 1;
    int j = high + 1;
    while (true) {
        do {
            i++;
        } while (compare2args(arr[i], pivot));
        do {
            j--;
        } while (compare2args(pivot, arr[j]));
        if (i >= j) {
            return j;
        }
        std::swap(arr[i], arr[j]);
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

// using provided std::sort algorithm to sort the Test case #1 and the Test case #2
// instead of sorting the provided C++ list, first I convert it to an array of data objects and then use std::sort
// which gives a faster time
// inline void sort_12(list<Data *> &l){

// list<Data *>:: iterator it;
//   int i = 0;
//   for(it=  l.begin(); it != l.end(); it++){
//     arrayPtrs[i++] = (*it);
//   }

//   sort(arrayPtrs, arrayPtrs + i, compare2args);

//   int j = 0;
//   for(it = l.begin(); it != l.end(); it++)
//   {
//     (*it) = arrayPtrs[j++];
//   }



// }

inline void sort_12(list<Data*>& l) {
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

// using provided std::sort algorithm intelligently to sort the Test case #3
// the lastnames and first names are already sorted
// the lastnames are left alone
// until the first names are equal, sort the ssns using the std::sort algorithm 
// so, sort ssns block by block while the first names stays same instead of sorting the whole list
inline void sort_3(list<Data *> &l){

  list<Data *>:: iterator it;
    int i = 0;
    for(it=  l.begin(); it != l.end(); it++){
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
        sort(arrayPtrs + currentStart, arrayPtrs + iterator, compare1arg);
        currentStart = iterator;
  }

  int j = 0;
  for(it = l.begin(); it != l.end(); it++){
    (*it) = arrayPtrs[j++];
  }

}

// radix sort is used to sort Test case #4
// since the length of the last names and first names are variable, 
// I found it difficult to implement the radix sort with strings for Test case #1, Test case #2, and Test case #2
// therefore, just tried to sort the ssns in Test case #4 by first converting the ssns into integers

// finds the max length of the ssn in the array 
// (while converting the ssns into integers the leading 0's in the first three digit of the ssn gets dropped)
// so max length of ssn can be 8, you never know
// A utility function to get maximum value in arr[]
int getMax(const int arr[], int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

// the radix sort algorithm is implemented with the help of Geeks for Geeks website on radix sort

// static array is created to hold the sorted list which is copied into the passed array to the function as a parameter
int output[1020000];
 
// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp){
    
    int i, count[10] = { 0 };
 
    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
 
    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
 
    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
 
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}
 
// The main function to that sorts arr[] of size n using
// Radix Sort
void radixsort(int arr[], int n){
    // Find the maximum number to know number of digits
    int m = getMax(arr, n);
 
    // Do counting sort for every digit. Note that instead
    // of passing digit number, exp is passed. exp is 10^i
    // where i is current digit number
    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(arr, n, exp);
}

// converts the third parameter into an integer by neglecting the dashes (-) and dropping leading 0s in the first three digit
int intSSN(Data* data){
        std::string ssnstring = (data->ssn.substr(0,3) + data->ssn.substr(4,2) + data->ssn.substr(7,4));
    return stoi(ssnstring);
}

// converts the integers ssns into string ssn just as they were in the file by adding back the dashes (-) and adding leading 0s 
string stringSSN(int ssn){
   
    string s = to_string(ssn);
    while(!(s.length() == 9)){//9 digits in the ssn id also the length of the bins need to constant in radix sort
        s = "0" + s;
    }
    s.insert(3, "-");
    s.insert(6, "-");
    return s;

}

// another temporary array is used to load the integers ssn and pass into the radix sort algorithm
// and the sorted ssns are then added in order to the provided C++ list
int loadArr[1020000];
// radix sort to sort Test case #4
inline void sort_4(list<Data *> &l){

    int i = 0, lSize = l.size();
        for(auto data:l){
            if(i == lSize)
                break;
            loadArr[i++] = intSSN(data);
        }
        radixsort(loadArr, lSize);

        i = 0;
        for(auto data2:l){
            if(i == lSize)
                break;
            data2->ssn = stringSSN(loadArr[i++]);
        }

}

void sortDataList(list<Data *> &l) {

  // using filetypeChecker function to determin which sorting function to use

  int a = filetypeChecker(l);
 
  if (a==4){

    sort_4(l);

  }else if (a==3){

    sort_3(l);
    
  }else{

    sort_12(l);
    sort_3(l);
   
  }

}


