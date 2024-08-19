
#include "datautil.h"
// #include <iostream>

std::vector<double> GetData() {

    const std::string dataDirectory = "data/train";
    const int numDatapoints = 101;
    
    // Randomly choose a csv file from the train folder

    std::vector<std::string> csv_files;
    for (const auto& entry : std::filesystem::directory_iterator(dataDirectory)) {
        if (entry.path().extension() == ".csv") {
            csv_files.push_back(entry.path().string());
        }
    }

    if (csv_files.empty()) {
        // TODO: Handle error here (No csv files)
        return {};
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, csv_files.size() - 1);

    std::string chosen_file = csv_files[distrib(gen)];
    // std::cout << "Chosen file: " << chosen_file << std::endl;

    // Get random 100 adjacent lines from chosen file

    std::ifstream file(chosen_file);
    std::vector<std::string> lines;
    std::string line;

    std::getline(file, line); // Skip the header line
    while (std::getline(file, line)) {
        lines.push_back(line);
    }

    if (lines.size() < numDatapoints) {
        // TODO: Handle error here (Fewer than numDatapoints lines in file)
        return {};
    }

    std::uniform_int_distribution<> distrib2(0, lines.size() - numDatapoints);
    int start_line = distrib2(gen);
    std::vector<std::string> random_lines(lines.begin() + start_line, lines.begin() + start_line + numDatapoints);

    // Extract close values from each line

    std::vector<double> close_values;
    for (const auto& line : random_lines) {
        std::stringstream ss(line);
        std::string token;
        int column = 0;

        while (std::getline(ss, token, ',')) {
            // The "Close" value is in the 5th column
            if (column == 4) {
                close_values.push_back(std::stod(token));
                break;
            }
            column++;
        }
    }

    return close_values;
}