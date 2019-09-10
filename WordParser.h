#ifndef WORDPARSER_H_INCLUDED
#define WORDPARSER_H_INCLUDED
#include "TrieTree.h"
#include "HashTable.h"

const string INVALID_WORDS = "invalidWords.txt";
const string NO_GEO = "NONE";

const string TWITTER_FILE = "tweets.txt";
const string OUTPUT_FILE = "output.txt";

const int PRINT_ALL = -1;

const char PRINT_BY_FREQ = 'f';
const char PRINT_BY_ALPHA = 'a';
const char PRINT_INVALID = 'i';

/*
    NOTE: By default, all methods report by frequency then alphabetically
*/

class Tweetalyzer{

private:
    TrieTree wordCounter;
    TrieTree invalidWords;

    TrieTree authors;

    HashTable location;

public:
    Tweetalyzer();

    void insertWord(const string& word);
    void insertAuthor(const string& word);
    void insertLocation(const Location& loc);

    void parseFile(const string& fileName = TWITTER_FILE);
    void parseCommands(char** args, int numArgs);  //To be improved later.  Support for cmdline args.

    void reportWordCount(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);
    void reportHashtags(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);
    void reportAuthors(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);
    void reportCityState(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);
    void reportBoundingBoxes(int listSize = PRINT_ALL, ostream& os = cout);
    void reportFullLocations(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);
    void reportMentions(int listSize = PRINT_ALL, const char args = PRINT_BY_FREQ, ostream& os = cout);

    int findWordCount(const string& word);
    int findAuthorCount(const string& word);
    int findMentionCount(const string& word);
    bool findLocation(const Location& loc);

    int getTotalWords();
    int getTotalUniqueWords();
    int getTotalDiscardedWords();

    int getTotalAuthors();
    int getTotalUniqueAuthors();
    int getTotalDiscardedAuthors();

    int getTotalLocations();
};

#endif // WORDPARSER_H_INCLUDED
