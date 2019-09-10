#include "Location.h"

bool Coordinate::operator<(const Coordinate& other) const{
    if(x < other.x) {
        return true;
    }

    else if(x == other.x) {
        if(y < other.y) {
            return true;
        }
    }

    return false;
}

bool Coordinate::operator==(const Coordinate& other) const{
    if(x == other.x && y == other.y) {
        return true;
    }

    else {
        return false;
    }
}

Location::Location(){
    city = "";
    state = "";
    coordinates.resize(NUM_OF_COORDS);
}

bool Location::operator<(const Location& other) const{
    if(city < other.city) {
        return true;
    }

    else if(city == other.city) {
        if(state < other.state) {
            return true;
        }

        else if(state == other.state) {
            if(coordinates[0] < other.coordinates[0]) {
                return true;
            }

            else if(coordinates[0] == other.coordinates[0]) {
                if(coordinates[1] < other.coordinates[1]) {
                    return true;
                }

                else if(coordinates[1] == other.coordinates[1]) {
                    if(coordinates[2] < other.coordinates[2]) {
                        return true;
                    }

                    else if(coordinates[2] == other.coordinates[2]) {
                        if(coordinates[3] < other.coordinates[3]) {
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;
}

bool Location::operator==(const Location& other) {
    for(int i = 0; i < coordinates.size(); i++) {
        if(coordinates[i].x != other.coordinates[i].x
        || coordinates[i].y != other.coordinates[i].y) {
            return false;
        }
    }

    if(city != other.city || state != other.state) {
        return false;
    }

    return true;
}

void Location::print(ostream& os) {
    os << city << ", " << state << endl;
    for(int i = 0; i < NUM_OF_COORDS; i++) {
        os << coordinates[i].x << ',' << coordinates[i].y << endl;
    }

    return;
}
