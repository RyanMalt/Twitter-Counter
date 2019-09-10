#include "TrieTree.h"

int convertCharToIndex(char letter) {
    int index = INVALID;

    letter = tolower(letter);

    if(letter >= '0' && letter <= '9') {
        index = letter - '0';
    }

    else if(letter >= 'a' && letter <= 'z') {
        index = letter - 'a' + A;
    }

    else if(letter == '\'') {
        index = APOST;
    }

    /*else if(letter == '-') {
        index = DASH;
    }*/

    else if(letter == '@') {
        index = AT;
    }

    else if(letter == '#') {
        index = POUND;
    }

    else if(letter == '_') {
        index = UNDERSCORE;
    }

    return index;
}

bool TrieTree::isValid(const string& word) {
    bool success = false;

    for(int i = 0; i < word.size() & !success; i++) {
        if(word[i] < '0' || word[i] > '9') {
            success = true;
        }
    }

    if(word.size() >= 4 && !false) {
        if(word[0] != 'h' || word[1] != 't' ||  word[2] != 't' || word[3] != 'p') {
            success = true;
        }

        else {
            success = false;
        }
    }

    return success;
}

char convertIndexToChar(int index) {
    char letter = 'a';

    if(index >= A && index <= Z) {
        letter = letter + (index - A);
    }

    else if(index >= ZERO && index <= NINE) {
        letter = '0' + index;
    }

    /*else if(index == DASH) {
        letter = '-';
    }*/

    else if(index == AT) {
        letter = '@';
    }

    else if(index == POUND) {
        letter = '#';
    }

    else if(index == APOST) {
        letter = '\'';
    }

    else if(index == UNDERSCORE) {
        letter = '_';
    }

    return letter;
}


TrieTreeNode::TrieTreeNode(bool valid) {
    alphabet = new TrieTreeNode*[NUM_POINTERS];

    for(int i = 0; i < NUM_POINTERS; i++) {
        alphabet[i] = NULL;
    }

    validWord = valid;
    wordCount = 0;
}

TrieTreeNode::~TrieTreeNode() {
    for(int i = 0; i < NUM_POINTERS; i++) {
        delete alphabet[i];
    }

    delete []alphabet;
}

void TrieTreeNode::reset() {
    validWord = false;
    wordCount = 0;

    for(int i = 0; i < NUM_POINTERS; i++) {
        if(alphabet[i] != NULL) {
            alphabet[i]->reset();
        }
    }

    return;
}

void TrieTreeNode::printAlphabetically(string word, ostream& os) {
    string oldWord = word;

    for(int i = 0; i < NUM_POINTERS; i++) {
        word = oldWord;

        if(alphabet[i] != NULL) {
            word += convertIndexToChar(i);

            if(alphabet[i]->validWord) {
                os << word << ' ' << alphabet[i]->wordCount << endl;
            }

            alphabet[i]->printAlphabetically(word, os);
        }
    }

    return;
}

void TrieTreeNode::convertToVector(vector<FreqContainer>* output, string word) {
    string oldWord = word;

    for(int i = 0; i < NUM_POINTERS; i++) {
        word = oldWord;

        if(alphabet[i] != NULL) {
            word += convertIndexToChar(i);

            if(alphabet[i]->validWord) {
                output->push_back(FreqContainer(word, alphabet[i]->wordCount));
            }

            alphabet[i]->convertToVector(output, word);
        }
    }

    return;
}

TrieTree::TrieTree() {
    root = NULL;

    uniqueElements = 0;
    totalElements = 0;
    discardedInput = 0;
}

