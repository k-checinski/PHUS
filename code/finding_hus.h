//
// Created by jedikarix on 17.12.2019.
//

#ifndef PHUS_EDAMI_FINDING_HUS_H
#define PHUS_EDAMI_FINDING_HUS_H

#include <utility>
#include <chrono>

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

void update_table(TSTable &table, const Pattern &pattern, unsigned su, unsigned mu);

std::vector<Pattern> generate_prefix_patterns(const Sequence &seq, const Pattern &prefix);

std::pair<std::vector<std::pair<Pattern, unsigned int> >, unsigned int>
find_hus(const Pattern &prefix, const std::vector<Sequence> &projected_seq, unsigned r,
         unsigned util_threshold, unsigned hus_counter, unsigned max_len);

std::ostream &operator<<(std::ostream &ost, const TSTable &table);

void push_back_uniques(std::vector<std::pair<Pattern, unsigned int>> &current,
                       const std::vector<std::pair<Pattern, unsigned int>> &new_elems);

#endif //PHUS_EDAMI_FINDING_HUS_H
