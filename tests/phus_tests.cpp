#include "catch.hpp"

#include "../code/phus.h"

TEST_CASE("PHUS works") {
    ProfitTable profit_table = {{1, 3}, {2, 10}, {3, 1}, {4, 6}, {5, 5}, {6, 2}};
    Sequence seq1 = {{{1, 1}}, {{1, 2}, {4, 1}}, {{5, 1}}, {{6, 2}}};
    Sequence seq2 = {{{1, 1}}, {{2, 1}, {3, 15}}, {{3, 3}}};
    Sequence seq3 = {{{5, 3}}, {{3, 2}}, {{5, 1}}};
    Sequence seq4 = {{{2, 2}, {3, 9}}, {{3, 5}}};
    Sequence seq5 = {{{1, 3}}, {{1, 2}, {3, 8}}, {{5, 2}}};
    Sequence seq6 = {{{3, 7}}, {{2, 1}}, {{6, 3}}};
    Sequence seq7 = {{{3, 7}}, {{4, 1}}};
    Sequence seq8 = {{{1, 3}, {2, 2}}, {{3, 2}}, {{5, 2}}, {{6, 3}}};
    Sequence seq9 = {{{1, 3}}, {{4, 1}}, {{6, 1}}};
    Sequence seq10 = {{{1, 2}}, {{3, 4}}, {{5, 2}}};
    SDB sdb = {seq1, seq2, seq3, seq4, seq5, seq6, seq7, seq8, seq9, seq10};
    transform_dataset_with_profit_table(sdb, profit_table);
    std::set<Item> items;
    for (const auto& item : profit_table) {
        items.insert(item.first);
    }
    unsigned threshold = 65;
    std::vector<std::pair<Pattern, unsigned>> found_patterns = phus(sdb, items, threshold, 0);
    std::cout<<"RESULT\n";
    for (const auto& pat: found_patterns)
        std::cout<<pat.first<<"\tasu: "<<pat.second<<"\n";
    REQUIRE(found_patterns.size() == 2);
    REQUIRE(found_patterns[0].first == Pattern{{1}, {5}});
    REQUIRE(found_patterns[1].first == Pattern{{1}, {3}, {5}});
}