TrieTree::TrieTree(const string& word) {
    if(word == "") {
        cout << "ERROR: Attempted insertion of empty string." << endl;
        assert(word != "");
    }

    root = new TrieTreeNode;

    TrieTreeNode* traveler = root;
    TrieTreeNode* parent = root;

    uniqueElements = 0;
    totalElements = 0;
    discardedInput = 0;

    int lastValidChar = 0;

    for(int i = 0, index = 0; i < word.size(); i++) {
        index = convertCharToIndex(word[i]);

        if(index != INVALID) {
            parent = traveler;

            traveler->alphabet[convertCharToIndex(word[i])] = new TrieTreeNode;
            traveler = traveler->alphabet[convertCharToIndex(word[i])];

            lastValidChar = i;
        }
    }

    if(convertCharToIndex(word[lastValidChar]) != INVALID) {
        parent->alphabet[convertCharToIndex(word[lastValidChar])]->wordCount++;
        parent->alphabet[convertCharToIndex(word[lastValidChar])]->validWord = true;

        uniqueElements++;
        totalElements++;
    }

    else {
        discardedInput++;
    }
}

TrieTree::~TrieTree() {
    delete root;

    uniqueElements = 0;
    totalElements = 0;
    discardedInput = 0;
}

//Does not deallocate memory, only makes all words invalid.  Resets dictionary.
void TrieTree::reset() {
    root->reset();

    uniqueElements = 0;
    totalElements = 0;
    discardedInput = 0;

    return;
}

void TrieTree::insert(const string &word) {

    if(root == NULL) {
        root = new TrieTreeNode;
    }

    if(word == "") {
        cout << "ERROR: Attempted insertion of empty string." << endl;
        assert(word != "");
    }

    if(isValid(word)) {

        TrieTreeNode* traveler = root;
        TrieTreeNode* parent = root;

        int lastValidChar = 0;

        for(int i = 0, index = 0; i < word.size(); i++) {
            index = convertCharToIndex(word[i]);

            if(index != INVALID) {
                parent = traveler;

                if(traveler->alphabet[convertCharToIndex(word[i])] != NULL) {
                    traveler = traveler->alphabet[convertCharToIndex(word[i])];
                }

                else {
                    traveler->alphabet[convertCharToIndex(word[i])] = new TrieTreeNode;
                    traveler = traveler->alphabet[convertCharToIndex(word[i])];
                }

                lastValidChar = i;
            }
        }

        if(convertCharToIndex(word[lastValidChar]) != INVALID) {
            parent->alphabet[convertCharToIndex(word[lastValidChar])]->wordCount++;
            parent->alphabet[convertCharToIndex(word[lastValidChar])]->validWord = true;

            if(parent->alphabet[convertCharToIndex(word[lastValidChar])]->wordCount == 1) {
                uniqueElements++;
            }

            totalElements++;
        }

        else {
            discardedInput++;
        }
    }

    else {
        discardedInput++;
    }
    return;
}

bool TrieTree::inDictionary(const string& word) {
    bool valid = false;

    TrieTreeNode* traveler = root;

    for(int i = 0, index = 0; i < word.size() && traveler != NULL; i++) {
        index = convertCharToIndex(word[i]);

        if(index != INVALID) {
            traveler = traveler->alphabet[index];
        }

        else {
            traveler = NULL;
        }
    }

    if(traveler != NULL) {
        valid = traveler->validWord;
    }

    return valid;
}

int TrieTree::getWordCount(const string& word) {
    int count = FAILED;

    TrieTreeNode* traveler = root;

    for(int i = 0, index = 0; i < word.size() && traveler != NULL; i++) {
        index = convertCharToIndex(word[i]);

        if(index != INVALID) {
            traveler = traveler->alphabet[index];
        }

        else {
            traveler = NULL;
        }
    }

    if(traveler != NULL && traveler->validWord) {
        count = traveler->wordCount;
    }

    return count;
}

int TrieTree::getMentions(const string& word) {
    int count = FAILED;

    if(root != NULL) {
        TrieTreeNode* traveler = root->alphabet[AT];

        for(int i = 1, index = 0; i < word.size() && traveler != NULL; i++) {
            index = convertCharToIndex(word[i]);

            if(index != INVALID) {
                traveler = traveler->alphabet[index];
            }

            else {
                traveler = NULL;
            }
        }

        if(traveler != NULL && traveler->validWord) {
            count = traveler->wordCount;
        }
    }

    return count;
}

