//
// Created by jedikarix on 22.12.2019.
//

#ifndef PHUS_EDAMI_PHUS_H
#define PHUS_EDAMI_PHUS_H

#include "finding_hus.h"

struct ItemTableTuple {
    unsigned asu = 0;
    unsigned suub = 0;
};

std::vector<Pattern> phus(const SDB &sequences, const ProfitTable &profit_table, unsigned util_threshold);

#endif //PHUS_EDAMI_PHUS_H
