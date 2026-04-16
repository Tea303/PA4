#ifndef SORTING_H
#define SORTING_H

#include <vector>

//------------------------------------------------------------------
// insertion sort
//-------------------------------------------------------------------

template <typename T, typename Comparator>
void insertionSort(std::vector<T>& data, Comparator comp) {
    for (size_t i = 1; i < data.size(); ++i) {
        T key = data[i];
        int j = i - 1;

        // move elements that's greater than key to one position ahead
        // until the correct position for key is found
        while (j >= 0 && comp(key, data[j])) {
            data[j + 1] = data[j];
            --j;
        }
        data[j + 1] = key;
    }
}

//------------------------------------------------------------------
// merge sort
//-------------------------------------------------------------------

template <typename T, typename Comparator>
void merge(std::vector<T>& data, int left, int mid, int right, Comparator comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // temp vectors
    std::vector<T> lData(n1);
    std::vector<T> rData(n2);

    // copy data to temp vectors
    for (int i = 0; i < n1; ++i) {
        lData[i] = data[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        rData[j] = data[mid + 1 + j];
    }

    // merge temp vectors back into data
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comp(lData[i], rData[j])) {
            data[k] = lData[i];
            ++i;
        } else {
            data[k] = rData[j];
            ++j;
        }
        ++k;
    }

    // copy remaining elements of lData
    while (i < n1) {
        data[k] = lData[i];
        ++i;
        ++k;
    }  

    // copy remaining elements of rData
    while (j < n2) {
        data[k] = rData[j];
        ++j;
        ++k;
    }
}

template <typename T, typename Comparator>
void mergeSortHelper(std::vector<T>& data, int left, int right, Comparator comp) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;

    // sort first and second halves
    mergeSortHelper(data, left, mid, comp);
    mergeSortHelper(data, mid + 1, right, comp);

    // merge sorted halves
    merge(data, left, mid, right, comp);
}

template <typename T, typename Comparator>
void mergeSort(std::vector<T>& data, Comparator comp) {
    mergeSortHelper(data, 0, data.size() - 1, comp);
}


#endif