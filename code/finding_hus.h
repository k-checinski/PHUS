//
// Created by jedikarix on 17.12.2019.
//

#ifndef PHUS_EDAMI_FINDING_HUS_H
#define PHUS_EDAMI_FINDING_HUS_H

#include "Sequence.h"

struct TSTuple {
    TSTuple(const Sequence& _pattern, unsigned _suub, unsigned _asu)
    : pattern(_pattern)
    , suub(_suub)
    , asu(_asu){};
    const Sequence& pattern;
    unsigned suub;
    unsigned asu;
};

std::vector<Pattern> generate_prefix_patterns(const Sequence& seq, const Pattern& prefix);
std::vector<Sequence> find_hus(const Sequence& prefix, const std::vector<Sequence>& projected_sequences, unsigned r);


#endif //PHUS_EDAMI_FINDING_HUS_H
