//
// Created by karolina on 08.01.2020.
//

#ifndef PHUS_EDAMI_STATISTICS_H
#define PHUS_EDAMI_STATISTICS_H

#endif //PHUS_EDAMI_STATISTICS_H

#include "types.h"
#include "phus.h"


DiscoveredPatternStatistics get_statistics(const std::vector<Pattern>& patterns);

void show_average_from_statistics(const std::vector<DiscoveredPatternStatistics>& statistics);