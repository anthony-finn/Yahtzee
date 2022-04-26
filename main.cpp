#include <iostream>
#include <string>
#include <sstream>
#include "Headers/dice.h"
#include "Headers/scorecard.h"
#include "Headers/algorithm.h"

using namespace std;

void display(Scorecard &scorecard, Dice &dice) {
    vector<int> possibleScores = scorecard.CalculatePossibleScores(dice);
    cout << "Possible scores: ";
    for (int i = 0; i < 14; i++) {
        cout << possibleScores[i] << " ";
    }
    cout << "\n" << endl;

    State state = Minimax_Rerolls(scorecard, dice);

    cout << "Best rerolls: ";
    for (int i = 0; i < state.RerollCombination.size(); i++) {
        cout << state.RerollCombination[i] << " ";
    }
    cout << "\n" << endl;
}

int main(int argc, char *argv[]) {
    Scorecard player;
    Dice dice;

    for (int turn = 0; turn < 13; turn++) {
        cout << "=======================================\nCURRENT TURN: " << turn + 1 << "\n\nYour scorecard: " << player << "\n\n" << endl;

        for (int roll = 0; roll < 3; roll++) {
            cout << "Roll #" << roll + 1 << endl;

            int selection = 0;
            while (selection != 1 && selection != 2) {
                string input;
                cout << "Would you like to roll [1] or manually input values [2]? ";
                cin >> input;

                if (input.length() == 1 && isdigit(input[0])) {
                    selection = stoi(input);

                    if (selection == 1 || selection == 2) {
                        break;
                    }
                } else {
                    cout << "Invalid input." << endl;
                }
            }

            if (selection == 1) {
                if (roll == 0) {
                    dice.Reroll();
                    cout << "\nYour roll: " << dice << "\n" << endl;
                    display(player, dice);
                } else {
                    int temp = 0;
                    string input;
                    cout << "What dice would you like to reroll? (Enter indicies e.g. 0 1 2 3 4) ";
                    cin.ignore();
                    getline(cin, input);
                    int reroll[5] = {0, 0, 0, 0, 0};

                    for (int i = 0; i < input.size(); i++) {
                        if (isdigit(input[i])) {
                            int index = input[i] - '0';
                            if (index >= 0 && index <= 5) {
                                reroll[index] = 1;
                            }
                        }
                    }

                    dice.Reroll(reroll);
                    cout << "\nYour roll: " << dice << "\n" << endl;
                    display(player, dice);
                }
            } else if (selection == 2) {
                int temp = 0;
                int count = 0;
                string input;
                cout << "Enter all 5 dice face values (e.g. 5 4 3 2 1): ";
                cin.ignore();
                getline(cin, input);

                for (int i = 0; i < input.size(); i++) {
                    if (isdigit(input[i])) {
                        int digit = input[i] - '0';
                        if (digit >= 1 && digit <= 6) {
                            dice.Face(count++) = digit;
                        }
                    }
                }

                cout << "\nYour roll: " << dice << "\n" << endl;
                display(player, dice);
            }

            string input;
            cout << "Would you like to keep rolling? [Y/N] ";
            while (cin >> input) {
                if (input == "N" || input == "Y") break;
                cout << "Would you like to keep rolling? [Y/N] ";
            }
            
            if (input == "N") {
                roll = 3;
            }
        }

        string input;
        int section = -1;
        while (section < 0 || section > 13) {
            cout << "\nWhich section would you like to score in? (0-13): ";
            cin >> input;

            if (input.length() >= 1 && isdigit(input[0])) {
                if (input.length() == 2 && !isdigit(input[1])) continue;
                section = stoi(input);

                if (section >= 0 && section <= 13) {
                    break;
                }
            }
        }

        player.ScoreSection(section, dice);

        cout << "\nYour scorecard: " << player << endl;

        cout << "=======================================" << endl;
    }

    cout << "Your score: " << player.CalculateScore() << endl;
    
    return 0;
}