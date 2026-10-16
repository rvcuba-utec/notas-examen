#include <iostream>
using namespace ::std;

int main() {
  cin.tie(0)->sync_with_stdio(false);

  // arreglo estático
  int A[10];

  // forma dinámica
  int *a = (int *)malloc(10 * sizeof(int));
  int *b = new int[10];
  // toda memoria dinámica debe ser liberada antes de finalizar

  int n;
  cin >> n;
  int B[n];

  free(a);    // c-like
  delete[] b; // moderno

  return 0;
}
