#include "phus.h"
#include "SequenceReader.h"
#include "statistics.h"
#include <string>
#include <iostream>

#define DEFAULT_MIN_UTILITY_THRESHOLD 80

void show_usage() {

    std::cout << " ********************** PHUS algorithm *********************" << std::endl;
    std::cout
            << "Implemented program discovers high utility sequential patterns in given dataset and specified by user minimum utility threshold. \n"
               "The dataset is expected to be delivered in a file where each line contains a sequence. \n"
               "The first number is the total number of transactions in this sequence. After that, each transaction is displayed, \nfirst by the number of items in this"
               "transaction, then followed by the items in it. Each item may be followed by its cardinality in parenthesis. \n"
               "However specifying cardinalities is not obligatory - their values by default are generated randomly. Program will use \n"
               "custom cardinalities if -c flag is provided. Input file may also include information about items profit values. If after the last sequence line \n"
               "there will be a line 'PROFIT_TABLE' followed by lines in format: item item_value, user defined profit table will be used by the algorithm. \n"
               "In another case it will be randomly generated. \n \n";
    std::cout << "Expected parameters: " << std::endl;
    std::cout << "-h help" << std::endl;;
    std::cout << "-i file with input data" << std::endl;
    std::cout << "-c flag whether input file contains items cardinalities. If not specified, their values will be randomly generated" << std::endl;
    std::cout << "-t minimum utility threshold (default: 80)" << std::endl;
    std::cout << "-m maximum pattern length (default: 0 - no maximum length)" << std::endl;
    std::cout << "-n how many times algorithm should be run (default: 1)" << std::endl;
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        show_usage();
        return 1;
    }

    unsigned minimum_utility_threshold = DEFAULT_MIN_UTILITY_THRESHOLD;

    unsigned max_length = 0, repeat_number = 1;
    bool should_generate_items_count = true;
    std::string input_file;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-h") {
            show_usage();
            return 0;
        } else if (arg == "-i") {
            if (i + 1 < argc) {
                input_file = argv[++i];
            } else {
                std::cout << "input file not specified" << std::endl;
                return 1;
            }
        } else if (arg == "-t") {
            if (i + 1 < argc) {
                minimum_utility_threshold = std::stoi(argv[++i]);
            } else {
                std::cout << "minimum utility threshold not specified" << std::endl;
                return 1;
            }
        } else if (arg == "-m") {
            if (i + 1 < argc) {
                max_length = std::stoi(argv[++i]);
            } else {
                std::cout << "maximum pattern length not specified" << std::endl;
            }
        } else if (arg == "-c") {
            should_generate_items_count = false;
        } else if (arg == "-n") {
            if (i + 1 < argc) {
                repeat_number = std::stoi(argv[++i]);
            } else {
                std::cout << "repetition number not specified" << std::endl;
            }
        } else {
            std::cout << "invalid parameter " << argv[i] << std::endl;
            return 1;
        }
    }

    if (input_file.empty()) {
        std::cout << "input file not specified" << std::endl;
        return 1;
    }

    SequenceReader sequence_reader;
    std::pair<SDB, ProfitTable> dataset;

    dataset = sequence_reader.read_dataset(input_file, should_generate_items_count);

    std::cout << "Dataset" << std::endl;
    std::cout << dataset.first << std::endl;
    std::cout << "Profit table:" << std::endl;
    std::cout << dataset.second << std::endl;

    transform_dataset_with_profit_table(dataset.first, dataset.second);
    std::set<Item> items;
    for (const auto &item : dataset.second) {
        items.insert(item.first);
    }

    std::vector<DiscoveredPatternStatistics> algorithm_runs_statistics;

    unsigned total_time = 0;

    for (unsigned i = 1; i <= repeat_number; i++) {

        std::cout << "[Iteration " << i << "] \n";
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

        std::vector<std::pair<Pattern, unsigned>> found_patterns = phus(dataset.first, items, minimum_utility_threshold,
                                                                        max_length);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        unsigned run_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "RESULT\n";
        std::cout << "Algorithm found " << found_patterns.size() << " patterns:" << "\n";
        std::cout << "Algorithm took " << run_time << " [ms]:" << "\n";

        for (const auto &pat: found_patterns)
            std::cout << pat.first << "\tasu: " << pat.second << "\n";

        DiscoveredPatternStatistics statistics = get_statistics(found_patterns);
        std::cout << "Patterns minimum cardinality: " << statistics.min << "\n";
        std::cout << "Patterns average cardinality: " << statistics.average << "\n";
        std::cout << "Patterns maximum cardinality: " << statistics.max << "\n";
        std::cout << "Patterns cardinality standard deviation: " << statistics.std_dev << "\n";

        algorithm_runs_statistics.push_back(statistics);
        total_time += run_time;
    }

    show_average_from_statistics(algorithm_runs_statistics);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "[TIME] average algorithm execution time: "
              << total_time / repeat_number << "[ms]"
              << std::endl;
    return 0;
}

