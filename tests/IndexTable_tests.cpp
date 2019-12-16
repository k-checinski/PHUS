#include "catch.hpp"

#include "../code/IndexTable.h"

TEST_CASE("IndexTable is created properly") {
    Sequence seq1 = {Transaction{{3, 1}}, Transaction{{2, 1}, {1, 1}}};
    Sequence seq2 = {Transaction{{3, 2}, {4, 1}}};
    SDB sdb = {seq1, seq2};
    IndexTable index_table = create_index_table(sdb);

    REQUIRE(index_table.size() == 4);
    REQUIRE(index_table[1][0].first_pos == 1);
    REQUIRE(index_table[1][0].sequence_id == 0);
    REQUIRE(index_table[3][0].first_pos == 0);
    REQUIRE(index_table[3][0].sequence_id == 0);
    REQUIRE(index_table[4][0].first_pos == 0);
    REQUIRE(index_table[4][0].sequence_id == 1);
}