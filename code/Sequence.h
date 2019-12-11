//
// Created by jedikarix on 11.12.2019.
//

#ifndef PHUS_EDAMI_SEQUENCE_H
#define PHUS_EDAMI_SEQUENCE_H

#include <list>
#include <set>
#include <map>
#include <utility>

typedef unsigned ItemType;
typedef std::pair<ItemType, unsigned> Item;
typedef std::set<Item> Transaction;
typedef std::list<Transaction> Sequence;
typedef std::map<ItemType, unsigned> ProfitTable;
typedef std::list<Sequence> SDB;

unsigned utility_of_item(const Item& item, const Sequence& seq, const ProfitTable& profit_table);
unsigned utility_of_subsequence(const Sequence& subseq, const Sequence& seq, const ProfitTable& profit_table);
unsigned actual_sequence_utility(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);
unsigned sequence_utility(const Sequence& seq, const ProfitTable& profitTable);
unsigned sequence_utility_upper_bound(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);

#endif //PHUS_EDAMI_SEQUENCE_H
