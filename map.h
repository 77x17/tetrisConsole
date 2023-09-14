namespace tetrisMap {
    void buildBoard() {
        std::ifstream file((const std::string)"Board.txt");

        std::string s;
        while (getline(file, s)) std::cout << s << '\n';

        file.close();
    }
}
