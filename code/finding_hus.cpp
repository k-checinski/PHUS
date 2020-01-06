#include "finding_hus.h"


std::pair<std::vector<Pattern>, unsigned int>
find_hus(const Pattern &prefix, const std::vector<Sequence> &projected_seq, unsigned r,
         const ProfitTable &profit_table, unsigned util_threshold, unsigned hus_counter) {

    std::chrono::steady_clock::time_point hus_start = std::chrono::steady_clock::now();
    hus_counter++;
    std::cout << "Prefix: " << prefix << "\n";
    std::cout << "r = " << r << '\n';
    /// PSTEP 1
    TSTable ts_table;
    /// PSTEP 2

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (const Sequence &seq_y : projected_seq) {
        unsigned sequence_util = sequence_utility(seq_y, profit_table);
        std::vector<Pattern> p_primes = generate_prefix_patterns(seq_y, prefix);
        for (const Pattern &pattern : p_primes) {
//            /// There are analysed only patterns with mutual prefix. Thus we need only 2 last transactions in pattern
//            /// to recognise it in temporary sequence table.
//            Pattern shortened_pattern = {*(pattern.rend()), *(pattern.rend()-1)};
            unsigned mu = utility_of_pattern(pattern, seq_y, profit_table);
            update_table(ts_table, pattern, sequence_util, mu);
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "[TIME] generation of all prefix_patterns for prefix: " << prefix << " took "
              << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    std::cout << ts_table << "\n";
    /// PSTEP 3 / 4
    std::vector<Pattern> hsuub;
    std::vector<Pattern> hus;
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
            hus.push_back(tuple.pat);
        }
    }
    ///DEBUG
    std::cout << "HUS" << std::endl;
    for (const auto &seq : hus) {
        std::cout << seq << "\n";
    }
    std::cout << "\nHSUUB" << std::endl;
    for (const auto &seq : hsuub) {
        std::cout << seq << "\n";
    }
    /// PSTEP 5
    std::cout << "\nfiltered_projected_sequences\n";
    std::vector<Sequence> filtered_projected_sequences = filter_SDB(hsuub_items, projected_seq, r + 2);
    for (const auto &seq : filtered_projected_sequences) {
        std::cout << seq << "\n";
    }
    /// PSTEP 6
    for (const Pattern &pat : hsuub) {
        std::vector<Sequence> sdp_prime = filter_SDB(projected_sequences(pat, filtered_projected_sequences), r + 2);
        if (!sdp_prime.empty()) {
            std::vector<Pattern> hus_prime = find_hus(pat, sdp_prime, r + 1, profit_table, util_threshold, hus_counter).first;
            hus.insert(hus.end(), hus_prime.begin(), hus_prime.end());
        }
    }

    std::chrono::steady_clock::time_point hus_end = std::chrono::steady_clock::now();
    std::cout << "[TIME] hus duration for pattern: " << prefix << " and projected sequences: ";

    for (const auto &seq : projected_seq) {
        std::cout << seq << " ,";
    }

    std::cout << " took: " << std::chrono::duration_cast<std::chrono::microseconds>(
            hus_end - hus_start).count() << "[µs]" << std::endl;
    std::cout << std::endl;

    return std::pair<std::vector<Pattern>,unsigned>(hus, hus_counter);
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
