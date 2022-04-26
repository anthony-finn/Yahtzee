#include "Headers/scorecard.h"
#include "Headers/dice.h"
#include "Headers/algorithm.h"

vector<vector<int>> rerollCombinations = {vector<int> {0},vector<int> {1},vector<int> {2},vector<int> {3},vector<int> {4},vector<int> {0, 1},vector<int> {0, 2},vector<int> {0, 3},vector<int> {0, 4},vector<int> {1, 2},vector<int> {1, 3},vector<int> {1, 4},vector<int> {2, 3},vector<int> {2, 4},vector<int> {3, 4},vector<int> {0, 1, 2},vector<int> {0, 1, 3},vector<int> {0, 1, 4},vector<int> {0, 2, 3},vector<int> {0, 2, 4},vector<int> {0, 3, 4},vector<int> {1, 2, 3},vector<int> {0, 1, 4},vector<int> {1, 3, 4},vector<int> {2, 3, 4},vector<int> {0, 1, 2, 3},vector<int> {0, 1, 2, 4},vector<int> {0, 1, 3, 4},vector<int> {0, 2, 3, 4},vector<int> {1, 2, 3, 4},vector<int> {0, 1, 2, 3, 4}};
vector<vector<int>> combinations[5];

void Combinations(vector<vector<int>>& combinations, int depth, int start = 1, vector<int> combination = {}, int startingDepth = -1) {
    if (depth == 0) {
        return;
    }

    if (startingDepth == -1) {
        startingDepth = depth;
    }

    for (int startIndex = start; startIndex <= 6; startIndex++) {
        combination.push_back(startIndex);
        Combinations(combinations, depth - 1, startIndex, combination, startingDepth);

        if (combination.size() == startingDepth) {
            vector<int> newCombination;
            for (int index = 0; index < startingDepth; index++) {
                newCombination.push_back(combination[index]);
            }
            combinations.push_back(newCombination);
        }        

        combination.pop_back();
    }
}

State Minimax_Rerolls(Scorecard& scorecard, Dice& dice) {
    vector<int> possibleScores = scorecard.CalculatePossibleScores(dice);
    State state;

    if (combinations[0].size() == 0) {
        for (int rerolls = 1; rerolls <= 5; rerolls++) {
            Combinations(combinations[rerolls - 1], rerolls);
        }
    }

    for (int rerollCombinationsIndex = 0; rerollCombinationsIndex < rerollCombinations.size(); rerollCombinationsIndex++) {
        vector<int> rerollCombination = rerollCombinations[rerollCombinationsIndex];
        int numRerolls = rerollCombination.size();
        int numCombinations = combinations[numRerolls - 1].size();
        double expectedValues[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

        for (int combinationIndex = 0; combinationIndex < numCombinations; combinationIndex++) {
            vector<int> combination = combinations[numRerolls - 1][combinationIndex];
            map<int, int> duplicates;
            Dice predictionDice(dice);
            int rerollIndex = 0;
            int numDuplicates = 0;

            for (int roll = 0; roll < numRerolls; roll++) {
                int face = combination[rerollIndex];
                predictionDice.Face(rerollCombination[rerollIndex]) = face;
                rerollIndex++;
                duplicates[face]++;

                if (duplicates[face] == 2) {
                    numDuplicates++;
                }
            }

            vector<int> predictionPossibleScores = scorecard.CalculatePossibleScores(predictionDice);

            for (int scoreIndex = 0; scoreIndex < predictionPossibleScores.size(); scoreIndex++) {
                double predictionScore = predictionPossibleScores[scoreIndex];
                double scoreDifference = (double) (predictionScore - possibleScores[scoreIndex]);

                if (predictionScore != -1) {
                    int size = duplicates.size();
                    double possibilities = (double) pow(6, numRerolls);
                    double probability = 1 / possibilities;

                    if (size != 1) {
                        if (numRerolls == size) {
                            probability *= tgamma(numRerolls + 1);
                        } else if (numRerolls == 3) {
                            probability *= 3;
                        } else if (numRerolls == 4) {
                            if (size == 2) {
                                if (numDuplicates == 1) {
                                    probability *= 4;
                                } else {
                                    probability *= 6;
                                }
                            } else {
                                probability *= 12;
                            }
                        } else if (numRerolls == 5) {
                            if (size == 4) {
                                probability *= 60;
                            } else if (size == 3) {
                                if (numDuplicates == 1) {
                                    probability *= 20;
                                } else {
                                    probability *= 30;
                                }
                            } else {
                                if (numDuplicates == 1) {
                                    probability *= 10;
                                } else {
                                    probability *= 5;
                                }
                            }
                        }
                    }
                    
                    double event = scoreDifference * probability;
                    expectedValues[scoreIndex] += event;
                }
            }
        }

        double totalExpectedValue = 0;
        for (int i = 0; i < 14; i++) {
            double expectedValue = expectedValues[i];
            totalExpectedValue += expectedValue;
        }

        if (totalExpectedValue > state.TotalExpectedValue) {
            state.TotalExpectedValue = totalExpectedValue;

            if (totalExpectedValue > 0) {
                state.RerollCombination = rerollCombination;
            }
        }
    }

    return state;
}