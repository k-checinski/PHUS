#include "finding_hus.h"


std::vector<Pattern> find_hus(const Pattern &prefix, const std::vector<Sequence> &projected_seq, unsigned r,
                              const ProfitTable &profit_table, unsigned util_threshold) {
    /// PSTEP 1
    TSTable ts_table;
    /// PSTEP 2
    for (const Sequence& seq_y : projected_seq) {
        unsigned sequence_util = sequence_utility(seq_y, profit_table);
        std::vector<Pattern> p_primes = generate_prefix_patterns(seq_y, prefix);
        for (const Pattern& pattern : p_primes) {
//            /// There are analysed only patterns with mutual prefix. Thus we need only 2 last transactions in pattern
//            /// to recognise it in temporary sequence table.
//            Pattern shortened_pattern = {*(pattern.rend()), *(pattern.rend()-1)};
            unsigned mu = utility_of_pattern(pattern, seq_y, profit_table);
            update_table(ts_table, pattern, sequence_util, mu);
        }
    }
    /// PSTEP 3 / 4
    std::vector<Pattern> hsuub;
    std::vector<Pattern> hus;
    std::set<Item> hsuub_items;
    for (const TSTuple& tuple : ts_table) {
        if (tuple.suub >= util_threshold) {
            hsuub.push_back(tuple.pat);
        }
        if (tuple.asu >= util_threshold) {
            hus.push_back(tuple.pat);
        }
    }
    /// PSTEP 5
    std::vector<Sequence> filtered_projected_sequences = filter_SDB(hsuub_items, projected_seq, r + 2);
    /// PSTEP 6
    for (const Pattern& pat : hsuub) {
        projected_sequences(pat, filtered_projected_sequences);
    }
//    std::vector<Sequence> projected_sequences_prime =

    return hus;
}


std::vector<Pattern> generate_prefix_patterns(const Sequence &seq, const Pattern &prefix) {
    auto prefix_end = prefix_end_position(prefix, seq);
    if (prefix_end == seq.end()) {
        return std::vector<Pattern>();
    }

    PatternElem last_prefix_elem = *(prefix.rbegin());
    std::set<Item> items_at_end = items_in_supersets(prefix_end, seq.cend(), last_prefix_elem);
    std::set<Item> items_behind_prefix = items_between(std::next(prefix_end, 1), seq.cend());
    std::vector<Pattern> patterns;

    for (Item item : items_at_end) {
        if (last_prefix_elem.find(item) == last_prefix_elem.end()) {
            Pattern new_pattern = prefix;
            new_pattern.back().insert(item);
            patterns.push_back(new_pattern);
        }
    }

    for (Item item : items_behind_prefix) {
        Pattern new_pattern = prefix;
        new_pattern.push_back(PatternElem({item}));
        patterns.push_back(new_pattern);
    }

    return patterns;
}

void update_table(TSTable &table, const Pattern &pattern, unsigned su, unsigned mu) {
    for (TSTuple& tuple : table) {
        if (tuple.pat == pattern) {
            tuple.asu += mu;
            tuple.suub += su;
            return;
        }
    }
    table.push_back(TSTuple(pattern, su, mu));
}
