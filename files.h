#pragma once

class file_work {
private:
    string path = "game_score.txt";
    string path2 = "game_level.txt";
public:
    void infile();
    void outfile();
} file;