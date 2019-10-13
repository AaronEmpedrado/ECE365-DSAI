// THIS IS THE PROVIDED CODE FOR PROGRAM #2, DSA 1, SPRING 2019

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

void insertionSort(list<Data *> &l);
void radixSort(list<Data *> &l);
void radixStringSort(list<Data *> &l);
bool cmp(const Data *a, const Data *b);
unsigned int getNum(string &s);
int stringtoint(string &s);

unsigned int ssn[1010000];
Data *pointers[1010000];
int counterArr1[256] = {0};
int counterArr2[256] = {0};
int counterArr3[256] = {0};
int counterArr4[256] = {0};
int counterArr5[676] = {0};
Data *arr1[256][10000];
Data *arr2[256][10000];
Data *arr3[256][10000];
Data *arr4[256][10000];
Data *arr5[676][10000];
unsigned int iarr1[256][10000];
unsigned int iarr2[256][10000];
unsigned int iarr3[256][10000];

void sortDataList(list<Data *> &l) {
    int i = 0;
    int size = l.size();
    for (auto at : l) {
        pointers[i] = at;
        i++;
    }

    i = 0;
    if (pointers[0]->firstName == pointers[1]->firstName && pointers[0]->firstName != pointers[size-1]->firstName){
        insertionSort(l);
    }
    else if (pointers[0]->firstName == pointers[size-1]->firstName && pointers[0]->lastName == pointers[size-1]->lastName){
        for (auto a : l) {
            ssn[i] = getNum(a->ssn);
            i++;
        }
        radixSort(l);
    }
    else if (size <= 101000) {
        radixStringSort(l);
    } else {
        radixStringSort(l);
    }

}

unsigned int getNum(string &s) {
    unsigned int num;
    num = (s[0]-'0')*100000000 + (s[1]-'0')*10000000 + (s[2]-'0')*1000000 + (s[4]-'0')*100000 + (s[5]-'0')*10000 + (s[7]-'0')*1000 + (s[8]-'0')*100 + (s[9]-'0')*10 + (s[10]-'0')*1;
    return num;
}

int stringtoint(string &s) {
    return (s[0]-'A')*26 + (s[1]-'A');
}

void merge(Data *a[], int left_low, int left_high, int right_low, int right_high)
{
    int length = right_high-left_low+1;
    Data* temp[length];
    int left = left_low;
    int right = right_low;
    for (int i = 0; i < length; ++i) {
        if (left > left_high)
            temp[i] = a[right++];
        else if (right > right_high)
            temp[i] = a[left++];
        else if (a[left]->ssn <= a[right]->ssn)
            temp[i] = a[left++];
        else
            temp[i] = a[right++];
    }

    for (int i=0; i< length; ++i)
        a[left_low++] = temp[i];
}

void merge_sort(Data *a[], int low, int high) {
    if (low >= high)                  //Base case: 1 value to sort->sorted
        return;                         //(0 possible nly on initial call)
    else {
        int mid = (low + high)/2;       //Approximate midpoint*
        merge_sort(a, low, mid);        //Sort low to mid part of array
        merge_sort(a, mid+1, high);     //Sort mid+1 to high part of array
        merge(a, low, mid, mid+1,high); //Merge sorted subparts of array
    }
}

void insertion_sort(Data *a[], int left, int right) {
    for(int i=left+1;i <= right; ++i){
        auto temp_data = a[i];
        auto tmp1 = temp_data->ssn;
        auto j = i - 1;
        while (j >= left && a[j]->ssn > tmp1){
            a[j+1] = a[j];
            --j;
        }
        a[j+1] = temp_data;
    }
}

void bubble_sort(Data *a[], int left, int right) {
    int i, j;
    for (i = left; i < right; i++) {
        for (j = left; j < right - i; j++) {
            if (a[j]->ssn > a[j+1]->ssn) {
                swap(a[j],a[j+1]);
            }
        }
    }
}

