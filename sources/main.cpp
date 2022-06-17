#include "Game.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Incorrect number of arguments" << endl;
        exit(EXIT_FAILURE);
    }
    string configpath = argv[1];
    Game game(configpath);
    string log = game.Process() + "0\n";
    // cerr << "log:" << endl;
    cerr << log << endl;
    exit(EXIT_SUCCESS);
}