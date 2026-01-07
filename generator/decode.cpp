#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const ll PROD_LIMIT = (ll)1e18;
const ll ANS_LIMIT_GLOBAL = (ll)1e18;

// Build all primes in [2, limit] using sieve
vector<ll> buildPrimes(ll limit) {
    vector<ll> primes;
    if (limit < 2) return primes;
    int n = (int)limit;
    vector<bool> isPrime(n + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= n; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= n; j += i)
            isPrime[j] = false;
    }
    for (int i = 2; i <= n; ++i)
        if (isPrime[i]) primes.push_back(i);
    return primes;
}

// Generate k random keys p_i in [2, maxP] with product <= 1e18 and no 1
vector<ll> genKeysRandom(int k, ll maxP) {
    vector<ll> p(k);

    if (maxP < 2) {
        quitf(_fail, "max_p must be >= 2 for genKeysRandom");
    }

    __int128 capacity = PROD_LIMIT;

    for (int i = 0; i < k; ++i) {
        int rem = k - i;
        __int128 denom = ((__int128)1 << (rem - 1));
        ll hi_cap = (ll)(capacity / denom);
        if (hi_cap < 2) hi_cap = 2;

        ll hi = min(maxP, hi_cap);
        if (hi < 2) hi = 2;

        ll x = rnd.next(2LL, hi);
        p[i] = x;
        capacity /= x;
    }

    return p;
}

// Choose a random n so that the answer is <= 1e18 and also <= ans_cap if given
ll chooseNForKeys(vector<ll>& p, ll max_n, ll ans_cap) {
    ll minp = *min_element(p.begin(), p.end());
    if (minp <= 0) minp = 1;

    ll nLimit = max_n;
    nLimit = min(nLimit, ANS_LIMIT_GLOBAL / max(1LL, minp));

    if (ans_cap > 0) {
        ll tmp = ans_cap / max(1LL, minp);
        nLimit = min(nLimit, tmp);
    }

    if (nLimit < 1) nLimit = 1;
    return rnd.next(1LL, nLimit);
}

