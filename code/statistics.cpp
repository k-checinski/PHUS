//
// Created by karolina on 08.01.2020.
//

#include <cmath>
#include "statistics.h"
#include "phus.h"


DiscoveredPatternStatistics get_statistics(const std::vector<std::pair<Pattern, unsigned int>> &patterns) {

    unsigned cardinalities_sum = 0;
    double variance = 0;
    DiscoveredPatternStatistics statistics;

    for (const auto &pattern : patterns) {
        if (pattern.first.size() > statistics.max) {
            statistics.max = pattern.first.size();
        }
        if (pattern.first.size() < statistics.min) {
            statistics.min = pattern.first.size();
        }
        cardinalities_sum += pattern.first.size();
    }
    statistics.average = cardinalities_sum / patterns.size();


    for (const auto &pattern : patterns) {
        variance += pow(pattern.first.size() - statistics.average, 2);
    }
    variance = variance / patterns.size();
    statistics.std_dev = sqrt(variance);

    return statistics;
}

void show_average_from_statistics(const std::vector<DiscoveredPatternStatistics> &statistics) {
    unsigned min_cardinalities_sum = 0, max_cardinalities_sum = 0;
    double average_cardinalities_sum = 0, cardinalities_std_dev_sum = 0;

    DiscoveredPatternStatistics average_statistics;

    for (const auto &statistic : statistics) {
        min_cardinalities_sum += statistic.min;
        max_cardinalities_sum += statistic.max;
        average_cardinalities_sum += statistic.average;
        cardinalities_std_dev_sum += statistic.std_dev;
    }

    average_statistics.min = min_cardinalities_sum / statistics.size();
    average_statistics.max = max_cardinalities_sum / statistics.size();
    average_statistics.average = average_cardinalities_sum / statistics.size();
    average_statistics.std_dev = cardinalities_std_dev_sum / statistics.size();

    std::cout << "[AVERAGE] Patterns minimum cardinality: "  << average_statistics.min << "\n";
    std::cout << "[AVERAGE] Patterns average cardinality: "  << average_statistics.average << "\n";
    std::cout << "[AVERAGE] Patterns maximum cardinality: "  << average_statistics.max << "\n";
    std::cout << "[AVERAGE] Patterns cardinality standard deviation: "  << average_statistics.std_dev << "\n";
}
