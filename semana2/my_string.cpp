#include <cstring>
#include <iostream>
#include <ostream>
class my_string {
  char *m_str = nullptr;
  int n_size = 0;

public:
  my_string(const char *str = nullptr) {
    if (!str)
      return;

    while (str[++n_size - 1])
      ;

    m_str = new char[n_size];
    std::memcpy(m_str, str, sizeof(char) * n_size);
  }
  int size() { return n_size - 1; }

  char *begin() { return m_str; }
  char *end() { return m_str + n_size - 1; }
  operator char *() { return m_str; }
  char &operator[](int i) { return m_str[i]; }

  friend std::ostream &operator<<(std::ostream &os, const my_string &str) {
    return os << str.m_str;
  }
};

int main() {
  my_string saludo("Hola, mundo!");
  std::cout << "Texto original: " << saludo << "\n";

  std::cout << "Tamaño: " << saludo.size() << " caracteres\n";

  saludo[0] = 'h';
  std::cout << "Texto modificado: " << saludo << "\n";

  std::cout << "Iterando letra por letra: ";
  for (char c : saludo) {
    std::cout << c << " ";
  }
  std::cout << "\n";

  char *c_str = saludo;
  std::cout << "Como puntero char*: " << c_str << "\n";

  return 0;
}
