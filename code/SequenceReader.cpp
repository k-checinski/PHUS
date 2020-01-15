//
// Created by Karola on 2019-12-13.
//

#include "SequenceReader.h"
#include "Sequence.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

SequenceReader::SequenceReader() : distribution(MIN_ITEM_COUNT, MAX_ITEM_COUNT),
                                   log_normal_distribution(MIN_PROFIT, MAX_PROFIT) {
}

unsigned SequenceReader::generate_item_count() {
    return distribution(items_generator);
}

float SequenceReader::generate_profit() {
    return ceil(log_normal_distribution(profit_generator));
}

Transaction SequenceReader::read_transaction(std::stringstream &transaction_data, bool should_generate_items_count) {
    unsigned items_number;
    transaction_data >> items_number;
    std::string item_string;
    Transaction transaction;
    while (items_number > 0) {
        Item item;
        if (!should_generate_items_count) {
            transaction_data >> item_string;
            auto item_count_start_index = item_string.find('(');
            auto item_count_end_index = item_string.find(')');
            if (item_count_start_index == std::string::npos || item_count_end_index == std::string::npos
                || item_count_end_index < item_count_start_index) {
                std::cout << "invalid file input";
                std::exit(1);
            }
            std::string item_identifier = item_string.substr(0, item_count_start_index);
            std::string item_count = item_string.substr(item_count_start_index + 1, item_count_end_index - item_count_start_index -1);
            item = std::atoi(item_identifier.c_str());
            unsigned count = std::atoi(item_count.c_str());
            transaction.insert(std::pair<Item, unsigned>(item, count));
        } else {
            transaction_data >> item_string;
            item = std::atoi(item_string.c_str());
            transaction.insert(std::pair<Item, unsigned>(item, generate_item_count()));
        }
        items_number--;
    }
    return transaction;
}


ProfitTable SequenceReader::read_profit_table(std::ifstream &file_stream, const std::set<Item> &items_in_dataset) {
    std::string line;
    std::set<Item> processed_items;
    ProfitTable profit_table;

    while (getline(file_stream, line)) {
        Item item;
        unsigned value;
        std::stringstream line_stream(line);
        line_stream >> item;
        line_stream >> value;
        profit_table.insert(std::pair<Item, double>(item, value));
        processed_items.insert(item);
    }
    for (Item item : items_in_dataset) {
        if (processed_items.find(item) == processed_items.end()) {
            std::cout << "invalid input data - item " + std::to_string(item) + " has no profit value";
            std::exit(1);
        }
    }
    return profit_table;
}

std::pair<SDB, ProfitTable>
SequenceReader::read_dataset(const std::string &file_name, const bool should_generate_items_count) {
    std::ifstream file;
    SDB dataset;
    ProfitTable profit_table;
    std::set<Item> processedItems;
    file.open(file_name);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream line_stream(line);
            if (line == "PROFIT_TABLE") {
                profit_table = read_profit_table(file, processedItems);
                return std::pair<SDB, ProfitTable>(dataset, profit_table);
            }
            Sequence sequence;
            unsigned transaction_number;
            line_stream >> transaction_number;
            while (transaction_number > 0) {
                Transaction transaction = read_transaction(line_stream, should_generate_items_count);
                sequence.push_back(transaction);

                for (const std::pair<Item, unsigned> item : transaction) {
                    processedItems.insert(item.first);
                }
                transaction_number--;
            }
            dataset.push_back(sequence);
        }
    } else {
        std::cout << "file couldn't be opened";
        std::exit(1);
    }
    file.close();
    profit_table = generate_profit_table(processedItems);
    return std::pair<SDB, ProfitTable>(dataset, profit_table);
}

ProfitTable SequenceReader::generate_profit_table(const std::set<Item> &itemSet) {
    ProfitTable profit_table;
    for (const Item &item : itemSet) {
        profit_table.insert(std::pair<Item, float>(item, generate_profit()));
    }
    return profit_table;
}
