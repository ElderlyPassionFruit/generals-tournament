#pragma once

#include "Cell.h"
#include "Config.h"
#include "Map.h"

class Game {
public:
    Game(const std::string& configpath);
    std::string Process();
    Config GetConfig() const;

private:
    Config config_;
    Map map_;
};