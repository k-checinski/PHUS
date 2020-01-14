#ifndef PHUS_EDAMI_TRANSACTION_H
#define PHUS_EDAMI_TRANSACTION_H

#include <map>
#include <set>
#include <iostream>

#include "types.h"

/**
 * Determines if transaction contains given item.
 * @param item
 * @param transaction
 * @return
 */
bool has_item(const Item& item, const Transaction& transaction);

unsigned pattern_elem_utility(const Transaction& t, const PatternElem& pat);
/**
 * Counts items in transaction.
 * @param item
 * @param transaction
 * @return
 */
unsigned item_count(const Item& item, const Transaction& transaction);

/**
 * Computes utility of transaction. Sums items quantities.
 * @param transaction
 * @return
 */
unsigned transaction_utility(const Transaction& transaction);

/**
 * Generates transaction based on given transaction. Keeps items from given set only.
 * @param items
 * @param transaction
 * @return new filtered transaction
 */
Transaction filter_transaction(const std::set<Item>& items, const Transaction& transaction);

bool is_partition(const PatternElem& pattern_elem, const Transaction &transaction);

std::ostream& operator<<(std::ostream& ost, const Transaction& trans);
std::ostream& operator<<(std::ostream& ost, const PatternElem& elem);
#endif //PHUS_EDAMI_TRANSACTION_H
