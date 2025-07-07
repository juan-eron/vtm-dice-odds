#include "../include/simulator.hpp"
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    // Default values
    int numDice = 6;
    int difficulty = 8;
    int trials = 1'000'000;

    if (argc >= 3) 
    {
        numDice = std::atoi(argv[1]);
        difficulty = std::atoi(argv[2]);

        if (argc >= 4) 
        {
            trials = std::atoi(argv[3]);
        }
    } 
    else 
    {
        std::cout << "Usage: " << argv[0] << " <numDice> <difficulty> [trials]\n";
        std::cout << "Using defaults: numDice=6, difficulty=8, trials=1000000\n";
    }

    // Basic validation
    if (numDice <= 0 || difficulty <= 0 || trials <= 0) {
        std::cerr << "Error: numDice, difficulty, and trials must be positive integers.\n";
        return 1;
    }

    double probability = simulateWithReroll(numDice, difficulty, trials);

    std::cout << "Chance to pass difficulty " << difficulty
              << " with " << numDice << " dice (with willpower reroll): "
              << probability * 100 << "%\n";

    return 0;
}
