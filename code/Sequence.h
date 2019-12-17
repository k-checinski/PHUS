#ifndef PHUS_EDAMI_SEQUENCE_H
#define PHUS_EDAMI_SEQUENCE_H

#include <list>
#include <set>
#include <map>

#include "Transaction.h"
#include "IndexTable.h"

/**
 * Determines if given item occurs in sequence
 * @param item
 * @param sequence
 * @return
 */
bool has_item(const Item& item, const Sequence& sequence);

/**
 * Computes utility of item in sequence. Sums every occurring of item multiplied by item utility in profit table.
 * @param item
 * @param seq
 * @param profit_table
 * @return value of utility of item
 */
unsigned utility_of_item(const Item& item, const Sequence& seq, const ProfitTable& profit_table);

/**
 * Computes actual sequence utility in sequential database for given item. Sums utility of item for every sequence
 * for every sequence in database.
 * @param item
 * @param sdb
 * @param profit_table
 * @return value of actual sequence utility
 */
unsigned actual_sequence_utility(const Item& item, const SDB& sdb, const ProfitTable& profit_table);

/**
 * Computes sequence utility. Sums utility of every transaction in sequence.
 * @param seq
 * @param profit_table
 * @return
 */
unsigned sequence_utility(const Sequence& seq, const ProfitTable& profit_table);

/**
 * Computes sequence utility upper bound for given item. Sums utility of sequences where item occurred.
 * @param item
 * @param sdb
 * @param profit_table
 * @return
 */
unsigned sequence_utility_upper_bound(const Item& item, const SDB& sdb, const ProfitTable& profit_table);

/**
 * Generates sequence based on given sequence. Keeps items from given set only. Removes empty transactions.
 * @param items Items to be kept.
 * @param sequence
 * @return new sequence with given items only.
 */
Sequence filter_sequence(const std::set<Item>& items, const Sequence& sequence);

/**
 * Generates sequence database based on given database. Uses filter_sequence function for every sequence in sdb.
 * Removes empty sequences and sequences shorter than min_length
 * @param items
 * @param sdb
 * @param min_length
 * @return new database with given items only.
 */
SDB filter_SDB(const std::set<Item>& items, const SDB& sdb, unsigned min_length=0);

/**
 * Counts items in every transaction in sequence. E.g. for <{a(1), b(2)}, a(4), c(1)> returns 4.
 * @param sequence
 * @return number of items in sequence
 */
unsigned count_items(const Sequence& sequence);

std::vector<unsigned> projected_sequences(Item item, const IndexTable& index_table);
Sequence::const_iterator prefix_end_position(const Sequence& prefix, const Sequence& sequence);
#endif //PHUS_EDAMI_SEQUENCE_H
