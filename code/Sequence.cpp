#include "Sequence.h"

#include <iostream>

bool has_item(const Item& item, const Sequence& sequence) {
    for (const Transaction & transaction : sequence) {
        if (has_item(item, transaction))
            return true;
    }
    return false;
}

unsigned utility_of_item(const Item& item, const Sequence& seq, const ProfitTable& profit_table) {
    unsigned max_util = 0;
    for (const Transaction& t : seq) {
        unsigned utility;
        if ((utility = item_count(item, t) * profit_table.at(item)) > max_util)
            max_util = utility;
    }
    return max_util;
}

unsigned actual_sequence_utility(const Item& item, const SDB& sdb, const ProfitTable& profit_table) {
    unsigned utility = 0;
    for (const Sequence& seq : sdb) {
        utility += utility_of_item(item, seq, profit_table);
    }
    return utility;
}

unsigned sequence_utility(const Sequence& seq, const ProfitTable& profit_table) {
    unsigned utility = 0;
    for (const Transaction& t : seq) {
        utility += transaction_utility(t, profit_table);
    }
    return utility;
}

unsigned sequence_utility_upper_bound(const Item& item, const SDB& sdb, const ProfitTable& profit_table) {
    unsigned utility = 0;
    for (const Sequence& seq : sdb) {
        if (has_item(item, seq))
            utility += sequence_utility(seq, profit_table);
    }
    return utility;
}

Sequence filter_sequence(const std::set<Item>& items, const Sequence& sequence) {
    Sequence new_sequence;
    for (const Transaction& trans : sequence) {
        Transaction filtered_trans = filter_transaction(items, trans);
        if (!filtered_trans.empty()) {
            new_sequence.push_back(filtered_trans);
        }
    }
    return new_sequence;
}

SDB filter_SDB(const std::set<Item>& items, const SDB& sdb, unsigned min_length) {
    SDB new_sdb;
    min_length = min_length > 1 ? min_length : 1;
    for (const Sequence& sequence : sdb) {
        Sequence filtered_sequence = filter_sequence(items, sequence);
        if (count_items(filtered_sequence) >= min_length) {
            new_sdb.push_back(filtered_sequence);
        }
    }
    return new_sdb;
}

SDB filter_SDB(const SDB &sdb, unsigned int min_length) {
    SDB new_sdb;
    min_length = min_length > 1 ? min_length : 1;
    for (const Sequence& sequence : sdb) {
        if (count_items(sequence) >= min_length) {
            new_sdb.push_back(sequence);
        }
    }
    return new_sdb;
}

unsigned count_items(const Sequence &sequence) {
    unsigned items = 0;
    for (const Transaction& transaction : sequence) {
        items += transaction.size();
    }
    return items;
}

std::vector<unsigned> projected_sequences(Item item, const IndexTable &index_table) {
    std::vector<unsigned> sequences_ids;
    for (auto const& index : index_table.at(item)) {
        sequences_ids.push_back(index.sequence_id);
    }
    return sequences_ids;
}

std::vector<Sequence> projected_sequences(const Pattern &pattern, const std::vector<Sequence> &sequences) {
    std::vector<Sequence> proj_sequences;
    for (const Sequence& seq : sequences) {
        auto it = prefix_end_position(pattern, seq);
        if (it != seq.cend()) {
            proj_sequences.emplace_back(it, seq.end());
        }
    }
    return proj_sequences;
}

Sequence::const_iterator prefix_end_position(const Pattern& prefix, const Sequence& sequence) {
    auto sequence_iter = sequence.cbegin();
    unsigned found = 0;
    for (const PatternElem& transaction: prefix) {
        for (; sequence_iter != sequence.cend(); ++sequence_iter) {
            if (is_partition(transaction, *sequence_iter)) {
                ++sequence_iter;
                ++found;
                break;
            }
        }
        if (sequence_iter == sequence.cend() || prefix.size() == found) {
            break;
        }
    }
    if (prefix.size() == found) {
        return --sequence_iter;
    }
    return sequence_iter;
}

std::set<Item> items_between(Sequence::const_iterator first, Sequence::const_iterator last) {
    std::set<Item> found_items;
    for (auto it = first; it != last; ++it) {
        const Transaction& tr = *it;
        for (const auto& item : tr) {
            found_items.insert(item.first);
        }
    }
    return found_items;
}

std::set<Item> items_in_supersets(Sequence::const_iterator first, Sequence::const_iterator last,
        const PatternElem& elem) {
    std::set<Item> found_items;
    for (auto it = first; it != last; ++it) {
        const Transaction& tr = *it;
        if (is_partition(elem, tr))
            for (const auto& item : tr) {
                found_items.insert(item.first);
            }
    }
    return found_items;
}

unsigned utility_of_pattern(const Pattern &pattern, const Sequence &seq, const ProfitTable &profit_table) {
    unsigned max_fit_len = 0;
    unsigned best_utility = 0;
    std::vector<unsigned> prev_row = {0};
    std::vector<unsigned> curr_row = {0};
    for (unsigned i = 1; i < seq.size() + 1; ++i) {
        for (unsigned j = 1; j <= max_fit_len; ++j) {
            unsigned non_fit_gain = prev_row[j];
            unsigned d_fit_gain = pattern_elem_utility(seq[i - 1], pattern[j - 1], profit_table);
            unsigned fit_gain = d_fit_gain != 0 ? prev_row[j - 1] + d_fit_gain : 0;
            curr_row.push_back(non_fit_gain > fit_gain ? non_fit_gain : fit_gain);
        }
        if (max_fit_len != pattern.size()) {
            unsigned d_fit_gain = pattern_elem_utility(seq[i - 1], pattern[max_fit_len], profit_table);
            if (d_fit_gain != 0) {
                curr_row.push_back(prev_row[max_fit_len] + d_fit_gain);
                ++max_fit_len;
            }
        }
        if (best_utility < curr_row[curr_row.size()-1]) {
            best_utility = curr_row[curr_row.size()-1];
        }
        prev_row = curr_row;
        curr_row = std::vector<unsigned>({0});
    }
    return best_utility;
}

std::ostream &operator<<(std::ostream &ost, const Sequence &seq) {
    ost<<"<";
    auto it_end = seq.cend();
    --it_end;
    for (auto it = seq.cbegin(); it != it_end; ++it) {
        if ((*it).size() > 1)
            ost << "{";
        ost << (*it);
        if ((*it).size() > 1)
            ost << "}";
        ost << ", ";
    }
    auto it = seq.crbegin();
    if ((*it).size() > 1)
        ost << "{";
    ost << (*it);
    if ((*it).size() > 1)
        ost << "}";
    ost << ">\n";
    return ost;
}


