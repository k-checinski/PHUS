#include "finding_hus.h"

//
//std::vector<Sequence> find_hus(const Sequence &prefix, const std::vector<Sequence> &projected_sequences, unsigned r) {
//    /// PSTEP 1
//    std::vector<TSTuple> ts_table;
//    /// PSTEP 2
//    for (const Sequence& seq_y : projected_sequences) {
//        std::vector<Item> items_after =
//    }
//    /// PSTEP 3
//    return std::vector<Sequence>();
//}
//

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
