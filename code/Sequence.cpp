#include "Sequence.h"

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

Sequence::const_iterator prefix_end_position(const Pattern& prefix, const Sequence& sequence) {
    auto sequence_iter = sequence.cbegin();
    for (const PatternElem& transaction: prefix) {
        for (; sequence_iter != sequence.cend(); ++sequence_iter) {
            if (is_partition(transaction, *sequence_iter)) {
                ++sequence_iter;
                break;
            }
        }
        if (sequence_iter == sequence.cend()) {
            return sequence_iter;
        }
    }
    return --sequence_iter;
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