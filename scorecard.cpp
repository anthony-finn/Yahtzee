#include "Headers/scorecard.h"

Scorecard::Scorecard() {}

vector<int> Scorecard::CalculatePossibleScores(Dice& dice) {
    vector<int> scores(14, 0);
    map<int, int> diceMap;

    /* Nth of a Kind */
    for (int i = 0; i < 5; i++) {
        int face = dice.Face(i);
        diceMap[face]++;
    }

    // Handle Already Used
    for (int index = 0; index < 14; index++) {
        if (this->scores_[index] != -1) {
            scores[index] = -1;
        }
    }

    // Special Flags
    // Used for Straights and Full House
    int consecutive = 0;
    int lastKey = 0;
    int fullHouse = 0;

    for (const auto &[key, value] : diceMap) {
        int translatedIndex = key - 1;

        /* Upper Section */
        if (this->scores_[translatedIndex] == -1) {
            scores[translatedIndex] = key * value;
        } else {
            scores[translatedIndex] = -1;
        }

        /* Full House */
        if (value >= 2) {
            fullHouse += value;
        }

        /* Three Of A Kind */
        if (value >= 3) {
            if (this->scores_[ThreeOfAKind] == -1) {
                scores[ThreeOfAKind] = dice.Sum();
            } else {
                scores[ThreeOfAKind] = -1;
            }
            
            /* Four of A Kind */
            if (value >= 4) {
                if (this->scores_[FourOfAKind] == -1) {
                    scores[FourOfAKind] = dice.Sum();
                } else {
                    scores[FourOfAKind] = -1;
                }

                /* Yahtzee */
                if (value == 5) {
                    if (this->scores_[Yahtzee] == -1) {
                        scores[Yahtzee] = 50;
                    } else {
                        scores[Yahtzee] = -1;

                        /* Yahtzee Bonus */
                        if (this->scores_[Yahtzee] == 50) {
                            scores[YahtzeeBonus] = 100;
                        }
                    }
                }
            }
        }

        /* Handle Consecutive Roll Values */
        if (key - lastKey == 1 || lastKey == 0) {
            consecutive++;
        } else {
            consecutive = 0;
        }
        lastKey = key;

        if (consecutive >= 4) {
            /* Small Straight */
            if (this->scores_[SmallStraight] == -1) {
                scores[SmallStraight] = 30;
            } else {
                scores[SmallStraight] = -1;
            }

            /* Large Straight */
            if (consecutive == 5) {
                if (this->scores_[LargeStraight] == -1) {
                    scores[LargeStraight] = 40;
                } else {
                    scores[LargeStraight] = -1;
                }
            }
        }
    }

    /* Full House */
    if (fullHouse == 5) {
        if (this->scores_[FullHouse] == -1) {
            scores[FullHouse] = 25;
        } else {
            scores[FullHouse] = -1;
        }
    }

    /* Chance */
    if (this->scores_[Chance] == -1) {
        scores[Chance] = dice.Sum();
    } else {
        scores[Chance] = -1;
    }

    return scores;
}

bool Scorecard::IsCompleted() {
    for (int i = 0; i < 13; i++) {
        if (this->scores_[i] == -1) {
            return false;
        }
    }
    return true;
}

int Scorecard::CalculateUpperScore() {
    int upperTotal = 0;
    for (int i = 0; i < 6; i++) {
        upperTotal += this->scores_[i];
    }

    if (upperTotal >= 63) {
        upperTotal += 35;
    }

    return upperTotal;
}

int Scorecard::CalculateLowerScore() {
    int lowerTotal = 0;
    for (int i = 6; i < 14; i++) {
        lowerTotal += this->scores_[i];
    }

    return lowerTotal;
}

int Scorecard::CalculateScore() {
    return this->CalculateUpperScore() + this->CalculateLowerScore();
}

void Scorecard::ScoreSection(int index, Dice &dice) {
    vector<int> scores = this->CalculatePossibleScores(dice);
    this->scores_[index] = scores[index];
}

const int &Scorecard::GetSectionScore(int index) const {
    return this->scores_[index];
}

ostream &operator<<(ostream &out, const Scorecard &scorecard) {
    for (int index = 0; index < 14; index++) {
        int score = scorecard.scores_[index];

        if (score != -1) {
            out << scorecard.scores_[index];
        } else {
            out << "X";
        }

        if (index != 13) {
            out << " ";
        }
    }
    return out;
}