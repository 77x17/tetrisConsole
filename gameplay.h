#include<conio.h>

const int nBoard = 3;
const int nDBlock = 2;
const int nBlock = 1;

bool play = true;
int inc = 1;

void gameplay() {
    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) currArr[i][j] = 0;
    }

    for (int i = 0; i <= w + 1; i++) currArr[0][i] = currArr[h + 1][i] = nBoard;
    for (int i = 0; i <= h + 1; i++) currArr[i][0] = currArr[i][w + 1] = nBoard;

    Block nextBlock = randBlock();

    nextBlock.printBlock();

    while (play) {
        if (lines <= 10) level = 1;
        else if (lines <= 30) level = 2;
        else if (lines <= 50) level = 3;
        else if (lines <= 75) level = 4;
        else if (lines <= 100) level = 5;
        else if (lines <= 125) level = 6;  
        else if (lines <= 150) level = 7;  
        else if (lines <= 175) level = 8;  
        else if (lines <= 200) level = 9;
        else level = 10;

        // display
        gotoxy(7, 30); color(0); cout << "Level: " << level;

        gotoxy(9, 30); color(0); cout << "Points: " << points;

        gotoxy(11, 30); color(0); cout << "Lines: " << lines;
        
        Block currBlock = nextBlock;

        nextBlock.deleteBlock();
        nextBlock = randBlock();
        nextBlock.printBlock();
        //
        
        // currBlock.x = 1; 
        
        // currBlock.y = inc;

        // inc += 2;

        // if (inc == 11) inc = 1;

        // currBlock.y = getch() - 48;

        currBlock.x = 1, currBlock.y = 4;

        if (currBlock.check(currBlock.x, currBlock.y)) currBlock.printBlock();

        play = false;

        const int DELTA_TIME = 1000;
        clock_t time_now = clock();

        while (true) {
            char dir = get_char_from_key();
            if (dir == 'd') currBlock.move_right();
            if (dir == 'a') currBlock.move_left();
            if (dir == 'w') currBlock.blockRotate();
            if (dir == 's') currBlock.moveDown();

            if (clock() - time_now >= DELTA_TIME / (level * 0.75)) {
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
                    for (int i = 0; i < currBlock.get_size(); i++) {
                        bool allFill = true;
                        for (int j = 1; j <= w; j++) if (currArr[currBlock.x + i][j] == 0) allFill = false;

                        if (allFill) {
                            cnt++;

                            for (int j = 1; j <= w; j++) {
                                currArr[currBlock.x + i][j] = 0;
                                gotoxy(currBlock.x + i, j); cout << ' ';
                            }

                            for (int _i = currBlock.x + i - 1; _i >= 1; _i--) {
                                for (int _j = 1; _j <= w; _j++) if (currArr[_i][_j]) {
                                    currArr[_i + 1][_j] = currArr[_i][_j];  currArr[_i][_j] = 0;
                                    currColor[_i + 1][_j] = currColor[_i][_j];

                                    gotoxy(_i, _j); cout << ' ';
                                    gotoxy(_i + 1, _j); color(currColor[_i][_j]); cout << '#';
                                }
                            }
                        }
                    }

                    if (cnt == 1) points += 40 * level;
                    if (cnt == 2) points += 100 * level;
                    if (cnt == 3) points += 300 * level;
                    if (cnt == 4) points += 1200 * level;

                    lines += cnt * 2;

                    break;
                } else play = true;
                time_now = clock();
            }
        }
    }

    gotoxy(22,1);
}
