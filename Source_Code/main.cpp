#include "WordParser.h"

enum INDICES {
    INPUT = 1,
    OUTPUT = 2
};

using namespace std;

int main(int argv, char** argc) {

    Tweetalyzer analyzer;
    ofstream output;
    output.open(argc[OUTPUT]);

    analyzer.parseFile(argc[INPUT]);

    cout << "Reporting word count..." << endl;
    output << "/**********************WORD COUNT**********************/" << endl;
    analyzer.reportWordCount(PRINT_ALL, PRINT_BY_FREQ, output);
    output << "/******************************************************/" << endl << endl;
    cout << "Finished reporting." << endl << endl;

    cout << "Reporting hashtag count..." << endl;
    output << "/**********************HASH TAGS***********************/" << endl;
    analyzer.reportHashtags(PRINT_ALL, PRINT_BY_FREQ, output);
    output << "/******************************************************/" << endl << endl;
    cout << "Finished reporting." << endl << endl;

    cout << "Reporting mentions..." << endl;
    output << "/***********************MENTIONS***********************/" << endl;
    analyzer.reportMentions(PRINT_ALL, PRINT_BY_FREQ, output);
    output << "/******************************************************/" << endl << endl;
    cout << "Finished reporting." << endl << endl;

    cout << "Reporting city, state..." << endl;
    output << "/**********************CITY,STATE**********************/" << endl;
    analyzer.reportCityState(PRINT_ALL, PRINT_BY_FREQ, output);
    output << "/******************************************************/" << endl << endl;
    cout << "Finished reporting." << endl << endl;

    cout << "Reporting bounding box..." << endl;
    output << "/********************BOUNDING BOXES********************/" << endl;
    analyzer.reportBoundingBoxes(PRINT_ALL, output);
    output << "/******************************************************/" << endl << endl;
    cout << "Finished reporting." << endl << endl;

    cout << "Reporting summary statistics..." << endl;
    output << "/**********************SUMMARY**********************/" << endl;
    output << "Total words: " << analyzer.getTotalWords() << endl;
    output << "Total unique words: " << analyzer.getTotalUniqueWords() << endl;
    output << "Total discarded words: " << analyzer.getTotalDiscardedWords() << endl << endl;

    output << "Total authors: " << analyzer.getTotalAuthors() << endl;
    output << "Total unique authors: " << analyzer.getTotalUniqueAuthors() << endl;
    output << "Total discarded authors: " << analyzer.getTotalDiscardedAuthors() << endl << endl;

    output << "Total locations: " << analyzer.getTotalLocations() << endl;
    output << "/******************************************************/" << endl;
    cout << "Finished reporting." << endl;

    output.close();

    return 0;
}
