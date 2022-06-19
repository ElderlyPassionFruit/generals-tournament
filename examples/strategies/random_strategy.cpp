#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#include <algorithm>
#include <cassert>

using namespace std;

enum CellType { UNKNOWN, EMPTY, CITY, CAPITAL, MOUNTAINS };

struct Cell {
    int visible;
    CellType type;
    int owner;
    int army_size;
};

struct Statistics {
    int total_army;
    int total_fields;
};

void output_afk() {
    cout << -1 << endl;
}

void output_move(int type, int x1, int y1, int x2, int y2) {
    cout << type << " " << x1 + 1 << " " << y1 + 1 << " " << x2 + 1 << " " << y2 + 1 << endl;
}

int n, m, k, id;
vector<Statistics> stat;
vector<vector<Cell>> info;

void input() {
    int alive;
    cin >> alive;
    if (!alive) {
        exit(0);
    }
    for (auto& [total_army, total_fields] : stat) {
        cin >> total_army >> total_fields;
    }
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            auto& cell = info[x][y];
            int value;
            cin >> cell.visible >> value;
            assert(value >= 1 && value <= 4);
            cell.type = static_cast<CellType>(value);
            cell.owner = 0;
            cell.army_size = 0;
            if (cell.visible && cell.type != MOUNTAINS) {
                cin >> cell.owner >> cell.army_size;
            }
        }
    }
}

mt19937 rnd(123);

void random_move() {
    vector<pair<int, int>> cells;
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            if (info[x][y].owner == id) {
                cells.emplace_back(x, y);
            }
        }
    }
    shuffle(cells.begin(), cells.end(), rnd);
    int x = cells[0].first;
    int y = cells[0].second;
    vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    shuffle(dirs.begin(), dirs.end(), rnd);
    for (auto [dx, dy] : dirs) {
        if (abs(dx) + abs(dy) != 1)
            continue;
        int nx = x + dx;
        int ny = y + dy;
        if (0 <= nx && nx < n && 0 <= ny && ny < m && info[nx][ny].type != MOUNTAINS) {
            output_move((unsigned long long)rnd() % 2 + 1, x, y, nx, ny);
            return;
        }
    }
    output_afk();
}

int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> k >> id;
    stat.resize(k);
    info.resize(n, vector<Cell>(m));
    while (true) {
        input();
        random_move();
    }
}