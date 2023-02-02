#include <bits/stdc++.h>

#define MAX 100000

using namespace std;

long long primes_len;
vector<long long> primes;

long long power(long long base, long long exp, long long mod) {
    long long mult = 1LL;

    while (exp) {
        if (exp & 1)
            mult = (mult % mod * base % mod) % mod;

        base = (base % mod * base % mod) % mod;
        exp >>= 1;
    }

    return mult;
}

long long extended_gcd(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    long long x1, y1, gcd;
    gcd = extended_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);

    return gcd;
}

long long find_coprime(long long phi) {
    long long x;

    do {
        x = primes[rand() % primes_len];
    } while (__gcd(x, phi) != 1 && (x <= 1 || x >= phi));

    return x;
}

vector<long long> sieve() {
    vector<bool> is_prime(MAX + 1, true);
    is_prime[0] = is_prime[1] = false;

    for (int i = 2; i * i <= MAX; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX; j += i)
                is_prime[j] = false;
        }
    }

    vector<long long> p;

    for (int i = 0; i <= MAX; i++) {
        if (is_prime[i])
            p.push_back(i);
    }

    return p;
}

int main() {
    srand(time(NULL));

    primes = sieve();
    primes_len = primes.size();

    long long p, q, N, phi, e, d, y;

    do {
        p = primes[rand() % primes_len];

        do {
            q = primes[rand() % primes_len];
        } while (q == p);

        N = p * q;
        phi = (p - 1) * (q - 1);
        e = find_coprime(phi);
        extended_gcd(e, phi, d, y);
    } while (d < 0);

    pair<long long, long long> pub_key, pvt_key;
    pub_key = {e, N};
    pvt_key = {d, N};

    cout << "CHAVE PUBLICA:\n";
    cout << "\tE -> " << pub_key.first << "\n\tMOD -> " << pub_key.second << "\n\n";

    cout << "CHAVE PRIVADA:\n";
    cout << "\tD -> " << pvt_key.first << "\n\tMOD -> " << pvt_key.second << "\n\n";

    string s;
    vector<string> lines;
    vector<vector<long long>> crypt;

    while (getline(cin, s))
        lines.push_back(s);

    cout << "MENSAGEM CRIPTOGRAFADA:\n\n";

    for (int i = 0; i < lines.size(); i++) {
        vector<long long> aux;
        cout << "\t";

        for (int j = 0; j < lines[i].size(); j++) {
            long long hash = power(static_cast<long long>(lines[i][j]), e, N);
            cout << hash << " ";
            aux.push_back(hash);
        }

        cout << "\n";
        crypt.push_back(aux);
    }

    cout << "\nMENSAGEM DESCRIPTOGRAFADA:\n\n";

    for (int i = 0; i < crypt.size(); i++) {
        cout << "\t";

        for (int j = 0; j < crypt[i].size(); j++) {
            char c = static_cast<char>(power(crypt[i][j], d, N));
            cout << c;
        }

        cout << "\n";
    }

    return 0;
}