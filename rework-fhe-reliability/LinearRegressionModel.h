#ifndef LINEAR_REGRESSION_MODEL_H
#define LINEAR_REGRESSION_MODEL_H

#include <vector>
#include <string>
#include <map>

class LinearRegressionModel {
private:
    std::vector<double> weights;
    double bias;
    std::map<std::string, double> ocean_weights;

public:
    LinearRegressionModel();
    double predict(const std::vector<double>& numerical_features, const std::string& ocean_proximity) const;

    // Add this declaration so the compiler can find it
    void processHousingCSV(const std::string& filename, int max_rows);
};

#endif