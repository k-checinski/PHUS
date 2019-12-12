#include "Sequence.h"

inline bool has_item(const Item& item, const Transaction& transaction) {
    return transaction.count(item) != 0;
}

inline unsigned item_count(const Item& item, const Transaction& transaction) {
    return transaction.count(item) != 0 ? transaction.at(item) : 0;
}

unsigned transaction_utility(const Transaction& transaction, const ProfitTable& profit_table) {
    unsigned utility = 0;
    for (auto const& item : transaction)
        utility += item.second * profit_table.at(item.first);
    return utility;
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


unsigned sequence_utility(const Sequence& seq, const ProfitTable& profit_table) {
    unsigned utility = 0;
    for (const Transaction& t : seq) {
        utility += transaction_utility(t, profit_table);
    }
    return utility;
}