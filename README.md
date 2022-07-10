
# Yahtzee-AI

Yahtzee is a dice game where the objective is to roll 5 dice, where you may roll the dice up to 3 times in a turn. The game lasts 13 rounds/turns. After rolling the dice, a player chooses a section to score which may not be reused later in the game. The name Yahtzee is where you roll a 5 of the kind.

This program is a simple Yahtzee game implemented in C++ with a roll state evaluator. The roll state algorithm determines the expected value of each scorecard section, and gives suggestions to attempt to maximize the expected value for the given roll.


## Demo

![](https://cdn.discordapp.com/attachments/995548321592660079/995548367251849216/YahtzeeAiDemo.gif)


## Optimizations

I attempted to use calculate the expected values of each reroll combination rather than each permutation by multiply the chances by the number of duplicates. Arrays are slightly faster than using the standard library vectors, which were used whenever the array size was known.

## Usage/Examples

Compile the program using a G++/C++ compiler.

```
g++ .\main.cpp .\scorecard.cpp .\dice.cpp .\algorithm.cpp -o
.\a.out
```

