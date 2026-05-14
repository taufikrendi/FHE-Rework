#pragma once
#include <vector>
#include <string>
#include "../lib/Plotter.h"
#include "FHEReliability.h"

class LinearRegressionModel {
private:
    std::vector<double> weights;
    double bias;

public:
    LinearRegressionModel();

    double predictEncrypted(const std::vector<double>& features, double injected_error) const;
    BenchmarkResult processHousingCSVWithFaults(const std::string& filename, FHEReliability& sim);
    // REVISED: Pass the FHE Simulator to calculate dynamic values
    BenchmarkResult runReliabilityBenchmark(FHEReliability& sim);
};