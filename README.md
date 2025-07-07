# VTM Dice Simulator

A command-line simulator for Vampire: The Masquerade 5th Edition dice rolls, written in C++.  
It calculates the probability of passing a test based on the number of dice, difficulty, and willpower rerolls.

## Features

- Simulates d10 rolls based on VTM V5 rules
- Counts successes (6–9 = 1 success, 10s can form criticals worth 4 successes)
- Supports rerolling up to 3 non-successes using willpower
- Configurable number of dice, difficulty, and trials

## Build

Requires `g++` (C++17 or later):

```bash
g++ -O2 -std=c++17 -o vtm_simulator main.cpp simulator.cpp
