#include <iostream>
#include <vector>
#include <random>
#include <cstdint>

/**
 * @brief Manages FHE ciphertext components and simulates memory faults
 * as described in the paper "Reliability Analysis of FHE Systems".
 */
class FT_FHEReliability {
private:
    struct CiphertextComponent {
        std::vector<std::vector<uint64_t>> data;

        CiphertextComponent(size_t N, size_t L)
            : data(L, std::vector<uint64_t>(N, 100)) {}
    };

    size_t ring_dim;
    size_t rns_levels;
    CiphertextComponent c0;
    CiphertextComponent c1;
    std::mt19937 gen;

public:
    FT_FHEReliability(size_t N, size_t L)
        : ring_dim(N), rns_levels(L), c0(N, L), c1(N, L), gen(std::random_device{}()) {}

    /**
     * @brief Step-by-step Fault Injection Algorithm
     * Simulates a random transient memory bitflip[cite: 48].
     */
    void injectMemoryFault() {
        // 1. Select Target: Randomly pick component c0 or c1 [cite: 33, 48]
        int comp_idx = std::uniform_int_distribution<>(0, 1)(gen);
        auto& target = (comp_idx == 0) ? c0 : c1;

        // 2. Select Location: Pick a random RNS row and NTT column [cite: 33, 48]
        size_t row = std::uniform_int_distribution<size_t>(0, rns_levels - 1)(gen);
        size_t col = std::uniform_int_distribution<size_t>(0, ring_dim - 1)(gen);

        // 3. Flip Bit: Choose 1 of 64 bits to flip [cite: 33, 34]
        int bit = std::uniform_int_distribution<>(0, 63)(gen);

        // Apply the XOR bitflip as described in the paper methodology [cite: 34, 49]
        target.data[row][col] ^= (1ULL << bit);

        std::cout << "[Fault Injected] Comp: c" << comp_idx
                  << " | RNS Level: " << row
                  << " | Coeff Index: " << col
                  << " | Bit: " << bit << "\n";
    }

    uint64_t getCoeff(int comp, size_t L, size_t N) const {
        return (comp == 0) ? c0.data[L][N] : c1.data[L][N];
    }
};