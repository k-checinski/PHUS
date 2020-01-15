#include "catch.hpp"

#include "../code/SequenceReader.h"

TEST_CASE("All sequences are loaded") {
    SequenceReader sequence_reader;

    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset("../tests/data/sample.data", true);
    SDB sequences = result.first;
    CHECK(sequences.size() == 2);
}

TEST_CASE("All transactions in sequence are loaded") {
    SequenceReader sequence_reader;
    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset("../tests/data/sample.data", true);
    SDB sequences = result.first;
    CHECK(sequences.front().size() == 9);
    CHECK(std::next(sequences.begin())->size() == 10);
}

TEST_CASE("All transaction's items are loaded") {
    SequenceReader sequence_reader;
    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset("../tests/data/sample.data", true);
    SDB sequences = result.first;
    CHECK(std::next(sequences.begin())->front().size() == 4);
}

TEST_CASE("Items occurrence in transaction is in range <1,5>") {
    SequenceReader sequence_reader;
    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset("../tests/data/sample.data", true);
    SDB sequences = result.first;
    for (auto &&sequence : sequences) {
        for (auto &&transaction : sequence) {
            for (auto &&item : transaction) {
                CHECK(item.second >= 1);
                CHECK(item.second <= 5);
            }
        }
    }
}

TEST_CASE("All items have profit value assigned") {
    SequenceReader sequence_reader;
    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset(
            "../tests/data/sample.data", true);
    ProfitTable profit_table = result.second;
    CHECK(profit_table.size() == 9);
}

TEST_CASE("Profit values are in range <0.1,10>") {
    SequenceReader sequence_reader;
    const std::pair<SDB, ProfitTable> result = sequence_reader.read_dataset(
            "../tests/data/sample.data", true);
    ProfitTable profit_table = result.second;
    for (auto &&profit_row : profit_table) {
        CHECK(profit_row.second >= 0.1);
        CHECK(profit_row.second <= 10);
    }
}