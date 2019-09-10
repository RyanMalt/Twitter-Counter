#include "Pair.h"

bool operator<(const FreqContainer& first, const FreqContainer& second) {

    if(first.frequency > second.frequency) {
        return true;
    }

    else if(first.frequency == second.frequency) {
        if(first.data < second.data) {
            return true;
        }
    }

    return false;
}
