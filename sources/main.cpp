#include "Game.h"

#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Incorrect number of arguments" << endl;
        exit(EXIT_FAILURE);
    }
    string configpath = argv[1];
    Game game(configpath);
    string log = game.Process() + "0\n";
    fstream fout(game.GetConfig().GetLogpath(), ios::out);
    fout << log << endl;
    // cerr << "log:" << endl;
    // cerr << log << endl;
    exit(EXIT_SUCCESS);
}