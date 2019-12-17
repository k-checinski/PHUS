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

TEST_CASE("Determining partitioning of transaction works") {
    Transaction a = {{1, 2}, {4, 1}, {5, 1}};
    Transaction b = {{1, 1}, {5, 1}};
    Transaction c = {{1, 1}, {3, 1}, {4, 1}};
    REQUIRE(is_partition(b, a));
    REQUIRE_FALSE(is_partition(c, a));
}