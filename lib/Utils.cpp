#ifndef FHE_UTILS_HPP
#define FHE_UTILS_HPP

#include <vector>
#include <string>
#include <sys/resource.h>

class BenchmarkResult {
public:
    std::string algoName;
    std::vector<std::string> stages;
    std::vector<double> time_ms;
    std::vector<double> memory_mb;

    void addStage(const std::string& name, double time, double memory) {
        stages.push_back(name);
        time_ms.push_back(time);
        memory_mb.push_back(memory);
    }
};

class MemoryMonitor {
public:
    static double getUsageMB() {
        struct rusage usage;
        getrusage(RUSAGE_SELF, &usage);
        return static_cast<double>(usage.ru_maxrss) / 1024.0;
    }
};

#endif