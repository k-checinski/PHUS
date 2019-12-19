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
