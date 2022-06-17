#pragma once

#include "Cell.h"
#include "Config.h"
#include "Map.h"
#include "Player.h"

class Game {
public:
    Game(const std::string& configpath);
    std::string Process();

private:
    Config config_;
    Map map_;
};