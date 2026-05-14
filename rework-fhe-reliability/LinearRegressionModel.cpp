#include "LinearRegressionModel.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>

LinearRegressionModel::LinearRegressionModel() {
    weights = {-0.2, -0.2, 0.01, -0.0001, 0.001, -0.00004, 0.0005, 0.4};
    bias = -35.0;
    ocean_weights["<1H OCEAN"] = 0.1;
    ocean_weights["INLAND"] = -0.2;
    ocean_weights["NEAR OCEAN"] = 0.15;
    ocean_weights["NEAR BAY"] = 0.12;
    ocean_weights["ISLAND"] = 0.5;
}

double LinearRegressionModel::predict(const std::vector<double>& num_feats, const std::string& ocean_prox) const {
    if (num_feats.size() != weights.size()) throw std::invalid_argument("Feature size mismatch.");
    double prediction = bias;
    for (size_t i = 0; i < weights.size(); ++i) {
        prediction += (weights[i] * num_feats[i]);
    }
    if (ocean_weights.count(ocean_prox)) prediction += ocean_weights.at(ocean_prox);
    return prediction;
}

void LinearRegressionModel::processHousingCSV(const std::string& filename, int max_rows) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    int row_count = 0;
    while (std::getline(file, line) && row_count < max_rows) {
        std::stringstream ss(line);
        std::string token;
        std::vector<double> numerical_data;
        std::string ocean_prox;
        double actual_value = 0.0;

        for (int i = 0; i < 9; ++i) {
            std::getline(ss, token, ',');
            if (i == 8) actual_value = std::stod(token);
            else numerical_data.push_back(token.empty() ? 0.0 : std::stod(token));
        }
        std::getline(ss, ocean_prox, ',');
        if (!ocean_prox.empty() && ocean_prox.back() == '\r') ocean_prox.pop_back();

        double result = predict(numerical_data, ocean_prox);

        std::cout << "Row " << (row_count + 1)
                  << " | Actual: $" << std::fixed << std::setprecision(2) << actual_value
                  << " | Predicted: $" << (result * 100000.0) << std::endl;
        row_count++;
    }
    file.close();
}