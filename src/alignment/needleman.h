#ifndef NEEDLEMAN_H
#define NEEDLEMAN_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Alignment_needleman {
        string X;
        string Y;
};

Alignment needleman(string X, string Y, int gap, int mismatch, int match);

#endif
