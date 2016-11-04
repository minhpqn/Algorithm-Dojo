/*
  inversion.cpp
  Calculate the number of inversions in an array
  array of integer numbers is read from a file
  See definition of inversion on:
  [1] https://en.wikipedia.org/wiki/Inversion_%28discrete_mathematics%29
  [2] https://www.cs.umd.edu/class/fall2009/cmsc451/lectures/Lec08-inversions.pdf
  Date: 2015/11/09
  Author: minhpham
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cmath>
using namespace std;

// read integer array from file
// each line contains an integer number
void readIntArray(vector<int>& intArray, const string& fileName)
{
    ifstream fin(fileName, ifstream::in);
    int num;
    while ( fin >> num ) {
        intArray.push_back(num);
    }
    fin.close();
}

long int naiveMethod(const vector<int>& intArray)
{
    long int numInversions = 0;
    
    for (unsigned int i = 0; i < intArray.size() - 1; i++) {
        for (unsigned int j = i+1; j < intArray.size(); j++) {
            if ( intArray[i] > intArray[j] ) {
                numInversions++;
            }
        }
    }
    return numInversions;
}

// merge and count the number of inversions for two sorted array
// intArray[p..q] and intArray[q+1..r]
long int mergeCount(vector<int>& intArray, int p, int q, int r)
{
    vector<int> aux;
    for (unsigned int k = p; k <= r; k++) {
        aux.push_back(intArray[k]);
    }

    long int count = 0;
    int i = p, j = q+1;
    for (unsigned int k = p; k <= r; k++) {
        if (i > q) {
            intArray[k] = aux[j-p];
            j++;
        }
        else if (j > r) {
            intArray[k] = aux[i-p];
            i++;
        }
        else if (aux[j-p] < aux[i-p]) {
            intArray[k] = aux[j-p];
            j++;
            count += q - i + 1;
        }
        else {
            intArray[k] = aux[i-p];
            i++;
        }
    }
    return count;
}

// fast divide-and-conquer algorithm
long int countInversions(vector<int>& intArray, int p, int r)
{
    if ( p < r ) {
        int q = floor( (p + r)/2 );
        long int leftCount  = countInversions(intArray, p, q);
        long int rightCount = countInversions(intArray, q+1, r);
        return leftCount + rightCount + mergeCount(intArray, p, q, r);
    }
    else {
        return 0;
    }
}

void printArray(const vector<int>& intArray, int l, int r) {
    cout << "(" << l << ", " << r << "): ";
    for (unsigned int k = l; k <= r; k++) {
        cout << intArray[k] << "  ";
    }
    cout << endl;
}

int main()
{
    vector<int> intArray;
    readIntArray(intArray, "./IntegerArray.txt");

    long int numInversions = countInversions(intArray, 0, intArray.size()-1);

    cout << "Number of inversions: " << numInversions << endl;

    return 0;
}






