#define sz(s) (int)s.size()
using matrix = vector<vector<int>>;

int random(int l, int r) {
    return 1ll * rand() * rand() % (r - l + 1) + l;
}

struct Block{
    int type, x, y;
    matrix arr;

    int get_size() { return sz(arr); }

    void deleteBlock() {
        for (int i = 0; i < get_size(); i++)
            for (int j = 0; j < get_size(); j++)
                if (arr[i][j]) gotoxy(x + i, y + j), cout << ' ';
    }

    void printBlock() {
        for (int i = 0; i < get_size(); i++) {
            for (int j = 0; j < get_size(); j++) {
                gotoxy(x + i, y + j); color(type);
                if (arr[i][j]) cout << '#';
            }
        }
    }

    bool check(int x, int y) {
        for (int i = 0; i < get_size(); i++) {
            for (int j = 0; j < get_size(); j++) {
                if (arr[i][j] && currArr[x + i][y + j] != 0)
                    return false;
            }
        }

        return true;
    }

    void update_layer(int p, int n) {
        matrix temp = arr;
        for (int i = p; i < n - p; i++) {
            arr[p][i] = temp[i][n - p - 1];
            arr[i][n - p - 1] = temp[n - p - 1][n - i - 1];
            arr[n - p - 1][n - i - 1] = temp[n - i - 1][p];
            arr[n - i - 1][p] = temp[p][i];
        }
    }

    void rotate() {
        int n = get_size();
        for (int i = 0; i < n / 2; i++)
            update_layer(i, n);
    }

    bool checkRotate() {
        Block temp = {type, x, y, arr};

        temp.rotate();

        return temp.check(x, y);
    }

    void blockRotate() {
        if (!checkRotate()) return;

        deleteBlock();

        rotate();

        printBlock();
    }

    bool moveDown() {
        if (!check(x + 1, y)) return false;

        deleteBlock();

        x++;

        printBlock();

        return true;
    }
};

Block blockArr[3];

Block randBlock() {
    srand(time(NULL));

    blockArr[0] = {
        0,          // type
        1, 30, {    // x, y
        {1, 1},     // block shape
        {1, 1}
    }};

    blockArr[1] = {
        1,              
        1, 30, {
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0},
        {0, 0, 1, 0}
    }};

    blockArr[2] = {
        2,              
        1, 30, {
        {0, 0, 0},
        {0, 1, 0},
        {1, 1, 1}
    }};

    int temp = random(0, 0);

    Block result = blockArr[temp];

    int n = random(0, 3);
    for (int i = 1; i <= n; i++) result.rotate();

    return result;
}
