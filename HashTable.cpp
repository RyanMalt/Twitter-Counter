#include "HashTable.h"

//Uses sieve of eratosthenes.  Quick and easy to implement.
//Can be greatly optimized if time allows.
void generateFormattedPrimes() {

    ofstream output;

    output.open(PRIMES_FILE.c_str(), ios::trunc);

    output << OUTPUT_PRIMES << endl;

    bool* sieve = new bool[PRIME_U_BOUND];

    for(int i = 0; i < PRIME_U_BOUND; i++) {
        sieve[i] = true;
    }

    double u_bound = sqrt(PRIME_U_BOUND);

    for(int i = 2; i < u_bound; i++) {
            if(sieve[i]) {
                for(int j = i; j * i < PRIME_U_BOUND; j++) {
                    sieve[i * j] = false;
                }
            }
    }

    for(int i = DEFAULT_SIZE; i < PRIME_U_BOUND; i *= 2) {
        while(i < PRIME_U_BOUND && !sieve[i]) {
            i++;
        }

        if(i < PRIME_U_BOUND) {
            output << i << endl;
        }
    }

    output.close();

    return;
}

void HashTable::rehash() {
    vector<Location> info;

    for(int i = 0; i < tableSize; i++) {
        if(filled[i]) {
            info.push_back(information[i]);
        }
    }

    currentIndex++;

    if(currentIndex >= OUTPUT_PRIMES) {
        cout << "ERROR: Too much data.  Why on earth are you processing this much?" << endl;
        assert(currentIndex < OUTPUT_PRIMES);
    }

    tableSize = primes[currentIndex];

    information.clear();
    information.resize(tableSize);
    filled.resize(tableSize);

    currentSize = 0;

    for(int i = 0; i < filled.size(); i++) {
        filled[i] = false;
    }

    for(int i = 0; i < info.size(); i++) {
        insert(info[i]);
    }

    return;
}

HashTable::HashTable() {
    ifstream input;
    input.open(PRIMES_FILE.c_str());

    int numPrimes = 0;

    if(!input) {
        cout << "Warning: Primes file either does not exist or is corrupted." << endl;
        generateFormattedPrimes();

        input.close();
        input.open(PRIMES_FILE.c_str());
        input >> numPrimes;
    }

    else {
        input >> numPrimes;

        if(numPrimes != OUTPUT_PRIMES) {
            cout << "Warning: Primes file either does not exist or is corrupted." << endl;
            generateFormattedPrimes();

            input.close();
            input.open(PRIMES_FILE.c_str());
            input >> numPrimes;
        }
    }

    if(input.is_open() && numPrimes == OUTPUT_PRIMES) {
        primes.resize(OUTPUT_PRIMES);
        currentIndex = 0;
        currentSize = 0;

        for(int i = 0; i < OUTPUT_PRIMES; i++) {
            input >> primes[i];
        }

        input.close();

        tableSize = primes[currentIndex];
        information.resize(tableSize);
        filled.resize(tableSize);

        for(int i = 0; i < tableSize; i++) {
            filled[i] = false;
        }
    }

    else {
        cout << "ERROR: Failure to find or create primes file." << endl;
        assert(false);
    }
}

void HashTable::insert(const Location& info) {
    bool success = false;

    if(currentSize + 1 >= tableSize / 2) {
        rehash();
    }

    int index = hash(info);

    for(int i = 0; i < tableSize / 2 && !success; i++) {
        index = (index + i) % tableSize;
        if(!filled[index]) {
            filled[index] = true;
            information[index] = info;

            success = true;
        }
    }

    if(!success) {
        cout << "WARNING: Hash failed for Location." << endl;
        cout << "city: " << info.city << endl;
        cout << "state/country: " << info.state << endl;

        for(int i = 0; i < NUM_OF_COORDS; i++) {
            cout << "Coord " << i << ": " << info.coordinates[i].x << ','
                 << info.coordinates[i].y << endl;
        }
    }

    else {
        currentSize++;
    }

    return;
}

bool HashTable::find(const Location& info) {
    bool found = false;

    int index = hash(info);

    for(int i = 0; i < tableSize / 2 && !found; i++) {
        index = (index + i) % tableSize;
        if(filled[index] && information[index] == info) {
            found = true;
        }
    }

    return found;
}

int HashTable::hash(const Location& info) {
    int value = info.city[info.city.size() / 2] * 13;
    value += info.state[info.state.size() / 2] * 17;
    value += abs(info.coordinates[0].x);
    value += abs(info.coordinates[1].y);
    value += abs(info.coordinates[2].x);
    value += abs(info.coordinates[3].y);

    return value % tableSize;
}

void HashTable::printAll(ostream &os) {
    for(int i = 0; i < tableSize; i++) {
        if(filled[i]) {
            information[i].print(os);
        }
    }

    return;
}

void HashTable::printAlphabetically(ostream& os) {
    vector<Location> printable;

    printToVector(printable);

    sort(printable.begin(), printable.end());

    for(int i = 0; i < printable.size(); i++) {
        printable[i].print(os);
    }

    return;
}

void HashTable::printCityState(ostream & os) {
    vector<Location> printable;

    printToVector(printable);

    sort(printable.begin(), printable.end());

    for(int i = 0; i < printable.size(); i++) {
        os << printable[i].city << ", " << printable[i].state << endl;
    }

    return;
}

void HashTable::printBoundingBoxes(ostream& os) {
    vector<Location> info;

    printToVector(info);

    sort(info.begin(), info.end());

    for(int i = 0; i < info.size(); i++) {
        for(int j = 0; j < NUM_OF_COORDS; j++) {
            os << info[i].coordinates[j].x << ' ' << info[i].coordinates[j].y << endl;
        }

        os << endl;
    }

    return;
}

void HashTable::printToVector(vector<Location>& info) {
    int total = 0;
    for(int i = 0; i < tableSize; i++) {
        if(filled[i]) {
            info.push_back(information[i]);
            total++;
        }
    }

    return;
}

int HashTable::getTotalLocations() {
    return currentSize;
}
