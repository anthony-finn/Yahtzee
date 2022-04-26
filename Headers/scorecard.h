#ifndef SCORECARD_H
#define SCORECARD_H

#include "dice.h"
#include <vector>
#include <map>
#include <iostream>

using namespace std;

/* Scorecard Sections */
#define Ones 0
#define Twos 1
#define Threes 2
#define Fours 3
#define Fives 4
#define Sixes 5
#define ThreeOfAKind 6
#define FourOfAKind 7
#define FullHouse 8
#define SmallStraight 9
#define LargeStraight 10
#define Yahtzee 11
#define Chance 12
#define YahtzeeBonus 13

class Scorecard {
private:
    int scores_[14] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
public:
    Scorecard();
    vector<int> CalculatePossibleScores(Dice&);
    bool IsCompleted();
    int CalculateUpperScore();
    int CalculateLowerScore();
    int CalculateScore();
    void ScoreSection(int, Dice &);
    const int &GetSectionScore(int) const;
    friend ostream &operator<<(ostream &, const Scorecard &);
};

#endif