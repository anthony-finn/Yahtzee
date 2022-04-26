# Yahtzee-AI

Yahtzee is a dice game where the objective is to roll 5 dice, where you may roll the dice up to 3 times in a turn. The game lasts 13 rounds/turns. After rolling the dice, a player chooses a section to score which may not be reused later in the game. The name Yahtzee is where you roll a 5 of the kind.

This program is a simple Yahtzee game implemented in C++ with a roll state evaluator. The roll state algorithm determines the expected value of each scorecard section, and gives suggestions to attempt to maximize the expected value for the given roll. 

## Usage

Compile the program with a c++ compiler.

```bash
g++ .\main.cpp .\scorecard.cpp .\dice.cpp .\algorithm.cpp
```
