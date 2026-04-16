PA4: World Cities Sorter

Build & Run
- Compile: `make` (Uses C++17, -Wall, -Wextra)
- Execute: `./city_sorter`
- Clean: `make clean`

Design Decisions
-Missing Data: Empty population fields default to `0` to keep the record in the dataset.
-Containers: Used `std::vector` for $O(1)$ access, optimizing sort performance.
-Templates*: Algorithms are implemented as generic templates in `Sorting.h` to support any type with a comparator.

Testing (cassert)
Verified sorting correctness using `cassert` on:
-Small hand-crafted `City` vectors.
-Edge cases: Empty and single-element vectors.
-Generality: Successfully sorted `std::vector<int>`.

## Reflection
As expected the Merge Sort (O(n log n)) significantly outperformed Insertion Sort (O(n^2)) on the 47k dataset and insertion Sort is efficient for small arrays but its performance degrades, while Merge Sort stays consistently fast.