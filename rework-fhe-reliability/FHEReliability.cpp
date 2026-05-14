#include "FHEReliability.h"
#include <iostream>

FHEReliabilitySim::CiphertextComponent::CiphertextComponent(size_t N, size_t L)
    : data(L, std::vector<uint64_t>(N, 100)) {}

FHEReliabilitySim::FHEReliabilitySim(size_t N, size_t L)
    : ring_dim(N), rns_levels(L), c0(N, L), c1(N, L), gen(std::random_device{}()) {}

void FHEReliabilitySim::injectRandomBitflip() {
    int comp_idx = std::uniform_int_distribution<>(0, 1)(gen);
    auto& target = (comp_idx == 0) ? c0 : c1;
    size_t row = std::uniform_int_distribution<size_t>(0, rns_levels - 1)(gen);
    size_t col = std::uniform_int_distribution<size_t>(0, ring_dim - 1)(gen);
    int bit = std::uniform_int_distribution<>(0, 63)(gen);

    target.data[row][col] ^= (1ULL << bit);

    std::cout << "[Fault Injected] Comp: c" << comp_idx
              << " | RNS Level: " << row
              << " | Coeff Index: " << col
              << " | Bit: " << bit << "\n";
}