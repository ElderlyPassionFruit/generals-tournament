#include "Map.h"

#include <iostream>
#include <fstream>

Map::Map(const std::string& mappath) : timer_(0) {
    std::fstream in(mappath);
    in >> n_;
    in >> m_;
    in >> players_;
    map_.resize(n_, std::vector<Cell>(m_));
    size_t has_players = 0;
    for (size_t x = 0; x < n_; ++x) {
        for (size_t y = 0; y < m_; ++y) {
            Cell::CellType type;
            int value;
            in >> value;
            type = static_cast<Cell::CellType>(value);
            size_t owner = 0;
            size_t army_size = 0;
            if (type == Cell::CellType::CAPITAL) {
                owner = ++has_players;
                army_size = 1;
            } else if (type == Cell::CellType::CITY) {
                in >> army_size;
            }
            map_[x][y] = Cell(type, owner, army_size);
        }
    }
}

void Map::PrintMap() const {
    return;
    std::cerr << "output map" << std::endl;
    for (int x = 0; x < static_cast<int>(n_); ++x) {
        for (int y = 0; y < static_cast<int>(m_); ++y) {
            std::cerr << map_[x][y].GetArmySize() << " ";
        }
        std::cerr << std::endl;
    }
    std::cerr << "finish" << std::endl;
}

void Map::MakeTurn() {
    ++timer_;
    if (timer_ % 2 == 0) {
        for (size_t x = 0; x < n_; ++x) {
            for (size_t y = 0; y < m_; ++y) {
                if (map_[x][y].GetOwner() != 0 &&
                    (map_[x][y].GetType() == Cell::CellType::CITY ||
                     map_[x][y].GetType() == Cell::CellType::CAPITAL)) {
                    map_[x][y].GetArmySize() += 1;
                }
            }
        }
    }
    if (timer_ % 50 == 0) {
        for (size_t x = 0; x < n_; ++x) {
            for (size_t y = 0; y < m_; ++y) {
                if (map_[x][y].GetOwner() != 0 && (map_[x][y].GetType() == Cell::CellType::EMPTY)) {
                    map_[x][y].GetArmySize() += 1;
                }
            }
        }
    }
}

void Map::MakeMove(size_t player_id, const Coordinates& from, const Coordinates& to,
                   size_t move_type) {
    if (!IsIn(from.x, from.y) || !IsIn(to.x, to.y) || Dist(from, to) != 1 ||
        map_[from.x][from.y].GetOwner() != player_id ||
        map_[to.x][to.y].GetType() == Cell::CellType::MOUNTAINS) {
        std::cerr << "destroy player_id = " << player_id << std::endl;
        std::cerr << "from.x = " << from.x << " from.y = " << from.y << " to.x = " << to.x
                  << " to.y = " << to.y << std::endl;
        DestroyPlayer(player_id);
        return;
    }
    size_t army_size = 0;
    if (move_type == 1) {
        if (map_[from.x][from.y].GetArmySize() >= 2) {
            army_size = map_[from.x][from.y].GetArmySize() - 1;
        }
    } else if (move_type == 2) {
        if (map_[from.x][from.y].GetArmySize() >= 2) {
            army_size = map_[from.x][from.y].GetArmySize() / 2;
        }
    } else {
        DestroyPlayer(player_id);
        return;
    }

    if (!army_size) {
        return;
    }

    map_[from.x][from.y].GetArmySize() -= army_size;
    if (map_[to.x][to.y].GetOwner() == player_id) {
        map_[to.x][to.y].GetArmySize() += army_size;
    } else {
        size_t lost_army = std::min(army_size, map_[to.x][to.y].GetArmySize());
        army_size -= lost_army;
        map_[to.x][to.y].GetArmySize() -= lost_army;
        if (army_size) {
            if (map_[to.x][to.y].GetType() == Cell::CellType::CAPITAL) {
                size_t other_player_id = map_[to.x][to.y].GetOwner();
                map_[to.x][to.y] = Cell(Cell::CellType::CITY, player_id, army_size);
                DestroyPlayer(other_player_id, player_id);
            } else {
                map_[to.x][to.y].GetOwner() = player_id;
                map_[to.x][to.y].GetArmySize() = army_size;
            }
        }
    }
}

