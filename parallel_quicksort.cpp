#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

const int MAX_DEPTH = 3; // Limits parallel recursion depth

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[right]);
    return i + 1;
}

void parallel_quicksort(vector<int>& arr, int left, int right, int depth = 0) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        if (depth < MAX_DEPTH) {
            thread left_thread(parallel_quicksort, ref(arr), left, pivot - 1, depth + 1);
            parallel_quicksort(arr, pivot + 1, right, depth + 1);
            left_thread.join();
        } else {
            // Sequential processing below MAX_DEPTH (no new threads)
            parallel_quicksort(arr, left, pivot - 1, depth + 1);
            parallel_quicksort(arr, pivot + 1, right, depth + 1);
        }
    }
}

vector<int> generate_random_array(int size) {
    vector<int> arr(size);
    srand(time(0));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int main() {
    int size = 1000000;
    vector<int> arr = generate_random_array(size);
    vector<int> arr_copy = arr;

    // Parallel
    auto start = chrono::high_resolution_clock::now();
    parallel_quicksort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Parallel Quicksort time: " << elapsed.count() << "s\n";

    bool sorted = true;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i-1]) {
            sorted = false;
            break;
        }
    }
    cout << "Sorted correctly: " << (sorted ? "Yes" : "No") << endl;

    return 0;
}