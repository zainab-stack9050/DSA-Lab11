#include <iostream>
using namespace std;

bool showTrace = true;       
long long comparisons = 0;   //counts arr[j] <= pivot comparisons
int  totalSize = 0;          //size of full array

void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]"; }

void swapInts(int& a, int& b) {
    int t = a;
    a = b;
    b = t; }

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;                 //end of the "<= pivot" region

    for (int j = low; j < high; j++) {
        comparisons++;               
        if (arr[j] <= pivot) {
            i++;
            swapInts(arr[i], arr[j]);
        }
    }
    swapInts(arr[i + 1], arr[high]); // place pivot between the two regions
    int pi = i + 1;

    if (showTrace) {
        cout << "  partition [" << low << ".." << high << "] pivot = " << pivot
             << ", pi = " << pi << " -> ";
        printArray(arr, totalSize);
        cout << endl;
    }
    return pi;
}

// Recursive quick sort on arr[low..high]
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);   // left of pivot
        quickSort(arr, pi + 1, high);  // right of pivot (pi excluded from both)
    }
}

void runTest(const char* title, int arr[], int n, bool trace) {
    cout << "\n=== " << title << " ===" << endl;
    cout << "Before: "; printArray(arr, n); cout << endl;

    showTrace = trace;
    totalSize = n;
    comparisons = 0;
    quickSort(arr, 0, n - 1);

    cout << "After : "; printArray(arr, n); cout << endl;
    cout << "Total comparisons: " << comparisons << endl;
}

int main() {
    int t1[] = {2, 1, 5, 4, 6, 3};
    int t2[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Trace: {2,1,5,4,6,3}", t1, 6, true);
    runTest("Trace: {35,12,43,8,51,27,19}", t2, 7, true);

    //Comparison for diff inputs
    int random_[]   = {5, 1, 4, 2, 8};
    int sorted[]    = {1, 2, 4, 5, 8};
    int reversed[]  = {8, 5, 4, 2, 1};
    int same[]      = {7, 7, 7, 7, 7};
    int single[]    = {9};

    runTest("Random order",     random_,  5, true);
    runTest("Already sorted (worst case for last pivot)", sorted, 5, true);
    runTest("Reverse sorted",   reversed, 5, true);
    runTest("Repeated values {7,7,7,7,7}", same, 5, true);
    runTest("Single element (n = 1)", single, 1, true);

    // Empty array (n = 0)
    int* empty = nullptr;
    cout << "\n=== Empty array (n = 0) ===" << endl;
    comparisons = 0;
    quickSort(empty, 0, -1);
    cout << "Total comparisons: " << comparisons << endl;

    return 0;
}