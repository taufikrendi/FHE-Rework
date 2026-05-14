#include "FHEReliability.h"
#include <cmath>

FHEReliability::FHEReliability(size_t ring_dim, double ckks_scale)
    : N(ring_dim), scale(ckks_scale), gen(std::random_device{}()) {}

double FHEReliability::calculateCKKSError(int bit_position) {
    // E = 2^bit / (N * Scale)
    return std::pow(2.0, bit_position) / (static_cast<double>(N) * scale);
}

double FHEReliability::injectRandomBitflip() {
    std::uniform_int_distribution<int> bit_dist(0, 63);
    int bit = bit_dist(gen);
    return calculateCKKSError(bit);
}