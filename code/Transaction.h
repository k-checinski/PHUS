//
// Created by jedikarix on 13.12.2019.
//

#ifndef PHUS_EDAMI_TRANSACTION_H
#define PHUS_EDAMI_TRANSACTION_H

#include <map>
#include <set>

typedef unsigned Item;
typedef std::map<Item, unsigned> ProfitTable;
typedef std::map<Item, unsigned> Transaction;

inline bool has_item(const Item& item, const Transaction& transaction);
inline unsigned item_count(const Item& item, const Transaction& transaction);
unsigned transaction_utility(const Transaction& transaction, const ProfitTable& profit_table);
Transaction filter_transaction(const std::set<Item>& items, const Transaction& transaction);

#endif //PHUS_EDAMI_TRANSACTION_H
