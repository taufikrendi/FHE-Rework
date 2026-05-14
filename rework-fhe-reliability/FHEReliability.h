#pragma once
#include <vector>
#include <random>

class FHEReliability {
private:
    size_t N; // Ring Dimension (8192)
    double scale; // CKKS Scaling Factor (2^40)
    std::mt19937 gen;

public:
    FHEReliability(size_t ring_dim, double ckks_scale);

    // Calculates the actual value deviation caused by a bitflip
    double calculateCKKSError(int bit_position);

    // Simulates a random fault injection and returns the error magnitude
    double injectRandomBitflip();
};