void TrieTree::makeInvalid(const string& word){
    bool valid = true;

    TrieTreeNode* traveler = root;
    TrieTreeNode* parent = root;

    int lastValidChar = 0;

    if(traveler != NULL) {
        for(int i = 0, index = 0; i < word.size() && valid; i++) {
            parent = traveler;
            index = convertCharToIndex(word[i]);

            if(index != INVALID) {
                if(traveler->alphabet[index] != NULL) {
                    traveler = traveler->alphabet[index];
                    lastValidChar = i;
                }

                else{
                    valid = false;
                }
            }
        }

        if(valid) {
            int index = convertCharToIndex(word[lastValidChar]);

            if(index != INVALID) {
                parent->alphabet[index]->validWord = false;

                totalElements -= parent->alphabet[index]->wordCount;
                parent->alphabet[index]->wordCount = 0;

                uniqueElements--;
            }

            else {
                cout << "ERROR: makeInvalid() failed." << endl;
            }
        }

        else {
            cout << "ERROR: makeInvalid() failed." << endl;
        }
    }

    else {
        cout << "ERROR: makeInvalid() failed." << endl;
    }

    return;
}

//Treats vector like a stack that can be printed out.  Go to the very end of each
//branch, then back track until all valid words have been printed.
void TrieTree::printAlphabetically(ostream& os) {

    if(root != NULL) {
        string output = "";

        root->printAlphabetically(output, os);
    }
    else {
        cout << "Empty trie tree cannot be printed." << endl;
    }

    return;
}

void TrieTree::printBiggestWordCount(int listSize, ostream& os) {
    vector<FreqContainer> output;
    string word = "";

    root->convertToVector(&output, word);

    sort(output.begin(), output.end());

    int maxSize = output.size();

    if(listSize > 0 && listSize < output.size()) {
        maxSize = listSize;
    }

    for(int i = 0; i < maxSize; i++) {
        if(output[i].data[0] != '@' && output[i].data[0] != '#') {
            os << output[i].data << ' ' << output[i].frequency << endl;
        }
    }

    return;
}

void TrieTree::printHashtagCount(int listSize, ostream& os) {
    if(root != NULL) {
        if(root->alphabet[POUND] != NULL) {
            int maxSize = 0;
            vector<FreqContainer> info;
            string word = "#";

            root->alphabet[POUND]->convertToVector(&info, word);

            sort(info.begin(), info.end());

            maxSize = info.size();

            if(listSize > 0 && listSize < info.size()) {
                maxSize = listSize;
            }

            for(int i = 0; i < maxSize; i++) {
                os << info[i].data << ' ' << info[i].frequency << endl;
            }
        }

        else {
            cout << "No hashtags exist." << endl;
        }
    }

    else {
        cout << "ERROR: Cannot print mentions on empty tree." << endl;
    }
}

void TrieTree::printMentions(int listSize, ostream& os) {
    if(root != NULL) {
        if(root->alphabet[AT] != NULL) {
            int maxSize = 0;
            vector<FreqContainer> info;
            string word = "@";

            root->alphabet[AT]->convertToVector(&info, word);

            sort(info.begin(), info.end());

            maxSize = info.size();

            if(listSize > 0 && listSize < info.size()) {
                maxSize = listSize;
            }

            for(int i = 0; i < maxSize; i++) {
                os << info[i].data << ' ' << info[i].frequency << endl;
            }
        }

        else {
            cout << "No mentions exist." << endl;
        }
    }

    else {
        cout << "ERROR: Cannot print mentions on empty tree." << endl;
    }

    return;
}

void TrieTree::convertToVector(vector<FreqContainer>* vec) {
    if(root != NULL) {
        string word = "";
        root->convertToVector(vec, word);
    }

    else {
        cout << "ERROR: Cannot convert empty TrieTree." << endl;
    }

    return;
}
