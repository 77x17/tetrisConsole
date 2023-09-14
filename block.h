#define sz(s) (int)s.size()
using matrix = vector<vector<int>>;

int random(int l, int r) {
    return rand() % (r - l + 1) + l;
}

struct Block{
    matrix arr;

    int get_size() { return sz(arr); }

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

    void out_block() {
        for (int i = 0; i < get_size(); i++) {
            for (int j = 0; j < get_size(); j++)
                if (arr[i][j]) cout << '#';
                else cout << ' ';
            cout << '\n';
        }
    }
};

Block blockArr[2];

Block randBlock() {
    srand(time(NULL));

    blockArr[0].arr = {{1, 1},
                       {1, 1}};

    blockArr[1].arr = {{0, 0, 1, 0},
                       {0, 0, 1, 0},
                       {0, 0, 1, 0},
                       {0, 0, 1, 0}};

    return blockArr[random(0, 1)];
}
