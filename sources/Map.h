#pragma once

#include "Cell.h"

#include <string>
#include <vector>

struct PlayerStatistics {
    size_t total_army_size = 0;
    size_t total_land_size = 0;
    PlayerStatistics() = default;
    PlayerStatistics(size_t total_army_size_, size_t total_land_size_)
        : total_army_size(total_army_size_), total_land_size(total_land_size_) {
    }
};

class Map {
public:
    using TContainer = std::vector<std::vector<Cell>>;
    Map(const std::string& mappath);
    void MakeTurn();
    void MakeMove(size_t player_id, const Coordinates& from, const Coordinates& to,
                         size_t move_type);
    std::string GetInitialInput(size_t player_id = 0) const;
    std::string GetLog(size_t player_id = 0) const;
    bool IsDestroyed(size_t player_id) const;
    size_t GetPlayers() const;
    void PrintMap() const;
private:
    bool IsVisible(size_t player_id, int x, int y) const;
    Map::TContainer GetVisibleMap(size_t player_id) const;
    PlayerStatistics GetPlayerStatistics(size_t player_id) const;
    std::string GetPlayersStatistics() const;
    void DestroyPlayer(size_t player_id, size_t new_owner = 0);
    bool IsIn(int x, int y) const;
    size_t n_, m_;
    size_t players_;
    TContainer map_;
    size_t timer_;
};