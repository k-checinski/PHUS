//
// Created by jedikarix on 16.12.2019.
//

#include "catch.hpp"

#include "../code/Transaction.h"

TEST_CASE("Filtering transaction works") {
    Transaction trans = {{1, 5}, {2, 3}, {1, 5}};
    REQUIRE(filter_transaction(std::set<Item>({2}), trans).size() == 1);
    REQUIRE(filter_transaction(std::set<Item>({}), trans).empty());
}