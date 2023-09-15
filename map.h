void buildBoard() {
    ifstream file((const string)"Board.txt");

    string s;
    while (getline(file, s)) cout << s << '\n';

    file.close();
}