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


int main(){
    
    ifstream fin = ifstream("inputs/day17.txt", std::ios::in);
    string s;

    getline(fin, s);

    using Uint = uint32_t;
    
    vector<Uint> one(1, 
        (Uint)strtoul("00000000000011110000000000000000", nullptr, 2));

    vector<Uint> two{ 
        (Uint)strtoul("00000000000001000000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000011100000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000001000000000000000000", nullptr, 2)};

    vector<Uint> three{ 
        (Uint)strtoul("00000000000000100000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000000100000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000011100000000000000000", nullptr, 2)};

    vector<Uint> four{ 
        (Uint)strtoul("00000000000010000000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000010000000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000010000000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000010000000000000000000", nullptr, 2)};

    vector<Uint> five{ 
        (Uint)strtoul("00000000000011000000000000000000", nullptr, 2),
        (Uint)strtoul("00000000000011000000000000000000", nullptr, 2)};

    const vector<vector<Uint>> pieces = {one, two, three, four, five};

    const Uint row = Uint(strtoul("11111111110000000111111111111111", nullptr, 2));

    vector<Uint> tower;
    tower.reserve(10000);
    tower.push_back(((1ull << 31) - 1ull) | (1ull << 31));
    tower.resize(10, row);
    int pad = 100;
    int last = 0;
    int mv = 0;

    const int moves = s.length();

    auto print = [&](){
        for(int i=tower.size()-1; i >= 0; --i){
            for(int j=0; j < 32; ++j){
                cout << ((tower[i] & (1 << j)) ? '#' : '.');
            }
            cout << endl;
        }
        cout << endl;
    };

    const long long LEN = s.length() * 5;
    vector<int> rounds;
    vector<long long> heights(400000000, -1); 

    for (int _ = 0; _ < LEN * 2000; ++_){
    
        auto piece = pieces[_ % 5];
        int ln = piece.size();
        int start = last + 3 + ln;
        if (start >= tower.size()){
            tower.resize(start + pad, row);
        }

        while(true){
            auto c = s[mv ++];
            if (mv == moves) mv = 0;

            if (c == '<'){
                int i = 0;
                for (int j=start; i < ln; ++i, --j){
                    if (tower[j] & (piece[i] << 1)){
                        break;
                    }
                }
                if (i == ln){
                    for(auto& p : piece){
                        p <<= 1;
                    }
                }
            } else if (c == '>'){
                int i = 0;
                for (int j=start; i < ln; ++i, --j){
                    if (tower[j] & (piece[i] >> 1)){
                        break;
                    }
                }
                if (i == ln){
                    for(auto& p : piece){
                        p >>= 1;
                    }
                }
            }
            
            int i=0;
            for(; i < ln; ++i){
                if(tower[start - i - 1] & piece[i]){
                    break;
                }
            }

            if(i == ln){
                --start;
            } else {
                for(int i=0; i < ln; ++i){
                    tower[start - i] |= piece[i];
                }
                
                if (start > last){
                    last = start;
                    rounds.resize(start + 1, _);
                }
                heights[_] = last;
                break;
            }
        }
    }

    cout << last << endl;

    long long period;
    for (int i = 1900; i > 600; --i){
        bool eq = equal(tower.begin() + last - 20000, 
                        tower.begin() + last,
                        tower.begin() + last - 20000 - LEN * i);

        if (eq){
            cout << "found" << " " << i << endl;
            period = i * LEN;
            break;
        }
    }

    int k = rounds[last] - rounds[last - period];
    assert(heights[LEN*500] + period == heights[LEN*500 + k]);

    long long request = 1000000000000;

    long long times = (request - rounds[last]) / k;

    long long res = last + times * period;

    long long diff = request - rounds[last] - times * k;
    
    cout << (res + (heights[last - period + diff] - heights[last-period])) << endl;

    fin.close();
    return 0;
}
