#include "Game.h"

#include <iostream>

// Game

Game::Game(const std::string& configpath)
    : config_(configpath), map_(config_.GetMappath()) {
}

std::string Game::Process() {
    // std::cerr << "Process start" << std::endl;
    std::string log = map_.GetInitialInput();
    static const size_t MAX_ITERATION = 1000;
    
    auto alive = [&] () -> bool {
        size_t cnt_alive = 0;
        for (size_t player_id = 1; player_id <= map_.GetPlayers(); ++player_id) {
            cnt_alive += !map_.IsDestroyed(player_id);
        }
        return cnt_alive > 1;
    };

    map_.PrintMap();

    for (size_t it = 1; it <= MAX_ITERATION && alive(); ++it) {
        // std::cerr << "it = " << it << std::endl;
        for (size_t player_id = 1; player_id <= map_.GetPlayers() && alive(); ++player_id) {
            // std::cerr << "player_id = " << player_id << std::endl;
            map_.PrintMap();
            if (it == 1) {
                // std::cerr << "initial input for player_id = " << player_id << std::endl;
                std::cout << map_.GetInitialInput(player_id);
                // std::cerr << "finish" << std::endl;
            }
            // std::cerr << "start output" << std::endl;
            std::cout << map_.GetLog(player_id);
            std::cout.flush();
            // std::cerr << "finish output" << std::endl;
            // std::cerr << "start input" << std::endl;
            int type;
            std::cin >> type;
            // std::cerr << "type = " << type << std::endl;
            if (type == -1) {
                // std::cerr << "continue" << std::endl;
                continue;
            }
            int i, j, i_, j_;
            std::cin >> i;
            std::cin >> j;
            std::cin >> i_;
            std::cin >> j_;
            --i;
            --j;
            --i_;
            --j_;
            // std::cerr << "finish input" << std::endl;
            map_.MakeMove(player_id, Coordinates(i, j), Coordinates(i_, j_), type);
            log += map_.GetLog();
        }
        map_.MakeTurn();
        if (it % 2 == 0) {
            log += map_.GetLog();
        }
    }
    return log;
}
