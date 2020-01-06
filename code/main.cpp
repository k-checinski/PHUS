#include "phus.h"
#include "SequenceReader.h"
#include <fstream>
#include <string>
#include <iostream>

#define DEFAULT_MIN_UTILITY_THRESHOLD 80
#define DEFAULT_OUTPUT_FILE "out.txt"

std::basic_ofstream<char> redirect_output_to_file(const std::string &file_name) {
    std::ofstream out(file_name);
    std::cout.rdbuf(out.rdbuf());
    return out;
}

void extract_time_and_algorithm_info(const std::string &file_name) {
    std::ifstream file;
    file.open(file_name);
    std::string output_file;
    if (file_name.find('.') != std::string::npos) {
        output_file = file_name.substr(0, file_name.find('.'));
    } else {
        output_file = file_name;
    }

    std::ofstream time_file;
    time_file.open(output_file + "_time.txt");
    std::ofstream algorithm_file;
    algorithm_file.open(output_file + "_algorithm.txt");

    std::string line;
    while (getline(file, line)) {
        if (line.rfind("[TIME]", 0) == 0) {
            time_file << line << std::endl;
        } else {
            algorithm_file << line << std::endl;
        }
    }

    file.close();
    time_file.close();
    algorithm_file.close();
}


void show_usage() {

    std::cout << " ********************** PHUS algorithm *********************" << std::endl;
    std::cout
            << "Implemented program discovers high utility sequential patterns in given dataset and specified by user minimum utility threshold. \n"
               "The dataset is expected to be delivered in a file where each line contains a sequence. \n"
               "The first number is the total number of itemsets in this sequence. After that, each itemset is displayed, \nfirst by the number of items in this"
               "itemset, then followed by the items in that itemset. Cardinality of items is randomly distributed, so is the profit table. \n \n";
    std::cout << "Expected parameters: " << std::endl;
    std::cout << "-h help" << std::endl;;
    std::cout << "-i file with input data" << std::endl;
    std::cout << "-o output file" << std::endl;
    std::cout << "-t minimum utility threshold" << std::endl;
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        show_usage();
        return 1;
    }

    unsigned minimum_utility_threshold = DEFAULT_MIN_UTILITY_THRESHOLD;
    std::string input_file, output_file = DEFAULT_OUTPUT_FILE;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            show_usage();
        } else if (arg == "-i") {
            if (i + 1 < argc) {
                input_file = argv[++i];
            } else {
                std::cout << "input file not specified" << std::endl;
                return 1;
            }
        } else if (arg == "-o") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            } else {
                std::cout << "output file not specified" << std::endl;
                return 1;
            }
        } else if (arg == "-t") {
            if (i + 1 < argc) {
                minimum_utility_threshold = std::stoi(argv[++i]);
            } else {
                std::cout << "minimum utility threshold not specified" << std::endl;
                return 1;
            }
        } else {
            std::cout << "invalid parameter " << argv[i] << std::endl;
            return 1;
        }
    }

    if (input_file.empty()){
        std::cout << "input file not specified" << std::endl;
        return 1;
    }

    auto out = redirect_output_to_file(output_file);

    SequenceReader sequence_reader;
    std::pair<SDB, ProfitTable> dataset = sequence_reader.prepare_data_for_sequence_mining(input_file);
    std::vector<Pattern> found_patterns = phus(dataset.first, dataset.second, minimum_utility_threshold);
    std::cout << "RESULT\n";
    for (const auto &pat: found_patterns)
        std::cout << pat << "\n";

    out.close();
    extract_time_and_algorithm_info(output_file);
    return 0;
}

