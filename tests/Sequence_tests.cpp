#include "catch.hpp"

#include "../code/Sequence.h"

TEST_CASE("Appearance of item in sequence is checked correctly") {
    Sequence seq = {Transaction{{1, 5}}, Transaction{{2, 1}, {3, 2}}};
    REQUIRE(has_item(1, seq));
    REQUIRE(has_item(2, seq));
    REQUIRE_FALSE(has_item(4, seq));
}

TEST_CASE("Utility of an item is calculated correctly", "[Utility]") {
    ProfitTable pt;
    Item a = 1;
    Item b = 2;
    pt[a] = 5;
    pt[b] = 10;
    Sequence seq = {Transaction{{a, 4}, {b, 3}}, Transaction{{a, 5}}};

    REQUIRE(utility_of_item(a, seq, pt) == 25);
    REQUIRE(utility_of_item(b, seq, pt) == 30);
}

TEST_CASE("Actual sequence utility is calculated correctly for single items") {
    ProfitTable pt = {{1, 5}, {2, 10}, {3, 7}};
    Sequence seq1 = {Transaction{{1, 4}, {2, 3}}, Transaction{{1, 5}}};
    Sequence seq2 = {Transaction{{3, 1}, {2, 5}}, Transaction{{2, 1}}};
    Sequence seq3 = {Transaction{{1, 1}}};
    SDB sdb = {seq1, seq2, seq3};

    REQUIRE(actual_sequence_utility(1, sdb, pt) == 30);
    REQUIRE(actual_sequence_utility(2, sdb, pt) == 80);

}

TEST_CASE("Utility of a sequence is calculated correctly", "[Utility]") {
    ProfitTable pt;
    Item a = 1;
    Item b = 2;
    pt[a] = 5;
    pt[b] = 10;
    Sequence seq = {Transaction{{a, 4}, {b, 3}}, Transaction{{a, 5}}};
    REQUIRE(sequence_utility(seq, pt) == 75);
}

TEST_CASE("Sequence Utility Upper-Bound is calculated correctly for item", "[Utility]") {
    ProfitTable pt = {{1, 5}, {2, 10}, {3, 7}};
    Sequence seq1 = {Transaction{{1, 4}, {2, 3}}, Transaction{{1, 5}}};
    Sequence seq2 = {Transaction{{3, 1}, {2, 5}}, Transaction{{2, 1}}};
    Sequence seq3 = {Transaction{{1, 1}}};
    SDB sdb = {seq1, seq2, seq3};

    REQUIRE(sequence_utility_upper_bound(1, sdb, pt) == 80);
}

TEST_CASE("Filtering sequence works") {
    Sequence seq = {Transaction{{3, 1}, {2, 5}}, Transaction{{2, 1}}};
    Sequence filtered_seq = filter_sequence(std::set<Item>({2}), seq);
    Sequence filtered_seq2 = filter_sequence(std::set<Item>({3}), seq);
    REQUIRE(filtered_seq.begin()->size() == 1);
    REQUIRE(filtered_seq2.size() == 1);
}

TEST_CASE("Filtering SDB works") {
    Sequence seq1 = {Transaction{{1, 4}, {2, 3}}, Transaction{{1, 5}}};
    Sequence seq2 = {Transaction{{3, 1}, {2, 5}}, Transaction{{2, 1}}};
    Sequence seq3 = {Transaction{{1, 1}}};
    SDB sdb = {seq1, seq2, seq3};
    SDB filtered_sdb = filter_SDB(std::set<Item>({2, 3}), sdb);
    SDB filtered_sdb2 = filter_SDB(std::set<Item>({1, 2}), sdb, 3);
    REQUIRE(filtered_sdb.size() == 2);
    REQUIRE(filtered_sdb2.size() == 1);
}


TEST_CASE("Items in sequence are counted correctly") {
    Sequence seq = {Transaction{{1, 1}, {2, 1}}, Transaction{{1, 2}}, Transaction{{4, 1}}};
    REQUIRE(count_items(seq) == 4);
}

TEST_CASE("Prefix end position is designated properly") {
    Sequence seq = {Transaction{{1, 1}, {2, 1}}, Transaction{{3, 1}},
                    Transaction{{4, 1}}, Transaction{{2, 1}, {3, 1}}};
    Pattern prefix = {PatternElem {1, 2}, PatternElem {4}};
    Pattern prefix2 = {PatternElem {4}, PatternElem {3}};
    REQUIRE(prefix_end_position(prefix, seq)->at(4) == 1);
    REQUIRE(prefix_end_position(prefix2, seq) == seq.cend());
}

TEST_CASE("items_between from begin to end returns all items in sequence") {
    Sequence seq = {Transaction{{1, 1}, {2, 1}}, Transaction{{3, 1}},
                    Transaction{{4, 1}}, Transaction{{2, 1}, {3, 1}}};
    auto found_items = items_between(seq.begin(), seq.end());
    std::set<Item> true_items = {1, 2, 3, 4};
    REQUIRE(found_items.size() == true_items.size());
    for (Item item : true_items) {
        REQUIRE(found_items.count(item) != 0);
    }
}

TEST_CASE("items_between for one elements returns items from one element") {
    Sequence seq = {Transaction{{1, 1}, {2, 1}}, Transaction{{3, 1}},
                    Transaction{{4, 1}}, Transaction{{2, 1}, {3, 1}}};
    auto found_items = items_between(seq.begin(), ++seq.begin());
    std::set<Item> true_items = {1, 2};
    REQUIRE(found_items.size() == true_items.size());
    for (Item item : true_items) {
        REQUIRE(found_items.count(item) != 0);
    }
}