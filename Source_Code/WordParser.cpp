#include "WordParser.h"

Tweetalyzer::Tweetalyzer() {
    ifstream input;
    input.open(INVALID_WORDS.c_str());

    if(input.is_open()) {
        string ignore;

        while(input >> ignore) {
            invalidWords.insert(ignore);
        }
    }
}

void Tweetalyzer::insertWord(const string& word) {
    wordCounter.insert(word);

    return;
}

void Tweetalyzer::insertAuthor(const string& word) {
    authors.insert(word);

    return;
}

void Tweetalyzer::insertLocation(const Location& loc) {
    location.insert(loc);

    return;
}

void Tweetalyzer::parseFile(const string& fileName) {
    int numTweets = 0;
    char throwaway;

    ifstream input;
    string info;
    input.open(fileName.c_str());

    if(input.is_open()) {
        cout << "Beginning parsing of: " << fileName << endl;
        input >> numTweets;

        for(int i = 0; i < numTweets; i++) {
            input >> info;
            authors.insert(info);

            input.get(throwaway);
            getline(input, info, ',');

            //Processes location
            if(info != NO_GEO) {
                Location loc;
                loc.city = info;

                getline(input, info, '\n');
                input.clear();
                info.erase(0, 1);
                loc.state = info;

                input >> info;

                if(info == "YES") {
                    input.get(throwaway); //Removes first brace

                    if(throwaway == '\n') {
                        input.get(throwaway); //Removes first brace if only newline before
                    }

                    for(int j = 0; j < NUM_OF_COORDS; j++) {
                        input.get(throwaway); //Removes left brace
                        input >> loc.coordinates[j].x;
                        input.get(throwaway); //Removes comma
                        input >> loc.coordinates[j].y;
                        input.get(throwaway); //Removes right brace
                        input.get(throwaway); //Removes comma

                        if(j < NUM_OF_COORDS - 1) {
                            input.get(throwaway); //Removes space if not last coord
                        }
                    }

                    location.insert(loc);
                }
            }

            input >> info;
            info.erase(0, 2);

            while(info[info.size() - 1] != '\"' || info[info.size() - 2] != '\"') {
                wordCounter.insert(info);
                input >> info;
            }

            info.erase(info.size() - 2);
            wordCounter.insert(info);
        }

        cout << "Finished parsing: " << fileName << endl;
    }

    else {
        cout << "ERROR: Tweet file not found." << endl;
        assert(input.is_open());
    }

    input.close();

    return;
}
void parseCommands(const char** args, int numArgs) {} //To be improved later.  Support for cmdline args.

void Tweetalyzer::reportWordCount(int listSize, const char args, ostream& os) {
    vector<FreqContainer> validWords;

    wordCounter.convertToVector(&validWords);

    sort(validWords.begin(), validWords.end());

    for(int i = 0; i < validWords.size(); i++) {
        if(!invalidWords.inDictionary(validWords[i].data)
        && validWords[i].data[0] != '@'
        && validWords[i].data[0] != '#') {
            os << validWords[i].data << ' ' << validWords[i].frequency << endl;
        }
    }
    return;
}

void Tweetalyzer::reportHashtags(int listSize, const char args, ostream& os) {
    wordCounter.printHashtagCount(listSize, os);
    return;
}

void Tweetalyzer::reportAuthors(int listSize, const char args, ostream& os) {
    authors.printBiggestWordCount(listSize, os);
    return;
}
void Tweetalyzer::reportCityState(int listSize, const char args, ostream& os) {
    location.printCityState(os);

    return;
}
void Tweetalyzer::reportBoundingBoxes(int listSize, ostream& os) {
    location.printBoundingBoxes(os);
    return;
}
void Tweetalyzer::reportFullLocations(int listSize, const char args, ostream& os) {
    location.printAll(os);

    return;
}
void Tweetalyzer::reportMentions(int listSize, const char args, ostream& os) {
    wordCounter.printMentions(listSize, os);

    return;
}

int Tweetalyzer::findWordCount(const string& word) {
    return wordCounter.getWordCount(word);
}

int Tweetalyzer::findAuthorCount(const string& word){
    return authors.getWordCount(word);
}

bool Tweetalyzer::findLocation(const Location& loc){
    return location.find(loc);
}

int Tweetalyzer::findMentionCount(const string& word){
    return wordCounter.getMentions(word);
}

int Tweetalyzer::getTotalWords(){
    return wordCounter.getTotalElements();
}

int Tweetalyzer::getTotalUniqueWords(){
    return wordCounter.getUniqueElements();
}

int Tweetalyzer::getTotalDiscardedWords(){
    return wordCounter.getDiscardedInput();
}

int Tweetalyzer::getTotalAuthors(){
    return authors.getTotalElements();
}

int Tweetalyzer::getTotalUniqueAuthors(){
    return authors.getUniqueElements();
}

int Tweetalyzer::getTotalLocations() {
    return location.getTotalLocations();
}

int Tweetalyzer::getTotalDiscardedAuthors(){
    return authors.getDiscardedInput();
}
