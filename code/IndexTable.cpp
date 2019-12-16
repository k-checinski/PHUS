#include "IndexTable.h"

IndexTable create_index_table(const SDB &sdb) {
    IndexTable table;
    unsigned seq_id = 0;
    for (const Sequence& sequence : sdb) {
        unsigned seq_pos = 0;
        for (const Transaction& transaction : sequence) {
            for (const auto& elem : transaction) {
                if (table.count(elem.first) == 0)
                    table[elem.first].push_back(IndexTableRecord(seq_id, seq_pos));
            }
            ++seq_pos;
        }
        ++seq_id;
    }
    return table;
}
