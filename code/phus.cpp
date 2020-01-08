//
// Created by jedikarix on 22.12.2019.
//
#include <iostream>
#include "phus.h"

std::vector<Pattern>
phus(const SDB &sequences, const ProfitTable &profit_table, unsigned util_threshold, unsigned max_len) {
    std::map<Item, ItemTableTuple> item_table;
    for (auto const &row: profit_table) {
        item_table[row.first] = ItemTableTuple();
    }
    /// STEP 1/2

    /// calculate one-item subsequences and their asu and suub

    for (auto const &sequence: sequences) {
        for (auto const &transaction: sequence) {
            unsigned seq_util = sequence_utility(sequence, profit_table);
            for (auto const &item: transaction) {
                unsigned util = profit_table.at(item.first) * item.second;
                item_table[item.first].asu += util;
                item_table[item.first].suub += seq_util;
            }
        }
    }

    /// STEP 3/4
    std::set<Item> promising_items;
    std::vector<Pattern> hsuub;
    std::vector<Pattern> hus;
    for (auto const &item_tuple: item_table) {
        if (item_tuple.second.suub >= util_threshold) {
            promising_items.insert(item_tuple.first);
            hsuub.push_back(Pattern({{item_tuple.first}}));
        }
        if (item_tuple.second.asu >= util_threshold) {
            hus.push_back(Pattern({{item_tuple.first}}));
        }
    }
    /// STEP 5
    unsigned r = 1;
    /// STEP 6
    SDB filtered_sdb = filter_SDB(promising_items, sequences, r + 1);
    /// STEP 7
    IndexTable index_table = create_index_table(filtered_sdb, promising_items);

    /// STEP 8

    unsigned hus_counter = 0;
    for (auto const &pattern : hsuub) {

        Item item = *(pattern[0].begin());
        std::vector<Sequence> sdp;
        for (auto const &index : index_table.at(item)) {
            sdp.push_back(filtered_sdb.at(index.sequence_id));
        }
        auto found_hus = find_hus(pattern, sdp, r, profit_table, util_threshold, hus_counter, max_len);
        std::vector<Pattern> hus_prime = found_hus.first;
        hus_counter += found_hus.second;
        push_back_uniques(hus, hus_prime);
    }

    std:: cout << "number of find_hus calls: " << hus_counter << std::endl;
    return hus;
}

