#include "Transaction.h"

bool has_item(const Item& item, const Transaction& transaction) {
    return item_count(item, transaction) != 0;
}

bool has_items(const Transaction &transaction, const PatternElem &items) {
    for (Item item : items) {
        if (!has_item(item, transaction))
            return false;
    }
    return true;
}


unsigned item_count(const Item& item, const Transaction& transaction) {
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

bool is_partition(const PatternElem &pattern_elem, const Transaction &transaction) {
    for (auto const& item: pattern_elem) {
        if (!has_item(item, transaction))
            return false;
    }
    return true;
}

unsigned pattern_elem_utility(const Transaction &t, const PatternElem &pat, const ProfitTable &profit_table) {
    unsigned utility = 0;
    for (Item item : pat) {
        Transaction::const_iterator it;
        if ((it = t.find(item)) != t.cend()) {
            utility += profit_table.at(item) * it->second;
        }
        else {
            return 0;
        }
    }
    return utility;
}

std::ostream &operator<<(std::ostream &ost, const Transaction &trans) {
    auto it_end = trans.cend();
    --it_end;
    for (auto it = trans.cbegin(); it != it_end; ++it) {
        ost << (*it).first << "(" << (*it).second << "), ";
    }
    auto it_last = trans.crbegin();
    ost << (*it_last).first << "(" << (*it_last).second << ")" ;
    return ost;
}

std::ostream &operator<<(std::ostream &ost, const PatternElem &elem) {
    auto it_end = elem.cend();
    --it_end;
    for (auto it = elem.cbegin(); it != it_end; ++it) {
        ost << (*it) << ", ";
    }
    auto it_last = elem.crbegin();
    ost << (*it_last);
    return ost;
}