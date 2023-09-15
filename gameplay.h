#include<conio.h>

const int nBoard = 3;
const int nDBlock = 2;
const int nBlock = 1;

bool play = true;
const int speed[11] = {0, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100};

void gameplay() {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) currArr[i][j] = 0;
    }

    for (int i = 0; i <= w + 1; i++) currArr[0][i] = currArr[h + 1][i] = nBoard;
    for (int i = 0; i <= h + 1; i++) currArr[i][0] = currArr[i][w + 1] = nBoard;

    Block nextBlock = randBlock();

    nextBlock.printBlock();

    while (play) {
        level = min(10, max(1, lines / 10));

        // display
        gotoxy(8, 31); setColor(BRIGHTWHITE, 0); cout << points;

        gotoxy(9, 31); setColor(BRIGHTWHITE, 0); cout << level;

        gotoxy(10, 31); setColor(BRIGHTWHITE, 0); cout << lines;

        Block currBlock = nextBlock;

        nextBlock.deleteBlock();
        nextBlock = randBlock();
        nextBlock.printBlock();

        currBlock.x = 1, currBlock.y = 4;

        if (currBlock.check(currBlock.x, currBlock.y)) currBlock.printBlock();

        play = false;

        clock_t time_now = clock();

        while (true) {
            char dir = get_char_from_key();
            if (dir == 'd') currBlock.move_right();
            if (dir == 'a') currBlock.move_left();
            if (dir == 'w') currBlock.blockRotate();
            if (dir == 's') if (currBlock.moveDown()) play = true;
            if (dir == ' ') while (currBlock.moveDown()) play = true;

            if (clock() - time_now >= speed[level]) {
                if (!currBlock.moveDown()) {
                    for (int i = 0; i < currBlock.get_size(); i++) {
                        for (int j = 0; j < currBlock.get_size(); j++) {
                            if (currBlock.arr[i][j]) {
                                currArr[currBlock.x + i][currBlock.y + j] = nDBlock;
                                currColor[currBlock.x + i][currBlock.y + j] = currBlock.type;
                            }
                        }
                    }

                    int cnt = 0;
                    for (int i = 0; i < currBlock.get_size(); i++) if (currBlock.x + i <= h) {
                        bool allFill = true;
                        for (int j = 1; j <= w; j++) if (currArr[currBlock.x + i][j] == 0) allFill = false;

                        if (allFill) {
                            cout << '\a';

                            cnt++;

                            for (int j = 1; j <= w; j++) {
                                currArr[currBlock.x + i][j] = 0;
                                gotoxy(currBlock.x + i, j), color((currBlock.x + i + j) % 2 ? BRIGHTWHITE : LIGHTGRAY), cout << ' ';
                            }

                            for (int _i = currBlock.x + i - 1; _i >= 1; _i--) {
                                for (int _j = 1; _j <= w; _j++) if (currArr[_i][_j]) {
                                    currArr[_i + 1][_j] = currArr[_i][_j];  currArr[_i][_j] = 0;
                                    currColor[_i + 1][_j] = currColor[_i][_j];

                                    gotoxy(_i, _j), color((_i + _j) % 2 ? BRIGHTWHITE : LIGHTGRAY), cout << ' ';
                                    gotoxy(_i + 1, _j); color(currColor[_i][_j]); cout << '#';
                                }
                            }
                        }
                    }

                    if (cnt == 1) points += 40 * level;
                    if (cnt == 2) points += 100 * level;
                    if (cnt == 3) points += 300 * level;
                    if (cnt == 4) points += 1200 * level;

                    lines += cnt;

                    break;
                } else play = true;
                time_now = clock();
            }
        }
    }

    gotoxy(22,1);
}
