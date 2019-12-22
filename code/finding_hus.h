//
// Created by jedikarix on 17.12.2019.
//

#ifndef PHUS_EDAMI_FINDING_HUS_H
#define PHUS_EDAMI_FINDING_HUS_H

#include <utility>

#include "Sequence.h"

struct TSTuple {
    TSTuple(Pattern  _pattern, unsigned _suub, unsigned _asu)
    : pat(std::move(_pattern))
    , suub(_suub)
    , asu(_asu){};
    const Pattern pat;
    unsigned suub;
    unsigned asu;
};

typedef std::vector<TSTuple> TSTable;

void update_table(TSTable& table, const Pattern& pattern, unsigned su, unsigned mu);

std::vector<Pattern> generate_prefix_patterns(const Sequence& seq, const Pattern& prefix);
std::vector<Pattern> find_hus(const Pattern &prefix, const std::vector<Sequence> &projected_sequences, unsigned r,
                               const ProfitTable &profit_table, unsigned util_threshold);

std::ostream& operator<<(std::ostream& ost, const TSTable& table);


#endif //PHUS_EDAMI_FINDING_HUS_H
