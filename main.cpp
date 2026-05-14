#include <iostream>
#include <sciplot/sciplot.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
// Include our modular classes
// #include "lib/Utils.cpp"
// #include "lib/Plotter.h"
// #include "benchmarker-testing/BFVBenchmarker.cpp"
// #include "benchmarker-testing/CKKSBenchmarker.cpp"
// #include "rework-fhe-reliability/FT_FHEReliabilitySim.cpp"

#include "rework-fhe-reliability/FHEReliability.h"
#include "rework-fhe-reliability/LinearRegressionModel.h"

using namespace sciplot;

// void PlotResults(const BenchmarkResult& res) {
//     std::vector<double> x_coords;
//     for(size_t i = 0; i < res.stages.size(); ++i) x_coords.push_back(static_cast<double>(i));
//
//     Plot2D plot;
//     plot.xlabel("FHE Pipeline Stage");
//     plot.ylabel("Time (ms)");
//     plot.xtics().at(x_coords, res.stages);
//
//     // widths must match the number of stages
//     std::vector<double> widths(res.stages.size(), 0.7);
//
//     plot.drawBoxes(x_coords, res.time_ms, widths)
//         .label(res.algoName + " Latency")
//         .fillColor("blue")
//         .fillIntensity(0.5);
//
//     Figure fig = {{plot}};
//     Canvas canvas = {{fig}};
//
//     // Updated Resolution
//     canvas.size(1200, 800);
//
//     canvas.save(res.algoName + "_benchmark.png");
//     std::cout << ">> " << res.algoName << " report generated (1200x800)." << std::endl;
// }

int main() {
    // std::cout << "--- First Testing Starting Comparative FHE Benchmarking ---" << std::endl;
    //
    // // Run BFV
    // BenchmarkResult bfvRes = BFVBenchmarker::Run();
    // PlotResults(bfvRes);
    //
    // // Run CKKS
    // BenchmarkResult ckksRes = CKKSBenchmarker::Run();
    // PlotResults(ckksRes);
    //
    // std::cout << "--- All Benchmarks Finished ---" << std::endl;
    //
    // // Parameters based on the paper's methodology
    // size_t ring_dimension = 8192; // N
    // size_t modulus_levels = 4;    // L (Number of RNS primes)
    //
    // // Initialize the simulation
    // FT_FHEReliabilitySim simulator(ring_dimension, modulus_levels);
    //
    // std::cout << "--- Starting FHE Reliability Analysis ---" << std::endl;
    //
    // // Simulate 3 random bitflips in the system memory
    // for(int i = 0; i < 3; ++i) {
    //     simulator.injectMemoryFault();
    // }
    //
    // std::cout << "Simulation Complete. Decrypt result to check for SDC." << std::endl;

    LinearRegressionModel model;

    // 1. Open the attached CSV file
    std::ifstream file("../data/housing.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open housing.csv. Please ensure it is in the same directory." << std::endl;
        return 1;
    }

    std::string line;
    // 2. Read and skip the header row
    std::getline(file, line);

    int row_count = 0;
    int max_rows = 10;

    std::cout << "--- FHE: Batch Processing housing.csv ---" << std::endl;
    std::cout << std::left << std::setw(8) << "Row"
              << std::setw(20) << "Actual Value"
              << "Predicted Value" << std::endl;
    std::cout << std::string(50, '-') << std::endl;

    // 3. Parse the file line by line
    while (std::getline(file, line) && row_count < max_rows) {
        std::stringstream ss(line);
        std::string token;

        std::vector<double> numerical_data;
        std::string ocean_prox;
        double actual_value = 0.0;

        try {
            // Read the first 9 columns (8 features + 1 target value)
            for (int i = 0; i < 9; ++i) {
                std::getline(ss, token, ',');
                if (i == 8) {
                    actual_value = std::stod(token); // Column 8 is median_house_value
                } else {
                    // Handle potential missing data
                    double val = token.empty() ? 0.0 : std::stod(token);
                    numerical_data.push_back(val);
                }
            }

            // Read the 10th column (categorical: ocean_proximity)
            std::getline(ss, ocean_prox, ',');
            if (!ocean_prox.empty() && ocean_prox.back() == '\r') {
                ocean_prox.pop_back(); // Clean up carriage returns on Windows
            }

            // 4. Execute the Model Algorithm
            double result = model.predict(numerical_data, ocean_prox);

            // Output comparison
            std::cout << std::left << std::setw(8) << (row_count + 1)
                      << "$" << std::fixed << std::setprecision(2) << std::setw(19) << actual_value
                      << "$" << (result * 100000.0) << std::endl;

            row_count++;

        } catch (const std::exception& e) {
            std::cerr << "Data parsing error on row " << row_count + 1 << ": " << e.what() << std::endl;
        }
    }

    file.close();

    std::cout << " rows involves " << (row_count * 8) << " PMULT operations, "<< std::endl;

    return 0;
}