// main.cpp -- Starter code for CPTS 223 Sorting Assignment
//
// This file provides:
//   - A working REPL (Read-Eval-Print Loop) with command parsing
//   - Timer usage example for measuring sort performance
//
// Your job:
//   - Create City.h / City.cpp (your City class)
//   - Create Sorting.h (your templated insertionSort and mergeSort)
//   - Fill in the TODO sections below to wire everything together
//

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <functional>
#include <iomanip>

#include "Timer.h"

// TODO: #include your City.h and Sorting.h headers here


// ----------------------------------------------------------------
// Timer usage example (delete this function once you understand it)
// ----------------------------------------------------------------
void timerExample() {
    Timer timer;

    timer.start();
    // ... do some work ...
    long sum = 0;
    for (long i = 0; i < 1000000; ++i) {
        sum += i;
    }
    timer.stop();

    std::cout << "Example elapsed time: "
              << std::fixed << std::setprecision(2)
              << timer.elapsedMilliseconds() << " ms" << std::endl;
    std::cout << "(sum = " << sum << ")" << std::endl;
}

// ----------------------------------------------------------------
// TODO: Implement handleSortCommand
// ----------------------------------------------------------------
// This function should:
//   1. Validate the field name and build the appropriate comparator
//   2. Make a fresh copy of masterData (so sorts don't affect each other)
//   3. Call the right sorting algorithm (insertionSort or mergeSort)
//      wrapped in timer.start() / timer.stop()
//   4. Print the top 10 results and the elapsed time
//
// Hint: Use std::function<bool(const City&, const City&)> for your
//       comparator, or pass lambdas directly to your sort templates.
//
// void handleSortCommand(const std::string& algorithmName,
//                        const std::string& fieldName,
//                        const std::vector<City>& masterData) {
//     // Your code here
// }


int main() {
    // Show timer example (you can remove this later)
    timerExample();
    std::cout << std::endl;

    // TODO: Load the CSV dataset into a container of your choice.
    //       Example:
    //   std::vector<City> cities = loadCities("worldcities.csv");
    //   std::cout << "Loaded " << cities.size() << " cities." << std::endl;

    // ---- REPL: Do not modify below this line ----

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break; // EOF
        }

        // Trim leading whitespace
        size_t start = line.find_first_not_of(" \t");
        if (start == std::string::npos) continue;
        line = line.substr(start);

        if (line == "quit" || line == "exit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }

        // Parse command: <algorithm> <field>
        std::istringstream iss(line);
        std::string algorithm, field;
        iss >> algorithm >> field;

        if (algorithm.empty() || field.empty()) {
            std::cout << "Usage: <algorithm> <field>" << std::endl;
            std::cout << "  Algorithms: insertionSort, mergeSort" << std::endl;
            std::cout << "  Fields: population, city, country, latitude"
                      << std::endl;
            std::cout << "  Or type 'quit' to exit." << std::endl;
            continue;
        }

        // Validate algorithm name
        if (algorithm != "insertionSort" && algorithm != "mergeSort") {
            std::cout << "Unknown algorithm: " << algorithm << std::endl;
            std::cout << "Valid algorithms: insertionSort, mergeSort"
                      << std::endl;
            continue;
        }

        // Validate field name
        if (field != "population" && field != "city" &&
            field != "country" && field != "latitude") {
            std::cout << "Unknown field: " << field << std::endl;
            std::cout << "Valid fields: population, city, country, latitude"
                      << std::endl;
            continue;
        }

        // TODO: Call your handleSortCommand function here.
        //   handleSortCommand(algorithm, field, cities);

        std::cout << std::endl;
    }

    return 0;
}
