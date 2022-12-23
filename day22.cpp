
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


int main(){
    
    ifstream fin = ifstream("inputs/day22.txt", std::ios::in);
    string s;

    vector<string> map;
    bool done = false;

    size_t n{}, m{};
    int W = 50;

    while(getline(fin, s)){
        done |= (s.empty());
        if (not done){
            m = std::max(m, s.length());
            map.push_back(string(W, ' ') + ' ' + s + ' ');
            map.back().resize(4 * W + 2, ' ');
            ++ n;
        }
    }

    std::reverse(map.begin(), map.end());
    map.push_back(string(4 * W + 2, ' '));
    std::reverse(map.begin(), map.end());
    map.push_back(string(4 * W + 2, ' '));

    for (int i = 1; i <= W; ++i){
        std::copy(map[i].begin() + 3 * W + 1, 
                    map[i].begin() + 4 * W + 1, 
                    map[3 * W + 1 - i].rbegin() + 1);
        std::fill(map[i].begin() + 3 * W + 1, 
                    map[i].begin() + 4 * W + 1, ' ');
    }

    for (int i = W + 1; i <= 2 * W; ++i){

        for (int j = 1; j <= 2 * W; ++j){
            map[i][j] = map[4 * W + 1 - j][i];
            map[4 * W + 1 - j][i] = ' ';
        }
    }

    n = 3 * W;
    m = 4 * W;


    vector<vector<int>> br(n + 1, vector<int>(2, 0));
    vector<vector<int>> bc(m + 1, vector<int>(2, 0));
    
    for (int j = 1; j <= n; ++ j){
        map[j].resize(m + 2, ' ');

        int i = 0;
        while(map[j][i] == ' ') ++i;

        br[j][0] = i;

        while(map[j][i] != ' ') ++i;
        br[j][1] = i - 1;
    }

    for (int i = 1; i <= m; ++ i){

        int j = 0;
        while(map[j][i] == ' ') ++j;

        bc[i][0] = j;

        while(map[j][i] != ' ') ++j;
        bc[i][1] = j - 1;
    }

    std::stringstream ss(s);

    int dir[2] = {0, 1};
    int x = 1;
    int y = br[1][0];

    int d;
    char c;

    while(true){
        ss >> d;

        for (int i = 0; i < d; ++ i){
            if (map[x + dir[0]][y + dir[1]] == '#'){
                break;
            }
            
            if (map[x + dir[0]][y + dir[1]] == ' '){
                // if (dir[0] == 0 && map[x][br[x][dir[1] != 1]] != '#'){
                //     y = br[x][dir[1] != 1];
                // }
                // if (dir[1] == 0 && map[bc[y][dir[0] != 1]][y] != '#'){
                //     x = bc[y][dir[0] != 1];
                // }

                if (x <= W){
                    if (dir[1] == 1 && map[3 * W + 1 - x][4 * W] != '#'){
                        dir[1] = -1;
                        y = 4 * W;
                        x = 3 * W + 1 - x;
                    } else if (dir[1] == -1 && map[W + 1][W + x] != '#'){
                        dir[0] = 1;
                        dir[1] = 0;
                        y = W + x;
                        x = W + 1;
                    } else if (dir[0] == -1 && map[W + 1][3 * W + 1 - y] != '#'){
                        dir[0] = 1;
                        y = 3 * W + 1 - y;
                        x = W + 1;
                    }
                } else if (y <= W){
                    if (dir[1] == -1 && map[3 * W][5 * W + 1 - x] != '#'){
                        dir[1] = 0;
                        dir[0] = -1;
                        y = 5 * W + 1 - x;
                        x = 3 * W;
                    } else if (dir[0] == -1 && map[1][3 * W + 1 - y] != '#'){
                        dir[0] = 1;
                        x = 1;
                        y = 3 * W + 1 - y;
                    } else if (dir[0] == 1 && map[3 * W][3 * W + 1 - y] != '#'){
                        dir[0] = -1;
                        x = 3 * W;
                        y = 3 * W + 1 - y;
                    }
                } else if (y <= 2 * W) {
                    if (dir[0] == 1 && map[4 * W + 1 - y][2 * W + 1] != '#'){
                        dir[0] = 0;
                        dir[1] = 1;
                        x = 4 * W + 1 - y;
                        y = 2 * W + 1;
                        
                    } else if (dir[0] == -1 && map[y - W][2 * W + 1] != '#'){
                        dir[0] = 0;
                        dir[1] = 1;
                        x = y - W;
                        y = 2 * W + 1;
                    }
                } else if (y <= 3 * W) {
                    if (dir[1] == 1 && map[2 * W + 1][5 * W + 1 - x] != '#'){
                        dir[1] = 0;
                        dir[0] = 1;
                        y = 5 * W + 1 - x;
                        x = 2 * W + 1;

                    } else if (dir[1] == -1 && map[2 * W ][4 * W + 1 - x] != '#'){
                        dir[1] = 0;
                        dir[0] = -1;
                        y = 4 * W + 1 - x;
                        x = 2 * W ;
                    } else if (dir[0] == 1 && map[2 * W ][3 * W + 1 - y] != '#'){
                        dir[0] = -1;
                        x = 2 * W ;
                        y = 3 * W + 1 - y;
                    }
                } else {
                    if (dir[0] == 1 && map[5 * W + 1 - y][1] != '#'){
                        dir[0] = 0;
                        dir[1] = 1;
                        x = 5 * W + 1 - y;
                        y = 1;
                    } else if (dir[0] == -1 && map[5 * W - y + 1][3 * W] != '#'){
                        dir[0] = 0;
                        dir[1] = -1;
                        x = 5 * W - y + 1;
                        y = 3 * W;
                    } else if (dir[1] == 1 && map[3 * W + 1 - x][3 * W] != '#'){
                        dir[1] = -1;
                        x = 3 * W + 1 - x;
                        y = 3 * W;
                    }
                }

            } else {
                x += dir[0];
                y += dir[1];
            }
        }


        if (ss >> c){
            if (c == 'L'){
                swap(dir[0], dir[1]);
                dir[0] *= -1;
            }
            if (c == 'R'){
                swap(dir[0], dir[1]);
                dir[1] *= -1;
            }
        } else {
            break;
        }
    }

    y -= W;

    cout << x << ' ' << y << endl;
    cout << dir[0] << ' ' << dir[1] << endl;

    int D = dir[1] == 1 ? 0 : (dir[0] == 1 ? 1 : (dir[1] == -1 ? 2 : 3));

    cout << (x * 1000 + 4 * y + D) << endl;





    fin.close();
    return 0;
}