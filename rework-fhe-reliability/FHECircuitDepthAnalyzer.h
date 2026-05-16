#pragma once

#include <vector>
#include <string>
#include "FHEReliability.h"
#include "../lib/Plotter.h"

class FHECircuitDepthAnalyzer {
private:
    int total_trials;
    double normalized_avg_feature;
    double avg_weight;

public:
    // Constructor sets experimental parameters
    FHECircuitDepthAnalyzer(int trials = 10000, double avg_feature = 0.5, double weight = 0.15);

    // Core benchmark that places the 6 operations on the X-axis for a SPECIFIC depth L
    BenchmarkResult runBenchmarkAtDepth(FHEReliability& sim, int L);
};