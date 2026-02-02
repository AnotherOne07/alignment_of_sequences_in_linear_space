#ifndef NEEDLEMAN_H
#define NEEDLEMAN_H

#include <string>

struct Alignment_needleman {
    std::string X;
    std::string Y;
};

Alignment_needleman needleman(
    std::string X, std::string Y,
    int gap, int mismatch, int match
);

#endif

