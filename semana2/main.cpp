#include <iostream>
#include <vector>
using namespace std;

struct my_string {
  std::vector<char> cadena;

  my_string() {}

  my_string(const std::vector<char> &cad) : cadena(cad) {}

  my_string(string cad) {
    cadena.clear();
    for (auto c : cad) {
      cadena.push_back(c);
    }
  }

  char operator[](size_t n) { return cadena[n]; }

  void operator=(const string cad) {
    for (auto c : cad) {
      cadena.clear();
      cadena.push_back(c);
    }
  }

  my_string operator+(my_string &otro) {
    my_string nuevacad;
    for (char c : cadena) {
      nuevacad.cadena.push_back(c);
    }
    for (char c : otro.cadena) {
      nuevacad.cadena.push_back(c);
    }
    return nuevacad;
  }
};

ostream &operator<<(ostream &os, my_string &cad) {
  for (char c : cad.cadena) {
    os << c;
  }
  return os;
}

int main() {
  my_string cadena = "hola";
  std::cout << cadena[1] << endl;
  my_string cadena2({' ', 'p', 'e', 'p', 'e'});
  my_string cadena3 = cadena + cadena2;
  cout << cadena3 << endl;
}
