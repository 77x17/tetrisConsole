const int nBoard = 3;
const int nDBlock = 2;
const int nBlock = 1;

bool play = true;

void gameplay() {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) currArr[i][j] = 0;
    }

    for (int i = 0; i <= w + 1; i++) currArr[0][i] = currArr[h + 1][i] = nBoard;
    for (int i = 0; i <= h + 1; i++) currArr[i][0] = currArr[i][w + 1] = nBoard;

    while (play) {
        Block curr = randBlock();
        curr.blockRotate();

        if (curr.check(curr.x, curr.y)) curr.printBlock();

        play = false;

        while (true) {
            if (!curr.moveDown()) {
                for (int i = 0; i < curr.get_size(); i++) {
                    for (int j = 0; j < curr.get_size(); j++) {
                        if (curr.arr[i][j]) currArr[curr.x + i][curr.y + j] = nDBlock;
                    }
                }

                break;
            } else play = true;

            Sleep(50);
            curr.blockRotate();
        }
    }

    gotoxy(22,1);
}
