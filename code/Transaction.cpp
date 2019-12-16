//
// Created by jedikarix on 13.12.2019.
//

#include "Transaction.h"

inline bool has_item(const Item& item, const Transaction& transaction) {
    return item_count(item, transaction) != 0;
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

Transaction filter_transaction(const std::set<Item> &items, const Transaction &transaction) {
    Transaction new_trans;
    for (auto const& elem : transaction) {
        if (items.find(elem.first) != items.end()) {
            new_trans[elem.first] = elem.second;
        }
    }
    return new_trans;
}