//
// Created by jedikarix on 16.12.2019.
//

#ifndef PHUS_EDAMI_TYPES_H
#define PHUS_EDAMI_TYPES_H

#include <list>
#include <set>
#include <vector>
#include <map>

typedef unsigned Item;
typedef std::map<Item, unsigned> Transaction;
typedef std::vector<Transaction> Sequence;
typedef std::map<Item, unsigned> ProfitTable;
typedef std::vector<Sequence> SDB;

#endif //PHUS_EDAMI_TYPES_H
