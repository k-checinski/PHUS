//
// Created by Karola on 2019-12-13.
//

#ifndef PHUS_EDAMI_SEQUENCEREADER_H
#define PHUS_EDAMI_SEQUENCEREADER_H


#include <random>
#include "Sequence.h"

class SequenceReader {

public:
    SequenceReader();

    std::pair<SDB, ProfitTable> read_dataset(const std::string &file_name);

private:
    const unsigned MIN_ITEM_COUNT = 1;
    const unsigned MAX_ITEM_COUNT = 5;
    const double MIN_PROFIT = 0.01;
    const double MAX_PROFIT = 1;

    std::default_random_engine items_generator;
    std::default_random_engine profit_generator;

    std::uniform_int_distribution<unsigned> distribution;
    std::lognormal_distribution<double> log_normal_distribution;

    unsigned generate_item_count();

    float generate_profit();

    Transaction read_transaction(std::stringstream &transaction_data);
};


#endif //PHUS_EDAMI_SEQUENCEREADER_H
