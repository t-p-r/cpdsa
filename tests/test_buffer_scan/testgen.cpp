#include "lib/testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int n = opt<int>("n");
    int lim = 1e9;
    cout << n << '\n';
    while (n--) {
        cout << rnd.next(-lim, lim) << ' ';
    }
}