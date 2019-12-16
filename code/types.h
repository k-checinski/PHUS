//
// Created by jedikarix on 16.12.2019.
//

#ifndef PHUS_EDAMI_TYPES_H
#define PHUS_EDAMI_TYPES_H

#include <list>
#include <set>
#include <map>

typedef unsigned Item;
typedef std::map<Item, unsigned> Transaction;
typedef std::list<Transaction> Sequence;
typedef std::map<Item, unsigned> ProfitTable;
typedef std::list<Sequence> SDB;

#endif //PHUS_EDAMI_TYPES_H
