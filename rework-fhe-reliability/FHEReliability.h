#ifndef FHE_RELIABILITY_SIM_H
#define FHE_RELIABILITY_SIM_H

#include <vector>
#include <random>
#include <cstdint>

class FHEReliabilitySim {
private:
    struct CiphertextComponent {
        std::vector<std::vector<uint64_t>> data;
        CiphertextComponent(size_t N, size_t L);
    };

    size_t ring_dim;
    size_t rns_levels;
    CiphertextComponent c0;
    CiphertextComponent c1;
    std::mt19937 gen;

public:
    FHEReliabilitySim(size_t N, size_t L);

    // Make sure this name matches what you call in main.cpp exactly!
    void injectRandomBitflip();
};

#endif