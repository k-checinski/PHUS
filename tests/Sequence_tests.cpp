#include "catch.hpp"

#include "../code/Sequence.h"

TEST_CASE()

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
