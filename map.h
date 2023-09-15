void buildBoard() {
    ifstream file((const string)"Board.txt");

    string s;
    while (getline(file, s)) cout << s << '\n';

    file.close();

    for (int i = 1; i <= h; i++) {
        for (int j = 1; j <= w; j++) gotoxy(i, j), color((i + j) % 2 ? BRIGHTWHITE : LIGHTGRAY), cout << ' ';
    }
}