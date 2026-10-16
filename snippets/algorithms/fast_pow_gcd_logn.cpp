// ============================================================
// Exponenciación rápida (Fast Power) + Aritmética modular
// ============================================================
// Complejidad: O(log n) tiempo, O(1) espacio
//
// Uso: Calcular a^n mod m de forma eficiente.
//      Fundamental en competitive programming.
//
// Aplicaciones:
//   - Exponenciación modular (criptografía, combinatoria)
//   - Inverso modular (a^(m-2) mod m, cuando m es primo)
//   - Combinaciones nCr mod p
//   - GCD, LCM, GCD extendido
// ============================================================

#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1e9 + 7; // Módulo típico en Codeforces

// -----------------------------------------------
// Fast Power (exponenciación binaria)
// -----------------------------------------------
long long fast_pow(long long base, long long exp, long long mod = MOD) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = result * base % mod;
        base = base * base % mod;
        exp >>= 1;
    }
    return result;
}

// -----------------------------------------------
// Inverso modular (cuando mod es primo)
// -----------------------------------------------
// Por el pequeño teorema de Fermat: a^(-1) ≡ a^(p-2) (mod p)
long long mod_inverse(long long a, long long mod = MOD) {
    return fast_pow(a, mod - 2, mod);
}

// -----------------------------------------------
// Combinaciones nCr mod p (con precálculo de factoriales)
// -----------------------------------------------
const int MAXN = 200005;
vector<long long> fact(MAXN), inv_fact(MAXN);

void precompute_factorials(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
    inv_fact[n] = mod_inverse(fact[n]);
    for (int i = n - 1; i >= 0; --i) inv_fact[i] = inv_fact[i + 1] * (i + 1) % MOD;
}

long long nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] % MOD * inv_fact[r] % MOD * inv_fact[n - r] % MOD;
}

// -----------------------------------------------
// GCD y LCM
// -----------------------------------------------
long long gcd(long long a, long long b) {
    return b ? gcd(b, a % b) : a;
    // Alternativa STL: __gcd(a, b) o std::gcd(a, b) en C++17
}

long long lcm(long long a, long long b) {
    return a / gcd(a, b) * b; // Dividir primero para evitar overflow
}

// -----------------------------------------------
// GCD Extendido: encuentra x, y tal que a*x + b*y = gcd(a,b)
// -----------------------------------------------
long long ext_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    long long x1, y1;
    long long g = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

int main() {
    cout << "2^10 mod 1e9+7 = " << fast_pow(2, 10) << '\n';
    cout << "2^64 mod 1e9+7 = " << fast_pow(2, 64) << '\n';
    cout << "Inverse of 2 mod 1e9+7 = " << mod_inverse(2) << '\n';

    precompute_factorials(200000);
    cout << "C(10, 3) = " << nCr(10, 3) << '\n';
    cout << "C(100, 50) mod 1e9+7 = " << nCr(100, 50) << '\n';

    cout << "GCD(12, 18) = " << gcd(12, 18) << '\n';
    cout << "LCM(12, 18) = " << lcm(12, 18) << '\n';

    return 0;
}