void insertionSort(list<Data *> &l){
    int size = l.size();
    int left = 0;
    int right = 0;
    int i = 0;
    string tmp1;

    while (left < size){
        while(i < size-1 && (pointers[i]->firstName == pointers[i+1]->firstName)){
            ++right;
            ++i;
        }

        //insertion_sort(pointers, left, right);
        //merge_sort(pointers, left, right);
        bubble_sort(pointers, left, right);

        ++right;
        left = right;
        i = left;
    }
    auto it = l.begin();
    for(i = 0; i < size; i++) (*it++) = pointers[i];
}

/*void insertionSort(list<Data *> &l){
    int size = l.size();
    int left = 0;
    int right = 0;
    int i = 0;
    int j;
    Data *temp_data;
    string tmp1;

    while (left < size){
        while(i < size-1 && (pointers[i]->firstName == pointers[i+1]->firstName)){
            ++right;
            ++i;
        }

        if (right-left+1 <= 3) {
            insertion_sort(pointers, left, right);
            //bubble_sort(pointers, left, right);
        } else {
            merge_sort(pointers, left, right);
        }

        ++right;
        left = right;
        i = left;
    }
    auto it = l.begin();
    for(i = 0; i < size; i++) (*it++) = pointers[i];
} */

void radixSort(list<Data *> &l){
    list<Data *>::iterator it;
    int size = l.size();
    int bufcount, curval;
    int i,j;
    string ssn1;

    for (i = 0; i < size; ++i) {
        curval = ssn[i] & 0xFF;
        arr1[curval][counterArr1[curval]] = pointers[i];
        iarr1[curval][counterArr1[curval]] = ssn[i];
        ++counterArr1[curval];
    }

    for (i = 0 ; i < 256 ; ++i ) {
        bufcount = counterArr1[i];
        for (j = 0 ; j < bufcount ; ++j) {
            curval = (iarr1[i][j] >> 8) & 0xFF;
            arr2[curval][counterArr2[curval]] = arr1[i][j];
            iarr2[curval][counterArr2[curval]] = iarr1[i][j];
            ++counterArr2[curval];
        }
    }

    for (i = 0 ; i < 256 ; ++i ) {
        bufcount = counterArr2[i];
        for (j = 0 ; j < bufcount ; ++j) {
            curval = (iarr2[i][j] >> 16) & 0xFF;
            arr3[curval][counterArr3[curval]] = arr2[i][j];
            iarr3[curval][counterArr3[curval]] = iarr2[i][j];
            ++counterArr3[curval];
        }
    }

    for (i = 0 ; i < 256 ; ++i ) {
        bufcount = counterArr3[i];
        for (j = 0 ; j < bufcount ; ++j) {
            curval = (iarr3[i][j] >> 24) & 0xFF;
            arr4[curval][counterArr4[curval]] = arr3[i][j];
            ++counterArr4[curval];
        }
    }

    for (i = 0, it = l.begin() ; i < 256; ++i ) {
        bufcount = counterArr4[i];
        for (j = 0 ; j < bufcount ; ++j, ++it)
            *it = arr4[i][j];
    }
}

void radixStringSort(list <Data *> &l) {
    list<Data *>::iterator it;
    int size = l.size();
    int bufcount, curval;
    int i,j;

    for (i = 0; i < size; ++i) {
        curval = stringtoint(pointers[i]->lastName);
        arr5[curval][counterArr5[curval]] = pointers[i];
        ++counterArr5[curval];
    }
    for(i = 0; i<676; i++){
        std::stable_sort(&arr5[i][0],&arr5[i][counterArr5[i]], cmp);
    }

    for (i = 0, it = l.begin() ; i < 676; ++i ) {
        bufcount = counterArr5[i];
        for (j = 0 ; j < bufcount ; ++j, ++it)
            *it = arr5[i][j];
    }

}

bool cmp(const Data *a, const Data *b) {
    if (a->lastName < b->lastName) return true;
    else if(a->lastName == b->lastName && a->firstName < b->firstName) return true;
    else if(a->lastName == b->lastName && a->firstName == b->firstName && a->ssn < b->ssn) return true;
    return false;
}




