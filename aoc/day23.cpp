
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
    
    ifstream fin = ifstream("inputs/day23.txt", std::ios::in);
    string s;

    using pii = std::pair<int, int>;

    std::set<pii> elfs;
    int row{};

    while(getline(fin, s)){
        int col{};

        for(auto& c : s){
            if (c == '#'){
                elfs.insert({row, col});
            }
            ++col;
        }
        ++row;
    }

    vector<vector<int>> dirs{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    int round{1};
    int n = elfs.size();
    int choice = 0;

    vector<vector<int>> neig(3, vector<int>(3));

    cout << elfs.size() << endl;


    while (true){
        vector<std::pair<pii, pii>> suggestions;

        // for (auto elf : elfs){
        //     cout << elf.first << " " << elf.second << endl;
        // }
        // cout << endl;

        int cnt{};
        for(auto elf : elfs) {

            for (size_t i = 0; i < 3; i++)
                std::fill(neig[i].begin(), neig[i].end(), 0);
            
            
            for(int i = elf.first - 1; i <= elf.first + 1; ++i){
                for(int j = elf.second - 1; j <= elf.second + 1; ++j){
                    if (i == elf.first && j == elf.second) continue;
                    if (elfs.find({i, j}) != elfs.end()) {
                        ++ neig[i - elf.first + 1][j - elf.second + 1];
                    }
                }
            }

            if (std::all_of(neig.begin(), neig.end(), 
                    [](vector<int> x){
                        return std::all_of(x.begin(), x.end(), 
                            [](int y){
                                return y == 0;
                            });
                    })){
                suggestions.push_back({elf, elf});
                cnt ++;
                continue;
            }

            for (int c = choice; c < choice + 4; ++c){
                int i = dirs[c & 3][0];
                int j = dirs[c & 3][1];

                vector<vector<int>> check;
                
                if (i == 0)
                    check = {{i-1, j}, {i, j}, {i+1, j}};
                else 
                    check = {{i, j-1}, {i, j}, {i, j+1}};
                

                if (std::all_of(check.begin(), check.end(), 
                    [&](auto& x){
                        return neig[x[0] + 1][x[1] + 1] == 0;
                    })){
                    suggestions.push_back({{i + elf.first, j + elf.second}, elf});
                    break;
                }
            }
            if(suggestions.back().second != elf){
                suggestions.push_back({elf, elf});
            }
        }

        if (cnt == elfs.size()){
            cout << "Part 1: " << round << endl;
            break;
        }
        
        sort(suggestions.begin(), suggestions.end());

        suggestions.push_back({{1e9, 1e9}, {0, 0}});

        elfs.clear();

        for (int i = 0; i < suggestions.size() - 1;){
            auto [sug, elf] = suggestions[i];
            
            int j = i;

            while(suggestions[j + 1].first == sug){
                ++j;
            }

            if (j == i){
                // cout << elf.first << " _ " << elf.second << endl;
                // cout << sug.first << " - " << sug.second << endl;
                elfs.insert(sug);
                ++ j;
            } else {
                j = i;
                do {
                    // cout << suggestions[j].second.first << " " << suggestions[j].second.second << endl;
                    elfs.insert(suggestions[j ++].second);
                } while(suggestions[j].first == sug);
            }
            // cout << i << " => " << j + 1 << endl;
            i = j;
        }

        // cout << elfs.size() << endl;

        if (round % 10 == 0){
            
            int mxx = 0, mxy = 0, mnx = 1e9, mny = 1e9;

            for (auto [x, y] : elfs){
                mxx = std::max(mxx, x);
                mxy = std::max(mxy, y);
                mnx = std::min(mnx, x);
                mny = std::min(mny, y);
            }

            cout << ((mxx - mnx + 1) * (mxy - mny + 1) - elfs.size()) << endl;
            // break;
        }

        // vector<string> table(12, string(14, '.'));

        // for (auto [x, y] : elfs){
        //     table[x][y] = '#';
        // }

        // cout << elfs.size() << endl;

        // for (auto& s : table){
        //     cout << s << endl;
        // }
        // cout << endl;


        (++ choice) &= 3;
        ++ round;
    }



    

    
    
    

    fin.close();
    return 0;
}