// Generate a general random test: random k, random keys, random n
void gen_random(const char* fn, ll max_n, int max_k, ll max_p, ll ans_cap) {
    FILE* f = fopen(fn, "w");
    if (!f) quitf(_fail, "Cannot open %s", fn);

    int k = rnd.next(1, max_k);
    vector<ll> p = genKeysRandom(k, max_p);
    ll n = chooseNForKeys(p, max_n, ans_cap);

    fprintf(f, "%lld %d\n", n, k);
    for (int i = 0; i < k; ++i) {
        if (i) fprintf(f, " ");
        fprintf(f, "%lld", p[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}

// Generate a test with k = 1
void gen_k1(const char* fn, ll max_n, ll max_p, ll ans_cap) {
    FILE* f = fopen(fn, "w");
    if (!f) quitf(_fail, "Cannot open %s", fn);

    int k = 1;
    if (max_p < 2) quitf(_fail, "max_p must be >= 2 for gen_k1");
    vector<ll> p(1);
    p[0] = rnd.next(2LL, max_p);

    ll n = chooseNForKeys(p, max_n, ans_cap);

    fprintf(f, "%lld %d\n", n, k);
    fprintf(f, "%lld\n", p[0]);
    fclose(f);
}

// Generate a test with one p_i = 1 to break wrong solutions
void gen_with_one(const char* fn, ll max_n, int max_k, ll max_p, ll ans_cap) {
    FILE* f = fopen(fn, "w");
    if (!f) quitf(_fail, "Cannot open %s", fn);

    int k = rnd.next(1, max_k);
    vector<ll> p = genKeysRandom(k, max_p);
    p[0] = 1;

    ll n = chooseNForKeys(p, max_n, ans_cap);

    fprintf(f, "%lld %d\n", n, k);
    for (int i = 0; i < k; ++i) {
        if (i) fprintf(f, " ");
        fprintf(f, "%lld", p[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}

// Generate a fixed hardest test with n = max_n and k = max_k depending on subtask c
void gen_maxNK_fixed(int c, const char* fn, ll max_n, int max_k, ll max_p, ll ans_cap) {
    FILE* f = fopen(fn, "w");
    if (!f) quitf(_fail, "Cannot open %s", fn);

    int k = max_k;
    vector<ll> p;

    if (c == 2) {
        static const ll base2[] = {2, 3};
        for (int i = 0; i < k; ++i) p.push_back(base2[i]);
    } else if (c == 3) {
        static const ll base3[] = {2, 3, 5, 7, 11, 13};
        for (int i = 0; i < k; ++i) p.push_back(base3[i]);
    } else if (c == 4) {
        static const ll base4[] = {997, 991, 983, 977, 971, 967};
        for (int i = 0; i < k; ++i) p.push_back(base4[i]);
    }

    __int128 prod = 1;
    for (int i = 0; i < k; ++i) prod *= p[i];
    if (prod > (__int128)PROD_LIMIT) {
        quitf(_fail, "Fixed MAXNK product exceeds 1e18");
    }

    ll n = max_n;

    fprintf(f, "%lld %d\n", n, k);
    for (int i = 0; i < k; ++i) {
        if (i) fprintf(f, " ");
        fprintf(f, "%lld", p[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}

// Generate a test with k=6 distinct primes <= 1000
void gen_6primes_distinct_small1000(const char* fn, ll max_n, ll max_p, ll ans_cap) {
    FILE* f = fopen(fn, "w");
    if (!f) quitf(_fail, "Cannot open %s", fn);

    int k = 6;
    if (max_p < 2) quitf(_fail, "max_p must be >= 2 for gen_6primes_distinct_small1000");

    ll primeLimit = min(max_p, (ll)1000);
    vector<ll> primes = buildPrimes(primeLimit);
    if ((int)primes.size() < k) {
        static const ll small[] = {2, 3, 5, 7, 11, 13};
        vector<ll> p(small, small + 6);
        ll n = chooseNForKeys(p, max_n, ans_cap);
        fprintf(f, "%lld %d\n", n, k);
        for (int i = 0; i < k; ++i) {
            if (i) fprintf(f, " ");
            fprintf(f, "%lld", p[i]);
        }
        fprintf(f, "\n");
        fclose(f);
        return;
    }

    shuffle(primes.begin(), primes.end());
    vector<ll> p(k);
    for (int i = 0; i < k; ++i) p[i] = primes[i];

    ll n = chooseNForKeys(p, max_n, ans_cap);

    fprintf(f, "%lld %d\n", n, k);
    for (int i = 0; i < k; ++i) {
        if (i) fprintf(f, " ");
        fprintf(f, "%lld", p[i]);
    }
    fprintf(f, "\n");
    fclose(f);
}

// Main: parse arguments and generate all test files for a given subtask
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    if (argc < 5) {
        quitf(_fail, "Usage: %s c max_n max_k max_p [ans_cap]", argv[0]);
    }

    int c = atoi(argv[1]);
    ll max_n = atoll(argv[2]);
    int max_k = atoi(argv[3]);
    ll max_p = atoll(argv[4]);
    ll ans_cap = 0;
    if (argc >= 6) ans_cap = atoll(argv[5]);

    if (max_k <= 0 || max_k > 6) {
        quitf(_fail, "max_k must be in [1, 6]");
    }
    if (max_p < 2) {
        quitf(_fail, "max_p must be >= 2");
    }

    char fn[64];

    // 1..15: random
    for (int i = 1; i <= 15; ++i) {
        sprintf(fn, "%d_%02d.in", c, i);
        gen_random(fn, max_n, max_k, max_p, ans_cap);
    }

    // 16: k = 1
    sprintf(fn, "%d_%02d.in", c, 16);
    gen_k1(fn, max_n, max_p, ans_cap);

    // 17: with_one
    sprintf(fn, "%d_%02d.in", c, 17);
    gen_with_one(fn, max_n, max_k, max_p, ans_cap);

    int cur = 18;

    // 18: fixed MAXNK for c != 1
    if (c != 1) {
        sprintf(fn, "%d_%02d.in", c, cur++);
        gen_maxNK_fixed(c, fn, max_n, max_k, max_p, ans_cap);
    }

    // 19 ~ 23: k = 6, p_i is prime, p_i <= 1000
    if (max_k >= 6) {
        for (int t = 0; t < 5; ++t) {
            sprintf(fn, "%d_%02d.in", c, cur++);
            gen_6primes_distinct_small1000(fn, max_n, max_p, ans_cap);
        }
    }

    return 0;
}
