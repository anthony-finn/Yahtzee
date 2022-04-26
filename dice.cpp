#include "Headers/dice.h"

double nCr(int n, int k) {
    return 1 / ((n + 1) * beta(n - k + 1, k + 1));
}

Dice::Dice() {
    int reroll[5] = {1, 1, 1, 1, 1};
    this->Reroll(reroll);
}

Dice::Dice(const Dice& dice) {
    for (int i = 0; i < 5; i++) {
        this->dice_[i] = dice.Face(i);
    }
    this->sum_ = dice.sum_;
    this->sumSynced_ = dice.sumSynced_;
}

void Dice::Reroll() {
    int reroll[5] = {1, 1, 1, 1, 1};
    this->Reroll(reroll);
}

void Dice::Reroll(int reroll[5]) {
    this->sum_ = 0;
    random_device source;
    unsigned int random_data[10];

    for(unsigned int& elem : random_data) {
        elem = source(); 
    }

    seed_seq seed = seed_seq(random_data + 0, random_data + 10);
    static default_random_engine generator(seed);

    static uniform_int_distribution<int> distribution(1,6);
    for (int i = 0; i < 5; i++) {
        if (reroll[i]) {
            int roll = distribution(generator);
            this->dice_[i] = roll;
            this->sum_ += roll;
        }
    }

    sort(this->dice_, this->dice_ + 5);
}

double Dice::GetProbability() {
    vector<int> diceCount = {0, 0, 0, 0, 0, 0};
    for (int faceIndex = 0; faceIndex < 5; faceIndex++) {
        int face = this->dice_[faceIndex];
        diceCount[face - 1]++;
    }

    sort(diceCount.begin(), diceCount.end(), greater<int>());
    int used = 0;
    int remaining = 5;
    double solution = 6;

    for (int countIndex = 0; countIndex < diceCount.size(); countIndex++) {
        int count = diceCount[countIndex];
        if (count > 0 && count != 5) {
            if (count + used == 5 || count == 1) {
                solution *= remaining--;
            } else {
                solution *= nCr(5, count);
            }
            used += count;
        }
    }

    if ((int) solution == 3000) {
        solution = 1800.0;
    }

    return solution / 7776.0;
}

int &Dice::Face(int index) {
    sumSynced_ = false;
    return this->dice_[index];
}

const int &Dice::Face(int index) const {
    return this->dice_[index];
}

const int &Dice::Sum() {
    if (!this->sumSynced_) {
        this->sum_ = 0;
        for (int i = 0; i < 5; i++) {
            this->sum_ += this->dice_[i];
        }
        this->sumSynced_ = true;
    }
    return this->sum_;
}

ostream &operator<<(ostream &out, const Dice &dice) {
    for (int index = 0; index < 5; index++) {
        out << dice.Face(index);

        if (index != 4) {
            out << " ";
        }
    }
    return out;
}