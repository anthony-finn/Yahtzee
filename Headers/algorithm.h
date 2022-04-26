#ifndef ALGORITHM_H
#define ALGORITHM_H

#include "scorecard.h"
#include "dice.h"
#include <vector>
#include <map>
#include <cmath>

using namespace std;

struct State {
    double TotalExpectedValue = numeric_limits<double>::lowest();
    vector<int> RerollCombination;
};

State Minimax_Rerolls(Scorecard&, Dice&);

#endif