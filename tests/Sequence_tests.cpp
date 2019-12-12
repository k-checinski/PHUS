#include "catch.hpp"

#include "../code/Sequence.h"

TEST_CASE("Occurence of item in sequence is checked correctly") {
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