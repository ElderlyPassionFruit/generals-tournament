#include "Cell.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <utility>
#include <vector>

using namespace std;

void dfs(int x, int y, int n, int m, vector<vector<bool>>& used) {
    static const vector<int> dx = {0, 1, 0, -1};
    static const vector<int> dy = {1, 0, -1, 0};
    auto IsIn = [&](int x, int y) -> bool { return 0 <= x && x < n && 0 <= y && y < m; };
    used[x][y] = true;
    for (int it = 0; it < 4; ++it) {
        int nx = x + dx[it];
        int ny = y + dy[it];
        if (!IsIn(nx, ny)) {
            continue;
        }
        if (used[nx][ny]) {
            continue;
        }
        dfs(nx, ny, n, m, used);
    }
}

bool IsConnect(const vector<vector<Cell::CellType>>& map) {
    int n = map.size();
    int m = map[0].size();
    vector<vector<bool>> used(n, vector<bool>(m));
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (map[x][y] == Cell::CellType::MOUNTAINS) {
                used[x][y] = true;
            }
        }
    }
    int components = 0;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (used[x][y]) {
                continue;
            }
            if (map[x][y] == Cell::CellType::MOUNTAINS) {
                continue;
            }
            dfs(x, y, n, m, used);
            ++components;
        }
    }
    return components == 1;
}

void TryAddMountains(vector<vector<Cell::CellType>>& map, int x, int y) {
    map[x][y] = Cell::CellType::MOUNTAINS;
    if (!IsConnect(map)) {
        map[x][y] = Cell::CellType::EMPTY;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Incorrect number of arguments" << endl;
        exit(EXIT_FAILURE);
    }
    int n = stoi(argv[1]);
    int m = stoi(argv[2]);
    int k = stoi(argv[3]);
    if (n * m < k) {
        cout << "The number of players must be less than or equal to the size of the map" << endl;
        exit(EXIT_FAILURE);
    }
    mt19937 rnd(179);
    auto gen = [&](int l, int r) -> int {
        return static_cast<unsigned long long>(rnd()) % (r - l + 1) + l;
    };
    vector<vector<Cell::CellType>> map(n, vector<Cell::CellType>(m, Cell::CellType::UNKNOWN));
    vector<pair<int, int>> candidates;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            candidates.emplace_back(x, y);
        }
    }
    shuffle(candidates.begin(), candidates.end(), rnd);
    candidates.resize(k);
    for (auto [x, y] : candidates) {
        map[x][y] = Cell::CellType::CAPITAL;
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (map[x][y] != Cell::CellType::UNKNOWN) {
                continue;
            }
            int type = gen(1, 100);
            if (type <= 70) {
                map[x][y] = Cell::CellType::EMPTY;
            } else if (type <= 90) {
                TryAddMountains(map, x, y);
            } else {
                map[x][y] = Cell::CellType::CITY;
            }
        }
    }
    cout << n << " " << m << " " << k << endl;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cout << map[x][y];
            if (map[x][y] == Cell::CellType::CITY) {
                cout << " " << gen(35, 55);
            }
            cout << endl;
        }
    }
}