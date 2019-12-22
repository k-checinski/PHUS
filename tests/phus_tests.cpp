#include "catch.hpp"

#include "../code/phus.h"

TEST_CASE("PHUS works") {
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
    Pattern prefix = {PatternElem {1}};
    std::vector<Pattern> found_patterns = phus(sdb, profit_table, threshold);
    std::cout<<"RESULT\n";
    for (const auto& pat: found_patterns)
        std::cout<<pat<<"\n";
    REQUIRE(found_patterns.size() == 2);
    REQUIRE(found_patterns[0] == Pattern{{1}, {5}});
    REQUIRE(found_patterns[1] == Pattern{{1}, {3}, {5}});
}

