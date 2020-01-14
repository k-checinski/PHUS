// #define DEBUG

#include "finding_hus.h"

std::pair<std::vector<std::pair<Pattern, unsigned int> >, unsigned int>
find_hus(const Pattern &prefix, const std::vector<Sequence> &projected_seq, unsigned r,
         unsigned util_threshold, unsigned hus_counter, unsigned max_len) {

    if (r > max_len -1 && max_len != 0) {
        return std::pair<std::vector<std::pair<Pattern, unsigned int> >, unsigned int>(std::vector<std::pair<Pattern, unsigned> >(), hus_counter);
    }
    hus_counter++;
#ifdef DEBUG
    std::cout << "Prefix: " << prefix << "\tr = " << r << '\n';
#endif
    /// PSTEP 1
    TSTable ts_table;
    /// PSTEP 2

    for (const Sequence &seq_y : projected_seq) {
        unsigned sequence_util = sequence_utility(seq_y);
        std::vector<Pattern> p_primes = generate_prefix_patterns(seq_y, prefix);
        for (const Pattern &pattern : p_primes) {
            unsigned mu = utility_of_pattern(pattern, seq_y);
            update_table(ts_table, pattern, sequence_util, mu);
        }
    }
#ifdef  DEBUG
    std::cout << "TS table\n";
    std::cout << ts_table << "\n";
#endif

    /// PSTEP 3 / 4
    std::vector<Pattern> hsuub;
    std::vector<std::pair<Pattern, unsigned>> hus;
    std::set<Item> hsuub_items;
    for (const TSTuple &tuple : ts_table) {
        if (tuple.suub >= util_threshold) {
            hsuub.push_back(tuple.pat);
            for (auto const &elem: tuple.pat) {
                for (Item item : elem) {
                    hsuub_items.insert(item);
                }
            }
        }
        if (tuple.asu >= util_threshold) {
            hus.emplace_back(tuple.pat, tuple.asu);
        }
    }

    /// PSTEP 5
    std::vector<Sequence> filtered_projected_sequences = filter_SDB(hsuub_items, projected_seq, r + 2);

    /// PSTEP 6
    for (const Pattern &pat : hsuub) {
        std::vector<Sequence> sdp_prime = filter_SDB(projected_sequences(pat, filtered_projected_sequences), r + 2);
        if (!sdp_prime.empty()) {
            std::vector<std::pair<Pattern, unsigned> > hus_prime = find_hus(pat, sdp_prime, r + 1, util_threshold, hus_counter,
                                                      max_len).first;
            push_back_uniques(hus, hus_prime);
        }
    }
    return std::pair<std::vector<std::pair<Pattern, unsigned>>,unsigned>(hus, hus_counter);
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
    for (TSTuple &tuple : table) {
        if (tuple.pat == pattern) {
            tuple.asu += mu;
            tuple.suub += su;
            return;
        }
    }
    table.push_back(TSTuple(pattern, su, mu));
}

std::ostream &operator<<(std::ostream &ost, const TSTable &table) {
    for (const auto &tuple : table) {
        ost << tuple.pat << "\tasu = " << tuple.asu << "\tsuub = " << tuple.suub << '\n';
    }
    return ost;
}

void push_back_uniques(std::vector<std::pair<Pattern, unsigned int>> &current,
        const std::vector<std::pair<Pattern, unsigned int>> &new_elems) {
    for (const auto& elem: new_elems) {
        bool unique = true;
        unsigned util = elem.second;
        for (const auto& curr_elem: current) {
            if (elem.first == curr_elem.first) {
                util = elem.second > curr_elem.second ? elem.second : curr_elem.second;
                unique = false;
                break;
            }
        }
        if (unique) {
            current.emplace_back(elem.first, util);
        }
    }
}
