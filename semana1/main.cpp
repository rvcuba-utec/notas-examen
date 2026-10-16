#include <vector>
using namespace std;

void insertion_sort(vector<int> &arr, int n) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;
    while (arr[j] > key && j >= 0) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void bubble_sort(vector<int> &arr, int n) {
  bool swapped;
  do {
    swapped = false;
    for (int i = 1; i < n; i++) {
      for (int j = i; j < n; j++) {
        if (arr[j - 1] > arr[j]) {
          int temp = arr[j - 1];
          arr[j - 1] = arr[j];
          arr[j] = temp;
          swapped = true;
        }
      }
    }
  } while (swapped);
}

void quick_sort(vector<int> &arr, int x, int n) {
  int pivot = x;
  int storeIndex = x + 1;
  for (int i = x + 1; i <= n; i++) {
    if (arr[i] < pivot[x]) {
      int temp =
    }
  }
}
