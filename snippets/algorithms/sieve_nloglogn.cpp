// ============================================================
// Criba de Eratóstenes (Sieve of Eratosthenes)
// ============================================================
// Complejidad: O(n log log n) tiempo, O(n) espacio
//
// Uso: Precalcular todos los primos hasta n.
//
// Aplicaciones:
//   - Verificar primalidad en O(1) después del precálculo
//   - Factorización rápida con "smallest prime factor"
//   - Contar primos en un rango
//   - Función de Euler (totient) con criba
// ============================================================

#include <bits/stdc++.h>
using namespace std;

// -----------------------------------------------
// Criba básica
// -----------------------------------------------
vector<bool> is_prime;
vector<int> primes;

void sieve(int n) {
    is_prime.assign(n + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; (long long)i * i <= n; ++i) {
        if (is_prime[i]) {
            for (int j = i * i; j <= n; j += i) {
                is_prime[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (is_prime[i]) primes.push_back(i);
    }
}

// -----------------------------------------------
// Criba lineal (O(n)) con menor factor primo (SPF)
// -----------------------------------------------
vector<int> spf; // Smallest Prime Factor

void linear_sieve(int n) {
    spf.assign(n + 1, 0);
    primes.clear();

    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            primes.push_back(i);
        }
        for (int j = 0; j < (int)primes.size() && primes[j] <= spf[i] && (long long)i * primes[j] <= n; ++j) {
            spf[i * primes[j]] = primes[j];
        }
    }
}

// Factorización en O(log n) usando SPF
vector<pair<int, int>> factorize(int n) {
    vector<pair<int, int>> factors;
    while (n > 1) {
        int p = spf[n], cnt = 0;
        while (n % p == 0) { n /= p; cnt++; }
        factors.push_back({p, cnt});
    }
    return factors;
}

// -----------------------------------------------
// Función de Euler (Totient) con criba
// -----------------------------------------------
vector<int> phi;

void euler_totient_sieve(int n) {
    phi.resize(n + 1);
    iota(phi.begin(), phi.end(), 0); // phi[i] = i
    for (int i = 2; i <= n; ++i) {
        if (phi[i] == i) { // i es primo
            for (int j = i; j <= n; j += i) {
                phi[j] -= phi[j] / i;
            }
        }
    }
}

int main() {
    sieve(100);
    cout << "Primes up to 100: ";
    for (int p : primes) cout << p << " ";
    cout << '\n';

    linear_sieve(1000000);
    auto factors = factorize(360);
    cout << "360 = ";
    for (auto [p, e] : factors) {
        cout << p << "^" << e << " ";
    }
    cout << '\n'; // 2^3 3^2 5^1

    euler_totient_sieve(100);
    cout << "phi(12) = " << phi[12] << '\n'; // 4

    return 0;
}
