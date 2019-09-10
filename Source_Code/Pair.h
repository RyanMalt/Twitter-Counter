#ifndef PAIR_H_INCLUDED
#define PAIR_H_INCLUDED
#include <iostream>

using namespace std;

//Ordered by second coordinate first
struct FreqContainer{
    int frequency;
    string data;

    FreqContainer(const string& word, const int& number) {data = word; frequency = number;}

    friend bool operator<(const FreqContainer& first, const FreqContainer& second);
};


#endif // PAIR_H_INCLUDED
