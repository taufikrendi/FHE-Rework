#pragma once

#include <vector>
#include <string>
#include "FHEReliability.h"
#include "../lib/Plotter.h"

class LinearRegressionModel {
private:
    std::vector<double> weights;
    double bias;
    // Removed unused ring_dim and rns_levels to satisfy -Werror

public:
    LinearRegressionModel();
    double predictEncrypted(const std::vector<double>& features, double injected_error) const;
    BenchmarkResult processHousingCSVWithFaults(const std::string& filename, FHEReliability& sim);
    BenchmarkResult runReliabilityBenchmark(FHEReliability& sim);
};