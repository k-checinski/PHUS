#include <iostream>
#include "SequenceReader.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    SequenceReader sequenceReader;
    sequenceReader.read_dataset("../tests/data/sample.data");
    return 0;
}
