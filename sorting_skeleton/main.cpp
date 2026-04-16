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
#include <fstream>
#include <cassert>


#include "Timer.h"

// TODO: #include your City.h and Sorting.h headers here
#include "City.h"
#include "Sorting.h"

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

//----------------------------------------------------------------
// CSV parsing utility
//----------------------------------------------------------------

// helper func to parse a single CSV line cautious to quotes and stuff
std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string currentField = "";
    bool inQuotes = false;

    for (size_t i = 0; i < line.length(); ++i) {
        char c = line[i];

        if (c == '\"') {
            inQuotes = !inQuotes; // toggle into quote state
        } else if (c == ',' && !inQuotes) {
            // found comma out of quotes so we end field
            fields.push_back(currentField);
            currentField = "";
        } else {
            currentField += c; // append a char
        }
    }
    fields.push_back(currentField); // add last field
    return fields;
}



//func to load the CSV into a vector of City
std::vector<City> loadCities(const std::string& filename) {
    std::vector<City> cities;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could NOT open file " << filename << std::endl;
        return cities; // return empty when error
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        // code snipit from online tutorial
        if (line.empty() && line.back() == '\r') {
            line.pop_back(); // Remove trailing carriage return if present
        }

        std:: vector<std::string> fields = parseCSVLine(line);
        if (fields.size() < 10) continue; // safe check

        std::string city = fields[0];
        std::string country = fields[4];
        
        double lat = 0.0;
        if (!fields[2].empty()) {
            try {
                lat = std::stod(fields[2]);
            } catch (...) {lat = 0.0;}
        }

        long popu = 0;
        if (!fields[9].empty()) {
            try { popu = static_cast<long>(std::stoll(fields[9])); } 
            catch (...) {popu = 0;}
    }
        cities.emplace_back(city, country, popu, lat);
    }

    file.close();
    return cities;
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

void handleSortCommand(const std::string& algorithmName,
                       const std::string& fieldName,
                       const std::vector<City>& masterData) {
    // 1. new copy of masterData
    std::vector<City> dataCopy = masterData;

    // 2. Define comparator with lambda
    std::function<bool(const City&, const City&)> comp;

    if (fieldName == "population") {
        comp = [](const City& a, const City& b) {
            return a.getPopulation() < b.getPopulation();
        };
    } else if (fieldName == "city") {
        comp = [](const City& a, const City& b) {
            return a.getCity() < b.getCity();
        };
    } else if (fieldName == "country") {
        comp = [](const City& a, const City& b) {
            return a.getCountry() < b.getCountry();
        };
    } else if (fieldName == "latitude") {
        comp = [](const City& a, const City& b) {
            return a.getLatitude() < b.getLatitude();
        };
    } else {
        std::cerr << "Error: Invalid field name: " << fieldName << std::endl;
        return;
    }

    // 3. Sort and time with right algorithm
    Timer timer;
    timer.start();

    if (algorithmName == "insertionSort") {
        insertionSort(dataCopy, comp);
        std::cout << "Insertion Sort not implemented yet." << std::endl;
    } else if (algorithmName == "mergeSort") {
        mergeSort(dataCopy, comp);
        std::cout << "Merge Sort not implemented yet." << std::endl;
    } else {
        std::cerr << "Error: Invalid algorithm name: " << algorithmName << std::endl;
        return;
    }
    timer.stop();

    // 4. Print top 10 results
    int printCount = std::min(10, static_cast<int>(dataCopy.size()));
    for (int i = 0; i < printCount; ++i) {
        std::cout << (i + 1) << ". " << dataCopy[i] << std::endl;
    }

    // Print elapsed time
    std::cout << "Sorted with " << fieldName << " using " << algorithmName
              << " (time: " << std::fixed << std::setprecision(2)
              << timer.elapsedMilliseconds() << " ms)" << std::endl;

}

void runTests() {
    std::cout << "Running cassert Tests..." << std::endl;

    // 1. template generalityand edge cases
    std::vector<int> intVec = {5, 1, 9, 3, 5, 111};
    auto intComp = [](int a, int b) { return a < b; };

    insertionSort(intVec, intComp);
    assert(intVec == std::vector<int>({1, 3, 5, 5, 9, 111})); //correctness

    intVec = {11};
    mergeSort(intVec, intComp);
    assert(intVec == std::vector<int>({11})); // single element edge case

    intVec.clear();
    mergeSort(intVec, intComp);
    assert(intVec.empty()); // empty vector edge case

    // 2 city correctness
    std::vector<City> cities = {
        City("CityA", "CountryX", 1000, 10.0),
        City("CityB", "CountryY", 500, 20.0),
    };

    // test population descending
    mergeSort(cities, [](const City& a, const City& b) {
        return a.getPopulation() > b.getPopulation();
    });
    assert(cities[0].getCity() == "CityA" && cities[1].getCity() == "CityB");

    //test city name ascending
    insertionSort(cities, [](const City& a, const City& b) {
        return a.getCity() < b.getCity();
    });
    assert(cities[0].getCity() == "CityA" && cities[1].getCity() == "CityB");

    std::cout << "All tests passed!" << std::endl;
}

int main() {
  

    runTests(); // Run tests before starting REPL
    
    // TODO: Load the CSV dataset into a container of your choice.
    //       Example:
    //   std::vector<City> cities = loadCities("worldcities.csv");
    //   std::cout << "Loaded " << cities.size() << " cities." << std::endl;

    std::cout << "Loading dataset" << std::endl;
    
    std::vector<City> cities = loadCities("worldcities.csv");
    
    if (cities.empty()) {
        std::cerr << "Error...Failed to load dataset or dataset is empty." << std::endl;
        return 1;
    }
    std::cout << "Successfully loaded " << cities.size() << " cities.\n" << std::endl;

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
        handleSortCommand(algorithm, field, cities);


        std::cout << std::endl;
    }

    return 0;
}
