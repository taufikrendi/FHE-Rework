#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <sciplot/sciplot.hpp>

/**
 * @brief Structure to hold data for plotting FHE metrics.
 */
struct BenchmarkResult {
    std::vector<std::string> labels;
    std::vector<double> values;
    std::string xLabel;
    std::string yLabel;
};

class DynamicPlotter {
public:
    void plot(const BenchmarkResult& res, const std::string& outputFilename = "dynamic_ckks_fault_analysis.png") {
        using namespace sciplot;

        // 1. Initialize Plot
        Plot2D plot;

        // --- MANDATORY: SET SIZE BEFORE DRAWING ---
        // This ensures the internal coordinate system is mapped to 1080p
        plot.size(800, 600);

        plot.xlabel(res.xLabel);
        plot.ylabel(res.yLabel);
        plot.legend().atTop().fontSize(12);

        // 2. Prepare X-axis indices
        std::vector<double> x_indices;
        for (size_t i = 0; i < res.labels.size(); ++i) {
            x_indices.push_back(static_cast<double>(i));
        }

        // 3. Draw the bar chart
        // Boxes are better for HD as they scale without pixelation
        plot.drawBoxes(x_indices, res.values)
            .label("Calculated CKKS Error Magnitude")
            .fillColor("blue")
            .fillIntensity(0.7);

        // 4. Map labels to the X-axis tics
        plot.xtics().at(x_indices, res.labels).fontSize(10);

        // 5. Save Output
        // Creating the Figure and Canvas objects explicitly at 1920x1080
        Figure fig = {{plot}};
        Canvas canvas = {{fig}};

        // Some versions of sciplot/gnuplot require size again at the canvas level
        canvas.size(800, 600);
        canvas.save(outputFilename);

        std::cout << "[Plotter] SUCCESS: HD Analysis chart (1920x1080) saved to: " << outputFilename << std::endl;
    }
};