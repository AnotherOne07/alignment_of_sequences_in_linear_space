#ifndef NEEDLEMAN_H
#define NEEDLEMAN_H

#include "../utils/alignment.h"
#include <string>

using namespace std;

/*struct Alignment_needleman {
        int score;
        string X;
        string Y;
};*/

AlignmentResult needleman(
    std::string X, std::string Y,
    int gap, int mismatch, int match
);

#endif
