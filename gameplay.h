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

    Block nextBlock = randBlock();

    nextBlock.printBlock();

    while (play) {
        Block currBlock = nextBlock;

        nextBlock.deleteBlock();
        nextBlock = randBlock();
        nextBlock.printBlock();

        currBlock.x = 1, currBlock.y = 4;

        if (currBlock.check(currBlock.x, currBlock.y)) currBlock.printBlock();

        play = false;

        while (true) {
            if (!currBlock.moveDown()) {
                for (int i = 0; i < currBlock.get_size(); i++) {
                    for (int j = 0; j < currBlock.get_size(); j++) {
                        if (currBlock.arr[i][j]) currArr[currBlock.x + i][currBlock.y + j] = nDBlock;
                    }
                }

                break;
            } else play = true;

            Sleep(50);
        }
    }

    gotoxy(22,1);
}
