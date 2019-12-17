#include "IndexTable.h"

IndexTable create_index_table(const SDB &sdb, const std::set<Item>& items) {
    IndexTable table;
    std::set<Item> current_seq;
    unsigned seq_id = 0;
    for (const Sequence& sequence : sdb) {
        unsigned seq_pos = 0;
        for (const Transaction& transaction : sequence) {
            for (const auto& elem : transaction) {
                if (current_seq.count(elem.first) == 0 && items.count(elem.first) != 0) {
                    current_seq.insert(elem.first);
                    table[elem.first].push_back(IndexTableRecord(seq_id, seq_pos));
                }
            }
            ++seq_pos;
            current_seq.clear();
        }
        ++seq_id;
    }
    return table;
}
