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
    return log_normal_distribution(profit_generator);
}

Transaction SequenceReader::read_transaction(std::stringstream &transaction_data) {
    unsigned items_number;
    transaction_data >> items_number;
    Transaction transaction;
    while (items_number > 0) {
        Item item;
        transaction_data >> item;
        transaction.insert(std::pair<Item, unsigned>(item, generate_item_count()));
        items_number--;
    }
    return transaction;
}

std::pair<SDB, ProfitTable> SequenceReader::read_dataset(const std::string &file_name) {
    std::ifstream file;
    SDB dataset;
    ProfitTable profitTable;
    std::set<Item> processedItems;
    file.open(file_name);

    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream line_stream(line);
            Sequence sequence;
            unsigned transaction_number;
            line_stream >> transaction_number;
            while (transaction_number > 0) {
                Transaction transaction = read_transaction(line_stream);
                sequence.push_back(transaction);

                for (const std::pair<Item, unsigned> item : transaction) {
                    if (processedItems.find(item.first) == processedItems.end()) {
                        profitTable.insert(std::pair<Item, float>(item.first, generate_profit()));
                        processedItems.insert(item.first);
                    }
                }
                transaction_number--;
            }
            dataset.push_back(sequence);
        }
    } else {
        std::cout << "file couldn't be opened";
    }
    file.close();
    return std::pair<SDB, ProfitTable>(dataset, profitTable);
}

