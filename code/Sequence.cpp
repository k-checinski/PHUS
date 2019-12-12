#include "Sequence.h"

inline bool has_item(const Item& item, const Transaction& transaction) {
    return transaction.count(item) != 0;
}

inline unsigned item_count(const Item& item, const Transaction& transaction) {
    return transaction.count(item) != 0 ? transaction.at(item) : 0;
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
