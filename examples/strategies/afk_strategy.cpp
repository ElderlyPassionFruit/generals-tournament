#include <iostream>
#include <vector>
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

int main() {
    ios_base::sync_with_stdio(NULL);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n >> m >> k >> id;
    stat.resize(k);
    info.resize(n, vector<Cell>(m));
    while (true) {
        input();
        output_afk();
    }
}