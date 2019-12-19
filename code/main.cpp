#include <iostream>
#include "SequenceReader.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SequenceReader sequenceReader;
    auto result = sequenceReader.prepare_data_for_sequence_mining("../tests/data/sample.data");

    return 0;
}
