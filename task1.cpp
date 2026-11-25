#include <iostream>
using namespace std;

bool showTrace = true;  
int  mergeCalls = 0;     //number of merge() calls

//printing the whole array
void printArray(const int arr[], int n) {
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << arr[i];
        if (i < n - 1) cout << ", ";
    }
    cout << "]";
}

int totalSize = 0;       //size of the full array

//merging two adjacent sorted subarrays arr[low..mid] and arr[mid+1..high]
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;      //size of left half
    int n2 = high - mid;         //size of right half

    int* L = new int[n1];        //temp arrays
    int* R = new int[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else              arr[k++] = R[j++];
    }
    // Copy leftovers
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;                  //memory clearance
    delete[] R;

    mergeCalls++;
    if (showTrace) {
        cout << "  merge [" << low << ".." << high << "] -> ";
        printArray(arr, totalSize);
        cout << endl;
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low >= high) return;               

    int mid = low + (high - low) / 2;      
    mergeSort(arr, low, mid);              
    mergeSort(arr, mid + 1, high);         
    merge(arr, low, mid, high);            
}

void runTest(const char* title, int arr[], int n, bool trace) {
    cout << "\n=== " << title << " ===" << endl;
    cout << "Before: "; printArray(arr, n); cout << endl;

    showTrace = trace;
    totalSize = n;
    mergeCalls = 0;
    mergeSort(arr, 0, n - 1);

    cout << "After : "; printArray(arr, n); cout << endl;
    cout << "merge() calls: " << mergeCalls << endl;
}

int main() {
    // Main trace test
    int a[] = {35, 12, 43, 8, 51, 27, 19};
    runTest("Trace: {35,12,43,8,51,27,19}", a, 7, true);

    // Boundary cases
    int sorted[]   = {1, 2, 4, 5, 8};
    int reversed[] = {8, 5, 4, 2, 1};
    int dups[]     = {5, 2, 5, 1, 2};
    int single[]   = {42};

    runTest("Already sorted",  sorted,   5, true);
    runTest("Reverse sorted",  reversed, 5, true);
    runTest("Repeated values", dups,     5, true);
    runTest("Single element (n = 1)", single, 1, true);

    // Empty array (n = 0): mergeSort(arr, 0, -1) hits base case immediately
    int* empty = nullptr;
    cout << "\n=== Empty array (n = 0) ===" << endl;
    mergeSort(empty, 0, -1);
    cout << "Handled without error (nothing to sort)." << endl;

    return 0;
}