#pragma once

#include <string>
#include <vector>

class Config {
public:
    using TContainer = std::vector<std::string>;
    Config(const std::string& configpath);
    std::string GetMappath() const;
    TContainer GetPlayerPrograms() const;

private:
    std::string mappath_;
    TContainer player_programs_;
};
