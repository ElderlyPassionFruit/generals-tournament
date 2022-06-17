#pragma once

#include <cstdlib>
#include <string>

struct Coordinates {
    int x, y;
    Coordinates() : x(0), y(0) {
    }
    Coordinates(int x_, int y_) : x(x_), y(y_) {
    }
};

int Dist(const Coordinates& lhs, const Coordinates& rhs);

class Cell {
public:
    enum CellType { UNKNOWN, EMPTY, CITY, CAPITAL, MOUNTAINS };

    Cell() = default;

    Cell(CellType type, size_t owner, size_t army_size)
        : type_(type), owner_(owner), army_size_(army_size) {
    }

    CellType& GetType() {
        return type_;
    }

    size_t& GetOwner() {
        return owner_;
    }

    size_t& GetArmySize() {
        return army_size_;
    };

    CellType GetType() const {
        return type_;
    }

    size_t GetOwner() const {
        return owner_;
    }

    size_t GetArmySize() const {
        return army_size_;
    };

private:
    CellType type_ = UNKNOWN;
    size_t owner_ = 0;
    size_t army_size_ = 0;
};