std::string Map::GetInitialInput(size_t player_id) const {
    return std::to_string(n_) + " " + std::to_string(m_) + " " + std::to_string(players_) + " " +
           std::to_string(player_id) + "\n";
}

bool Map::IsVisible(size_t player_id, int x, int y) const {
    if (!player_id) {
        return true;
    }
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            int nx = x + dx;
            int ny = y + dy;
            if (!IsIn(nx, ny)) {
                continue;
            }
            if (map_[nx][ny].GetOwner() == player_id) {
                return true;
            }
        }
    }
    return false;
}

Map::TContainer Map::GetVisibleMap(size_t player_id) const {
    auto map = map_;
    for (int x = 0; x < static_cast<int>(n_); ++x) {
        for (int y = 0; y < static_cast<int>(m_); ++y) {
            if (IsVisible(player_id, x, y)) {
                if (map[x][y].GetType() == Cell::CellType::EMPTY ||
                    map[x][y].GetType() == Cell::CellType::CAPITAL) {
                    map[x][y] = Cell(Cell::CellType::EMPTY, 0, 0);
                } else {
                    map[x][y] = Cell(Cell::CellType::MOUNTAINS, 0, 0);
                }
            }
        }
    }
    return map;
}

PlayerStatistics Map::GetPlayerStatistics(size_t player_id) const {
    PlayerStatistics player_statistics;
    for (size_t x = 0; x < n_; ++x) {
        for (size_t y = 0; y < m_; ++y) {
            if (map_[x][y].GetOwner() == player_id) {
                player_statistics.total_land_size += 1;
                player_statistics.total_army_size += map_[x][y].GetArmySize();
            }
        }
    }
    return player_statistics;
}

std::string Map::GetPlayersStatistics() const {
    std::string players_statistics;
    for (size_t player_id = 1; player_id <= players_; ++player_id) {
        auto player_statistics = GetPlayerStatistics(player_id);
        players_statistics += std::to_string(player_statistics.total_army_size) + " " +
                              std::to_string(player_statistics.total_land_size) + "\n";
    }
    return players_statistics;
}

bool Map::IsDestroyed(size_t player_id) const {
    if (!player_id) {
        return false;
    }
    for (size_t x = 0; x < n_; ++x) {
        for (size_t y = 0; y < m_; ++y) {
            if (map_[x][y].GetOwner() == player_id) {
                return false;
            }
        }
    }
    return true;
}

std::string Map::GetLog(size_t player_id) const {
    auto map = GetVisibleMap(player_id);
    std::string output;
    if (IsDestroyed(player_id)) {
        return "0\n";
    } else {
        output += "1\n";
    }
    output += GetPlayersStatistics();
    for (int x = 0; x < static_cast<int>(n_); ++x) {
        for (int y = 0; y < static_cast<int>(m_); ++y) {
            if (IsVisible(player_id, x, y)) {
                output += "1 " + std::to_string(map_[x][y].GetType());
                if (map_[x][y].GetType() != Cell::CellType::MOUNTAINS) {
                    output += " " + std::to_string(map_[x][y].GetOwner()) + " " +
                              std::to_string(map_[x][y].GetArmySize());
                }
                output += "\n";
            } else {
                output += "0 ";
                if (map_[x][y].GetType() == Cell::CellType::EMPTY ||
                    map_[x][y].GetType() == Cell::CellType::CAPITAL) {
                    output += "1\n";
                } else {
                    output += "2\n";
                }
            }
        }
    }
    return output;
}

bool Map::IsIn(int x, int y) const {
    return 0 <= x && x < static_cast<int>(n_) && 0 <= y && y < static_cast<int>(m_);
}

void Map::DestroyPlayer(size_t player_id, size_t new_owner) {
    for (size_t x = 0; x < n_; ++x) {
        for (size_t y = 0; y < m_; ++y) {
            if (map_[x][y].GetOwner() == player_id) {
                if (!new_owner) {
                    if (map_[x][y].GetType() == Cell::CellType::CAPITAL) {
                        map_[x][y].GetType() = Cell::CellType::CITY;
                    }
                } else {
                    map_[x][y].GetArmySize() += 1;
                    map_[x][y].GetArmySize() /= 2;
                }
                map_[x][y].GetOwner() = new_owner;
            }
        }
    }
}

size_t Map::GetPlayers() const {
    return players_;
}