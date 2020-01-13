//
// Created by jedikarix on 22.12.2019.
//

#ifndef PHUS_EDAMI_PHUS_H
#define PHUS_EDAMI_PHUS_H

#include "finding_hus.h"
#include <chrono>

struct ItemTableTuple {
    unsigned asu = 0;
    unsigned suub = 0;
};

struct DiscoveredPatternStatistics {
    unsigned max = 0;
    unsigned min = INT8_MAX;
    double average = 0;
    double std_dev = 0;
};

std::vector<std::pair<Pattern, unsigned int>>
phus(const SDB &sequences, const ProfitTable &profit_table, unsigned util_threshold, unsigned max_len);

#endif //PHUS_EDAMI_PHUS_H
