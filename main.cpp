#include <bits/stdc++.h>
using namespace std;

#include "settings.h"
#include "map.h"
#include "block.h"
#include "gameplay.h"

int main() {
    settings::main();

    tetrisMap::buildBoard();

    gameplay();

    return 0;
}
