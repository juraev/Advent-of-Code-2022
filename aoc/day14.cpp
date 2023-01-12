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

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;
using std::stoi;


int main(){
    
    ifstream fin = ifstream("inputs/day14.txt", std::ios::in);
    string s, t;

    vector<vector<std::pair<int, int>>> coords;
    int mnx, mxx, mny, mxy;
    mxx = mxy = -1000;
    mnx = mny = 1000;

    while(getline(fin, s)){

        s += " -> ";
        
        string_view sv(s);

        int pos, x, y;
        int prevx{-1};
        int prevy{-1};
        coords.push_back({});

        while(sv.length() > 4){
            pos = sv.find_first_of(" -> ");
            int pos1 = sv.find_first_of(",");
            x = stoi(sv.substr(0, pos1).data());
            y = stoi(sv.substr(pos1 + 1, pos - pos1 - 1).data());
            sv.remove_prefix(pos + 4);
            coords.back().push_back({x, y});
            mnx = std::min(mnx, x);
            mxx = std::max(mxx, x);
            mny = std::min(mny, y);
            mxy = std::max(mxy, y);
        }
    }

    mnx -= 300;
    mxx += 300;
    mxy += 2;
    coords.push_back({{mnx, mxy}, {mxx, mxy}});

    vector<string> v(mxy + 1, string(mxx - mnx + 1, '.'));
    int padx = -mnx;
    int pady = 0;
    
    for(auto& c : coords){
        
        int n = c.size();

        for(int i = 1; i < n; ++ i){

            int x1 = c[i - 1].first;
            int y1 = c[i - 1].second;
            int x2 = c[i].first;
            int y2 = c[i].second;

            int dx = x2 - x1;
            int dy = y2 - y1;

            if(dx == 0){
                for(int j = std::min(y1, y2); j <= std::max(y1, y2); ++ j){
                    v[j+pady][x1+padx] = '#';
                }
            }else{
                for(int j = std::min(x1, x2); j <= std::max(x1, x2); ++ j){
                    v[y1+pady][j+padx] = '#';
                }
            }
        }
    }

    int cnt{};

    while(true){
        int posx = 500 + padx;
        int posy = 0 + pady;
        int t{};

        while(posy < v.size() - 1 and posx < v[0].size()-1 and posx > 0){
            
            if (v[posy + 1][posx] == '.'){

            } else if (v[posy + 1][posx - 1] == '.'){
                posx --;
            } else if (v[posy + 1][posx + 1] == '.'){
                posx ++;
            } else {
                cnt ++;
                v[posy][posx] = 'o';
                break;
            }
            
            posy ++;
            t ++;
        }

        if(t == 0) break;


        if (not (posy < v.size() - 1 and posx < v[0].size()-1 and posx > 0)){
            cout << posx << " " << posy << endl;
            break;
        }
    }

    cout << cnt << endl;


    fin.close();
    return 0;
}
