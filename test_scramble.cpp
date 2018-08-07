#include "Scramble.h"
#include <iostream>

using namespace std;
int main() {
    for(int i = 0; i < 100; ++i) {
        cout << get_scramble() << endl;
    }
    return 0;
}
