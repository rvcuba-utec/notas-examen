#include <bits/stdc++.h>
using namespace std;

long long evaluar(long long &ind, vector<string> &exp) {
  if (exp[ind] == "*") {
    ind++;
    long long res1;
    res1 = evaluar(ind, exp);
    long long res2;
    res2 = evaluar(ind, exp);
    return res1 * res2;
  } else if (exp[ind] == "+") {
    ind++;
    long long res1;
    res1 = evaluar(ind, exp);
    long long res2;
    res2 = evaluar(ind, exp);
    return res1 + res2;
  } else if (exp[ind] == "-") {
    ind++;
    long long res1;
    res1 = evaluar(ind, exp);
    long long res2;
    res2 = evaluar(ind, exp);
    return res1 - res2;
  } else {
    ind++;
    return stoi(exp[ind - 1]);
  }
}

int main() {
  long long n;
  cin >> n;
  vector<string> exp(n);
  for (long long i = 0; i < n; i++) {
    cin >> exp[i];
  }
  long long i = 0;
  long long res = evaluar(i, exp);
  cout << res;
}
