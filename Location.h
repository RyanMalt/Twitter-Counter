#ifndef LOCATION_H_INCLUDED
#define LOCATION_H_INCLUDED
#include <string>
#include <vector>
#include <ostream>
#include <iostream>

using namespace std;

const int NUM_OF_COORDS = 4;

//Orders lexicographically by x coordinate
struct Coordinate{
    double x;
    double y;

    Coordinate() {x = 0; y = 0;}
    Coordinate(double newX, double newY) {x = newX; y = newY;}
    bool operator<(const Coordinate& other) const;
    bool operator==(const Coordinate& other) const;
};

struct Location {
    string city;
    string state;

    vector<Coordinate> coordinates;

    Location();

    bool operator==(const Location& other);
    bool operator<(const Location& other) const;
    void print(ostream& os = cout);
};

#endif // LOCATION_H_INCLUDED
