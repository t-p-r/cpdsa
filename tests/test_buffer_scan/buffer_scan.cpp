#include "lib/cpdsa/cpdsa.hpp"
using namespace std;

int main() {
    int n;
    cpdsa::buffer_scan(n);
    int x;
    while (n--) {
        cpdsa::buffer_scan(x);
    }
}