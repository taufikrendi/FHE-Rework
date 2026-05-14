#include <iostream>
#include <sciplot/sciplot.hpp>

// Include our modular classes
#include "Utils.cpp"
#include "BFVBenchmarker.cpp"
#include "CKKSBenchmarker.cpp"
#include "FHEReliabilitySim.cpp"

using namespace sciplot;

void PlotResults(const BenchmarkResult& res) {
    std::vector<double> x_coords;
    for(size_t i = 0; i < res.stages.size(); ++i) x_coords.push_back(static_cast<double>(i));

    Plot2D plot;
    plot.xlabel("FHE Pipeline Stage");
    plot.ylabel("Time (ms)");
    plot.xtics().at(x_coords, res.stages);

    // widths must match the number of stages
    std::vector<double> widths(res.stages.size(), 0.7);

    plot.drawBoxes(x_coords, res.time_ms, widths)
        .label(res.algoName + " Latency")
        .fillColor("blue")
        .fillIntensity(0.5);

    Figure fig = {{plot}};
    Canvas canvas = {{fig}};

    // Updated Resolution
    canvas.size(1200, 800);

    canvas.save(res.algoName + "_benchmark.png");
    std::cout << ">> " << res.algoName << " report generated (1200x800)." << std::endl;
}

int main() {
    std::cout << "--- Starting Comparative FHE Benchmarking ---" << std::endl;

    // Run BFV
    BenchmarkResult bfvRes = BFVBenchmarker::Run();
    PlotResults(bfvRes);

    // Run CKKS
    BenchmarkResult ckksRes = CKKSBenchmarker::Run();
    PlotResults(ckksRes);

    std::cout << "--- All Benchmarks Finished ---" << std::endl;

    // Parameters based on the paper's methodology
    size_t ring_dimension = 8192; // N
    size_t modulus_levels = 4;    // L (Number of RNS primes)

    // Initialize the simulation
    FHEReliabilitySim simulator(ring_dimension, modulus_levels);

    std::cout << "--- Starting FHE Reliability Analysis ---" << std::endl;

    // Simulate 3 random bitflips in the system memory
    for(int i = 0; i < 3; ++i) {
        simulator.injectMemoryFault();
    }

    std::cout << "Simulation Complete. Decrypt result to check for SDC." << std::endl;

    return 0;
}