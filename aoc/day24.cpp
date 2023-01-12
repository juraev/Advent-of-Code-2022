
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <bit>
#include <map>
#include <set>
#include <functional>
#include <ranges>
#include <string_view>
#include <sstream>
#include <list>
#include <numeric>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;
using std::stoi;
using std::swap;
using std::min;

using vll = vector<long long>;

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main(){
    
    ifstream fin = ifstream("inputs/day24.txt", std::ios::in);
    string s;
    using pii = std::pair<int, int>;

    auto newTable = [](int u, int v){
        vector<string> new_table(u, string(v, '.'));
        for(int i = 0; i < v; ++i){
            new_table[0][i] = '#';
            new_table[u - 1][i] = '#';
        }

        for(int i = 0; i < u; ++i){
            new_table[i][0] = '#';
            new_table[i][v - 1] = '#';
        }

        new_table[0][1] = new_table[u - 1][v - 2] = '.';
        return move(new_table);
    };

    vector<std::pair<pii, char>> blizzards;
    vector<string> table;

    int row{};
    while(getline(fin, s)){
        int col{};
        table.push_back(s);

        for (auto& c : s){
            if (c != '.' and c != '#'){
                blizzards.push_back({{row, col}, c});
            }
            ++ col;
        }
        ++ row;
    }

    int n = table.size();
    int m = table[0].size();

    vector<std::pair<pii, int>> reached;
    reached.push_back({{0, 1}, 0});
    int res{};
    int travel{1};

    int rounds = (n - 2) * (m - 2) / gcd(n - 2, m - 2);
    for (int i = 0; i < 10 * rounds; ++ i){

        auto new_table = newTable(n, m);

        for (auto& [pos, c] : blizzards){
            int& x = pos.first;
            int& y = pos.second;

            if (c == '<'){
                if (y == 1){
                    y = m - 1;
                }
                -- y;
            } else if (c == '>'){
                if (y == m - 2){
                    y = 0;
                }
                ++ y;
            } else if (c == '^'){
                if (x == 1){
                    x = n - 1;
                }
                -- x;
            } else if (c == 'v'){
                if (x == n - 2){
                    x = 0;
                }
                ++ x;
            }
            
            new_table[x][y] = (new_table[x][y] == '.' ? c : '2');
        }

        map<pii, int> new_reached;

        for(auto [pos, steps] : reached){
            int x = pos.first;
            int y = pos.second;

            if (new_table[x][y] == '.'){
                if (new_reached.find(pos) == new_reached.end()){
                    new_reached[pos] = steps + 1;
                } else {
                    new_reached[pos] = min(new_reached[pos], steps + 1);
                }
            }

            if (x > 0 and new_table[x - 1][y] == '.'){
                if (new_reached.find({x - 1, y}) == new_reached.end()){
                    new_reached[{x - 1, y}] = steps + 1;
                } else {
                    new_reached[{x - 1, y}] = min(new_reached[{x - 1, y}], steps + 1);
                }
            }

            if (x < n - 1 and new_table[x + 1][y] == '.'){
                if (new_reached.find({x + 1, y}) == new_reached.end()){
                    new_reached[{x + 1, y}] = steps + 1;
                } else {
                    new_reached[{x + 1, y}] = min(new_reached[{x + 1, y}], steps + 1);
                }
            }

            if (new_table[x][y - 1] == '.'){
                if (new_reached.find({x, y - 1}) == new_reached.end()){
                    new_reached[{x, y - 1}] = steps + 1;
                } else {
                    new_reached[{x, y - 1}] = min(new_reached[{x, y - 1}], steps + 1);
                }
            }

            if (new_table[x][y + 1] == '.'){
                if (new_reached.find({x, y + 1}) == new_reached.end()){
                    new_reached[{x, y + 1}] = steps + 1;
                } else {
                    new_reached[{x, y + 1}] = min(new_reached[{x, y + 1}], steps + 1);
                }
            }

        }

        reached.clear();

        if (travel == 1 and new_reached.find({n - 1, m - 2}) != new_reached.end()){
            reached.push_back({{n - 1, m - 2}, new_reached[{n - 1, m - 2}]});
            ++ travel;
            continue;
        }

        if (travel == 2 and new_reached.find({0, 1}) != new_reached.end()){
            reached.push_back({{0, 1}, new_reached[{0, 1}]});
            ++ travel;
            continue;
        }

        if (travel == 3 and new_reached.find({n - 1, m - 2}) != new_reached.end()){
            // reached.push_back({{n - 1, m - 2}, new_reached[{n - 1, m - 2}]});
            // ++ travel;
            cout << new_reached[{n - 1, m - 2}];
            break;
        }

        
        for (auto& [pos, steps] : new_reached){
            reached.push_back({pos, steps});
        }
    }


    fin.close();
    return 0;
}