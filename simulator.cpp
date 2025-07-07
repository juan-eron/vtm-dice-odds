#include "simulator.hpp"
#include <vector>
#include <random>
#include <algorithm>
#include <chrono>

const int DICE_SIDES = 10;

// Random number generator setup
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
std::uniform_int_distribution<int> d10(1, DICE_SIDES);

// Count total successes, with critical success logic
int countSuccesses(const std::vector<int>& roll) 
{
    int successes = 0;
    int tens = 0;

    for (int value : roll) 
    {
        if (value >= 6) ++successes;
        if (value == 10) ++tens;
    }

    int criticalBonus = (tens / 2) * 2; // Each pair of 10s adds 2 extra successes
    return successes + criticalBonus;
}

// Identify indices of dice eligible for reroll (< 6)
std::vector<int> getRerollCandidates(const std::vector<int>& roll) 
{
    std::vector<int> indices;

    for (size_t i = 0; i < roll.size(); ++i) 
    {
        if (roll[i] < 6) 
            indices.push_back(i);
    }

    return indices;
}

// Simulate dice tests with willpower reroll
double simulateWithReroll(int numDice, int difficulty, int trials) 
{
    int successCount = 0;

    for (int t = 0; t < trials; ++t) 
    {
        std::vector<int> roll(numDice);
        for (int& die : roll) 
            die = d10(rng);

        int totalSuccess = countSuccesses(roll);
        if (totalSuccess >= difficulty) 
        {
            ++successCount;
            continue;
        }

        // Willpower reroll: up to 3 failures (<6)
        std::vector<int> rerollIndices = getRerollCandidates(roll);
        if (!rerollIndices.empty()) 
        {
            int rerollCount = std::min(3, (int)rerollIndices.size());
            for (int i = 0; i < rerollCount; ++i) 
                roll[rerollIndices[i]] = d10(rng);

            totalSuccess = countSuccesses(roll);
            if (totalSuccess >= difficulty) 
                ++successCount;
        }
    }

    return static_cast<double>(successCount) / trials;
}