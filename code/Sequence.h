//
// Created by jedikarix on 11.12.2019.
//

#ifndef PHUS_EDAMI_SEQUENCE_H
#define PHUS_EDAMI_SEQUENCE_H

#include <list>
#include <set>
#include <map>

#include "Transaction.h"

typedef unsigned Item;

typedef std::list<Transaction> Sequence;
typedef std::map<Item, unsigned> ProfitTable;
typedef std::list<Sequence> SDB;


bool has_item(const Item& item, const Sequence& sequence);
unsigned utility_of_item(const Item& item, const Sequence& seq, const ProfitTable& profit_table);
unsigned utility_of_subsequence(const Sequence& subseq, const Sequence& seq, const ProfitTable& profit_table);
unsigned actual_sequence_utility(const Item& item, const SDB& sdb, const ProfitTable& profit_table);
unsigned actual_sequence_utility(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);
unsigned sequence_utility(const Sequence& seq, const ProfitTable& profit_table);
unsigned sequence_utility_upper_bound(const Sequence& seq, const SDB& sdb, const ProfitTable& profit_table);
unsigned sequence_utility_upper_bound(const Item& item, const SDB& sdb, const ProfitTable& profit_table);


Sequence filter_sequence(const std::set<Item>& items, const Sequence& sequence);
SDB filter_SDB(const std::set<Item>& items, const SDB& sdb);

unsigned count_items(const Sequence& sequence);
#endif //PHUS_EDAMI_SEQUENCE_H
