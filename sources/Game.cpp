#include "Game.h"

#include <iostream>

// Game

Game::Game(const std::string& configpath) : config_(configpath), map_(config_.GetMappath()) {
}

std::string Game::Process() {
    std::string log = map_.GetInitialInput();
    static const size_t MAX_ITERATION = 10000;

    std::vector<bool> must_skip(map_.GetPlayers() + 1, false);

    auto alive = [&]() -> bool {
        size_t cnt_alive = 0;
        for (size_t player_id = 1; player_id <= map_.GetPlayers(); ++player_id) {
            cnt_alive += !map_.IsDestroyed(player_id);
        }
        return cnt_alive > 1;
    };

    for (size_t it = 1; it <= MAX_ITERATION && alive(); ++it) {
        if (it % 5 == 0) {
            std::cerr << "progress: " << (double)it / MAX_ITERATION * 100 << "%" << std::endl;
        }
        for (size_t player_id = 1; player_id <= map_.GetPlayers() && alive(); ++player_id) {
            if (must_skip[player_id]) {
                continue;
            }
            if (it == 1) {
                std::cout << map_.GetInitialInput(player_id);
            }
            std::cout << map_.GetLog(player_id);
            std::cout.flush();
            if (map_.IsDestroyed(player_id)) {
                must_skip[player_id] = true;
                continue;
            }
            int type;
            std::cin >> type;
            if (type == -1) {
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
            map_.MakeMove(player_id, Coordinates(i, j), Coordinates(i_, j_), type);
            log += map_.GetLog();
        }
        map_.MakeTurn();
        if (it % 2 == 0) {
            log += map_.GetLog();
        }
    }
    if (!alive()) {
        std::cerr << "progress: "
                  << "100%" << std::endl;
    }
    return log;
}

Config Game::GetConfig() const {
    return config_;
}