#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

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

void quicksort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quicksort(arr, left, pivot - 1);
        quicksort(arr, pivot + 1, right);
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
    int size = 100000000;
    vector<int> arr = generate_random_array(size);
    vector<int> arr_copy = arr;

    auto start = chrono::high_resolution_clock::now();
    quicksort(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    cout << "Sequential Quicksort time: " << elapsed.count() << "s\n";

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