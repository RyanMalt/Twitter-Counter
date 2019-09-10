#ifndef TRIETREE_H_INCLUDED
#define TRIETREE_H_INCLUDED
#include <iostream>
#include <ostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cassert>
#include "Pair.h"

using namespace std;

const int NUM_POINTERS = 41;
const bool HTML_PARSING = false;
const int FAILED = -1;

//This is the alphabet of valid characters.  Make sure to update index conversion
//functions whenever this is changed.
enum INDEX{
    ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
    A, B, C, D, E, F, G, H, I, J, K,
    L, M, N, O, P, Q, R, S, T, U, V,
    W, X, Y, Z, APOST, AT,
    POUND, UNDERSCORE, INVALID
};

struct TrieTreeNode {
    TrieTreeNode** alphabet;
    bool validWord;
    int wordCount;

    TrieTreeNode(bool validWord = false);//
    ~TrieTreeNode();//

    void reset();//

    void printAlphabetically(string path, ostream& os);//
    void convertToVector(vector<FreqContainer>*, string word);//
};

class TrieTree {
    private:
        TrieTreeNode* root;

        int uniqueElements;
        int totalElements;
        int discardedInput;

        bool isValid(const string& word);
    public:
        TrieTree();//
        TrieTree(const string& word );//
        ~TrieTree();//

        void reset();//

        void insert(const string& word);//
        void makeInvalid(const string& word);//

        bool inDictionary(const string& word);//
        int getWordCount(const string& word);//Handles hashtags or
        int getMentions(const string& word);//

        int getUniqueElements() {return uniqueElements;} //
        int getTotalElements() {return totalElements;} //
        int getDiscardedInput() {return discardedInput;} //

        void printAlphabetically(ostream& os = cout); //
        void printBiggestWordCount(int listSize = -1, ostream& os = cout); //
        void printMentions(int listSize = -1, ostream& os = cout); //
        void printHashtagCount(int listSize = -1, ostream& os = cout); //

        void convertToVector(vector<FreqContainer>*);//
};

int convertCharToIndex(char letter);//

char convertIndexToChar(int index);//

#endif // TRIETREE_H_INCLUDED
