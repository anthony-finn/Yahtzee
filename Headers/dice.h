#ifndef DICE_H
#define DICE_H

#include <random>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

class Dice {
private:
    int dice_[5];
    int sum_ = 0;
    bool sumSynced_ = true;
public:
    Dice();
    Dice(const Dice&);
    void Reroll();
    void Reroll(int[5]);
    double GetProbability();
    int &Face(int);
    const int &Face(int) const;
    const int &Sum();
    friend ostream &operator<<(ostream &, const Dice &);
};

#endif