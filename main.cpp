#include <bits/stdc++.h>
using namespace std;

#include "map.h"
#include "block.h"

int main() {
    buildMap();

    Block curr = randBlock();

    for (int i = 0; i <= 3; i++) {
        for (int j = 0; j <= 3; j++) {
            if (curr.arr[i][j] == 1) cout << 'x'; else cout << ' ';
        }
        cout << '\n';
    }

    return 0;
}
