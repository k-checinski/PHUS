#ifndef PHUS_EDAMI_INDEXTABLE_H
#define PHUS_EDAMI_INDEXTABLE_H

#include "types.h"

struct IndexTableRecord {
    IndexTableRecord(unsigned _sequence_id, unsigned _first_pos)
    : sequence_id(_sequence_id)
    , first_pos(_first_pos){};
    unsigned sequence_id;
    unsigned first_pos;
};
typedef std::map<Item, std::vector<IndexTableRecord> > IndexTable;

IndexTable create_index_table(const SDB& sdb);

#endif //PHUS_EDAMI_INDEXTABLE_H
