#include "LinearRegressionModel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

LinearRegressionModel::LinearRegressionModel() {
    weights = {-0.2, -0.2, 0.01, -0.0001, 0.001, -0.00004, 0.0005, 0.4};
    bias = -35.0;
}

double LinearRegressionModel::predictEncrypted(const std::vector<double>& features, double injected_error) const {
    double prediction = bias;
    for (size_t i = 0; i < weights.size(); ++i) {
        prediction += (weights[i] * features[i]);
    }
    return prediction + injected_error;
}

BenchmarkResult LinearRegressionModel::processHousingCSVWithFaults(const std::string& filename, FHEReliability& sim) {
    // FIX 1: Declare 'res' at the very beginning of the function
    BenchmarkResult res;
    res.labels = {"PADD-P", "PMULT-P", "HADD", "HMUL"};
    res.xLabel = "CKKS Operation";
    res.yLabel = "Error Magnitude";

    // Dynamic Calculation (Logic from the paper)
    // FIX 2: Define 'base_error' ONLY ONCE here
    double base_error = sim.calculateCKKSError(62);

    // Calculate the propagation values
    double pmult_impact = base_error * 2000.0; // average feature scaling
    res.values = {base_error, pmult_impact, base_error * 1.05, pmult_impact * 7.0};

    // --- CSV Processing Block ---
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return res;
    }

    std::string line;
    std::getline(file, line); // skip header
    int count = 0;

    std::cout << "[FHE Analysis] Base CKKS Error (bit 62): " << base_error << std::endl;

    while (std::getline(file, line) && count < 5) {
        std::stringstream ss(line);
        std::vector<double> feats;
        std::string val;
        for (int i = 0; i < 8; ++i) {
            if(std::getline(ss, val, ',')) {
                feats.push_back(std::stod(val));
            }
        }
        // Use the pmult_impact as the injected error to simulate a weight fault
        double pred = predictEncrypted(feats, pmult_impact);
        std::cout << "Row " << ++count << " | Predicted (with Fault): $" << (pred * 100000.0) << std::endl;
    }

    return res; // Final return for the plotter
}