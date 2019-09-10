#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include <string>
#include <fstream>
#include <iostream>
#include <ostream>
#include <cassert>
#include <vector>
#include <cmath>
#include "Location.h"
#include <algorithm>

using namespace std;

const string PRIMES_FILE = "primes.txt";

const int DEFAULT_SIZE = 13;
const int PRIME_U_BOUND = 1000000000;
const int OUTPUT_PRIMES = 26;

/*
    Note: Number of allowed tries for hashing is given by tableSize / 2.
*/

//Uses quadratic probing
class HashTable {

private:
    vector<Location> information;
    vector<bool> filled;
    int tableSize;
    int currentSize;

    vector<int> primes;
    int currentIndex;

    void rehash();

public:
    HashTable();

    void insert(const Location& info);
    bool find(const Location& info);
    int hash(const Location& info);

    int getTotalLocations();

    void printAll(ostream& os = cout);
    void printAlphabetically(ostream& os = cout);
    void printCityState(ostream& os = cout);
    void printBoundingBoxes(ostream& os = cout);
    void printToVector(vector<Location>& info);
};

void generateFormattedPrimes();

#endif // HASHTABLE_H_INCLUDED
