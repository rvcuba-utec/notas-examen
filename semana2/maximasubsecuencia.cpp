#include <iostream>
using namespace std;

int main() {
  int n;
  int cont = 0;
  string cad;
  cin >> n;
  cin >> cad;
  char ant = '\0';
  for (char &c : cad) {
    if (c != ant) {
      cont += 1;
    }
    ant = c;
  }
  cout << cont;
}
