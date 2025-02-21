#include <bits/stdc++.h>
#include "lib/cpdsa/cpdsa.hpp"
using namespace std;

mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}

constexpr size_t MAX_SIZE = (1 << 24);

static unsigned int v[MAX_SIZE], v2[MAX_SIZE], v3[MAX_SIZE];
// setup branch prediction, cache fitting, etc.
void heatup(int n) {
    for (int i = 0; i < n; ++i)
        v[i] = rand(INT_MIN, INT_MAX);
    copy(v, v + n, v2);
    copy(v, v + n, v3);

    sort(v, v + n);
    cpdsa::radix_sort(v2, v2 + n);
    cpdsa::radix_sort<16>(v3, v3 + n);
}

int32_t main(int argc, char* argv[]) {
#ifdef _TPR_
    freopen("t.inp", "r", stdin);
    freopen("t.out", "w", stdout);
#endif
    for (int n = (1 << 18); n <= (1 << 18); n <<= 1) {
        if (n > 1000)
            n -= n % 1000;
        // heatup(n);
        // heatup(n);
        // heatup(n);  // just to make sure

        for (int i = 0; i < n; ++i)
            v[i] = rand((int)-1e9, (int)1e9);
        copy(v, v + n, v2);
        copy(v, v + n, v3);

        auto start1 =
            chrono::high_resolution_clock::now().time_since_epoch().count();
        sort(v, v + n);
        auto start2 =
            chrono::high_resolution_clock::now().time_since_epoch().count();
        cpdsa::radix_sort(v2, v2 + n);
        auto start3 =
            chrono::high_resolution_clock::now().time_since_epoch().count();
        cpdsa::radix_sort<10>(v3, v3 + n);
        auto start4 =
            chrono::high_resolution_clock::now().time_since_epoch().count();

        // final validation run
        for (int i = 1; i < n; i++) {
            assert(v[i] >= v[i - 1]);
            assert(v2[i] >= v2[i - 1]);
            assert(v3[i] >= v3[i - 1]);
        }

        auto std_sort_time = (start2 - start1) / 1e6;
        auto r8_sort_time = (start3 - start2) / 1e6;
        auto r16_sort_time = (start4 - start3) / 1e6;
        printf("n = %d:\n", n);
        printf("std::sort:                    %.5f ms \n", std_sort_time);
        printf("cpdsa::radix_sort (radix 8):  %.5f ms (%.5fx faster)\n",
               r8_sort_time, std_sort_time / r8_sort_time);
        printf("cpdsa::radix_sort (radix 16): %.5f ms (%.5fx faster)\n\n",
               r16_sort_time, std_sort_time / r16_sort_time);
    }
}
