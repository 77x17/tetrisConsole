using matrix = vector<vector<int>>;

int random(int l, int r) {
    return rand() % (r - l + 1) + l;
}

struct Block{
    matrix arr;
};

Block blockArr[2];

Block randBlock() {
    srand(time(NULL));

    blockArr[0].arr = {{1, 1},
                       {1, 1}};

    blockArr[1].arr = {{0, 1, 0, 0},
                       {0, 1, 0, 0},
                       {0, 1, 0, 0},
                       {0, 1, 0, 0}};

    return blockArr[random(0, 1)];
}
