#include <iostream>
#include <sciplot/sciplot.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>
// Include our modular classes
// #include "lib/Utils.cpp"
#include "lib/Plotter.h"
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

    //Linier Regression
    std::cout << "--- Starting Dynamic CKKS Reliability Analysis ---\n" << std::endl;

    // 1. Initialize FHE Parameters (N=8192, Scale=2^40)
    size_t ring_dim = 8192;
    double ckks_scale = std::pow(2.0, 40);
    FHEReliability reliabilitySim(ring_dim, ckks_scale);

    LinearRegressionModel lrModel;

    // 2. Process data with faults
    std::cout << "Processing dataset with simulated memory fault...\n";
    // lrModel.processHousingCSVWithFaults("../data/housing.csv", reliabilitySim);

    // 3. Generate DYNAMIC Benchmark Data
    // We now pass the simulator so it can calculate exact mathematically sound errors
    BenchmarkResult lr_res = lrModel.processHousingCSVWithFaults("housing.csv", reliabilitySim);

    // 4. Plot the results
    DynamicPlotter plotter;
    plotter.plot(lr_res, "ckks_fault_analysis.png");

    std::cout << "\nAnalysis Complete. Check 'dynamic_ckks_fault_analysis.png'." << std::endl;

    return 0;
}