#include <iostream>

using namespace std;
void quickSort(int * arr, int low, int high) {
    if (low < high) {
        // Choose the pivot as the middle element
        int mid = low + (high - low) / 2;
        int pivot = arr[mid];

        // Initialize pointers for partitioning
        int i = low;
        int j = high;

        while (i <= j) {
            // Move the left pointer to the right as long as elements are less than pivot
            while (arr[i] < pivot) {
                i++;
            }

            // Move the right pointer to the left as long as elements are greater than pivot
            while (arr[j] > pivot) {
                j--;
            }

            // If pointers have not crossed, swap elements and move pointers
            if (i <= j) {
                swap(arr[i], arr[j]);
                i++;
                j--;
            }
        }

        // Recursively apply QuickSort to the partitions
        if (low < j) {
            quickSort(arr, low, j);
        }
        if (i < high) {
            quickSort(arr, i, high);
        }
    }
}


void mergeSortSingle(int * arr, int left, int right) {
    if (left >= right) {
        // Base case: If the array has one or no elements, it's already sorted
        return;
    }

    // Find the middle point to divide the array into two halves
    int mid = left + (right - left) / 2;

    // Recursively sort the first and second halves
    mergeSortSingle(arr, left, mid);
    mergeSortSingle(arr, mid + 1, right);

    // Merge the sorted halves
    // Create temporary vectors for left and right subarrays
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int * L = new int[n1];
    int * R = new int[n2];

    // Copy data to temporary vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary vectors back into arr[left..right]
    int i = 0;    // Initial index of first subarray
    int j = 0;    // Initial index of second subarray
    int k = left; // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }

    // Copy any remaining elements of L[], if any
    while (i < n1) {
        arr[k++] = L[i++];
    }

    // Copy any remaining elements of R[], if any
    while (j < n2) {
        arr[k++] = R[j++];
    }
}


int main() {
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, n - 1);

    cout << "Sorted array: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
