//
// Created by jedikarix on 11.12.2019.
//

#ifndef PHUS_EDAMI_SEQUENCE_H
#define PHUS_EDAMI_SEQUENCE_H

#include <list>
#include <set>
#include <map>

typedef unsigned Item;

typedef std::map<Item, unsigned> Transaction;
typedef std::list<Transaction> Sequence;
typedef std::map<Item, unsigned> ProfitTable;
typedef std::list<Sequence> SDB;

inline bool has_item(const Item& item, const Transaction& transaction);
inline unsigned item_count(const Item& item, const Transaction& transaction);
unsigned transaction_utility(const Transaction& transaction, const ProfitTable& profit_table);
unsigned utility_of_item(const Item& item, const Sequence& seq, const ProfitTable& profit_table);
unsigned utility_of_subsequence(const Sequence& subseq, const Sequence& seq, const ProfitTable& profit_table);
unsigned actual_sequence_utility(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);
unsigned sequence_utility(const Sequence& seq, const ProfitTable& profit_table);
unsigned sequence_utility_upper_bound(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);

#endif //PHUS_EDAMI_SEQUENCE_H
