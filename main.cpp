#include <bits/stdc++.h>
using namespace std;

const int w = 10;
const int h = 20;

int points = 0, level = 1, lines = 0;
int currArr[h + 2][w + 2], currColor[h + 2][w + 2];

#include "settings.h"
#include "map.h"
#include "block.h"
#include "control.h"
#include "gameplay.h"

int main() {
    settings::main();

    buildBoard();

    gameplay();

    char s = getch();

    return 0;
}
