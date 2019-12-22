#include "catch.hpp"

#include "../code/finding_hus.h"

TEST_CASE("r+1 patterns with prefix: items are added properly at last prefix element") {
    Sequence seq = {Transaction{{1, 3}, {2, 4}},
                    Transaction{{3, 1}},
                    Transaction{{1, 2}},
                    Transaction{{3, 4}, {4, 3}, {2, 1}}};
    Pattern pat = {PatternElem{1},
                   PatternElem{1},
                   PatternElem{4}};
    auto patterns = generate_prefix_patterns(seq, pat);
    REQUIRE(patterns.size() == 2);
}

TEST_CASE("r+1 patterns with prefix: items are added properly behind prefix") {
    Sequence seq = {Transaction{{1, 3}, {2, 4}},
                    Transaction{{3, 1}},
                    Transaction{{1, 2}},
                    Transaction{{3, 4}, {4, 3}, {2, 1}},
                    Transaction{{1, 4}},
                    Transaction{{4, 1}, {5, 2}}};
    Pattern pat = {PatternElem{1},
                   PatternElem{1},
                   PatternElem{4}};
    auto patterns = generate_prefix_patterns(seq, pat);
    REQUIRE(patterns.size() == 6);
}

TEST_CASE("find_hus works for example from paper") {
    ProfitTable profit_table = {{1, 3}, {2, 10}, {3, 1}, {4, 6}, {5, 5}, {6, 2}};
    Sequence proj_seq1 = {Transaction{{1, 1}}, Transaction{{1, 2}},
                          Transaction {{5, 1}}, Transaction{{6, 2}}};
    Sequence proj_seq2 = {Transaction{{1, 1}}, Transaction{{2, 1}, {3, 15}},
                          Transaction{{3, 3}}};
    Sequence proj_seq3 = {Transaction{{1, 3}}, Transaction {{1, 2}, {3, 8}},
                          Transaction {{5, 2}}};
    Sequence proj_seq4 = {Transaction{{1, 3}, {2, 2}}, Transaction{{3, 2}},
                          Transaction{{5, 2}}, Transaction{{6, 3}}};
    Sequence proj_seq5 = {Transaction{{1, 3}}, Transaction{{6, 1}}};
    Sequence proj_seq6 = {Transaction{{1, 2}}, Transaction{{3, 4}},
                          Transaction{{5, 2}}};
    SDB sdb = {proj_seq1, proj_seq2, proj_seq3, proj_seq4, proj_seq5, proj_seq6};
    unsigned threshold = 65;
    unsigned r = 1;
    Pattern prefix = {PatternElem {1}};
    find_hus(prefix, sdb, r, profit_table, threshold);
}