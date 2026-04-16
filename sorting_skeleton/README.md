# CPTS 223 - Programming Assignment 4: Sorting World Cities

## Build Instructions
To compile and run the program on a Linux/Unix environment:
1. Ensure you have `g++` and `make` installed.
2. Open a terminal in the project directory.
3. Run the command: `make`
4. Execute the program: `./main`
5. To clean up compiled object files and the executable, run: `make clean`

## Design Decisions
* **Container Choice:** `std::vector<City>` was used to store the records. Vectors provide contiguous memory allocation, which is cache-friendly and ideal for sorting algorithms like Merge Sort and Insertion Sort that rely heavily on indexing.
* **Handling Missing Data:** The SimpleMaps dataset contains missing population fields for some cities. I chose to handle this by implementing a `try-catch` block during the CSV parsing process. If the `stod` or `stoll` parsing fails (due to an empty string), the population defaults to `0`. 
* **CSV Parsing:** Since city names or locations can contain commas within quotation marks, a standard `getline` with a comma delimiter is insufficient. I implemented a state-machine parser (`parseCSVLine`) that tracks whether the current character is inside or outside of quotes, ensuring fields are split correctly.
* **Sorting Generality:** Both `insertionSort` and `mergeSort` are implemented as function templates in `Sorting.h` that accept a `std::vector<T>` and a lambda comparator function, ensuring they work on integers, strings, or custom objects like `City`.

## Testing
I implemented a `runTests()` function in `main.cpp` utilizing `<cassert>` to verify the stability and correctness of the algorithms before the REPL begins.
1. **Template Generality & Edge Cases:** Tested `insertionSort` and `mergeSort` on a `std::vector<int>`. I verified that the algorithms do not crash on an empty vector, function correctly on a single-element vector, and correctly reorder a reverse-sorted vector.
2. **Sorting Correctness:** Created a small vector of `City` objects (Tokyo, Seattle, Pullman) and tested sorting by population (descending) and city name (ascending). The asserts explicitly verify that the city names end up at the exact expected indices after the sort finishes.

## Performance Analysis
*Note: Times were recorded in milliseconds (ms).*

| Field | Insertion Sort (ms) | Merge Sort (ms) |
| :--- | :--- | :--- |
| population | [FILL THIS IN] | [FILL THIS IN] |
| city | [FILL THIS IN] | [FILL THIS IN] |
| country | [FILL THIS IN] | [FILL THIS IN] |
| latitude | [FILL THIS IN] | [FILL THIS IN] |

## Reflection
*(Write a minimum of 1 paragraph here. Discuss what you observed when running the timer. Insertion Sort is O(n^2) and Merge Sort is O(n log n)—did the ms timings reflect this massive difference for ~47,000 records? Did sorting by a `string` like 'city' take longer than sorting by a `double` like 'latitude' because string comparisons are more expensive?)*