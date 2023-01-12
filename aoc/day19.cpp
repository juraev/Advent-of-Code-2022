
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
    
    ifstream fin = ifstream("inputs/day19.txt", std::ios::in);
    string s;

    int res{};


    while(getline(fin, s)){
        int ore_or, clay_or, obsidian_or, obsidian_c, geode_or, geode_o;
        int blueprint;

        sscanf(s.c_str(), 
            "Blueprint %d: Each ore robot costs %d ore. Each clay robot costs %d ore. Each obsidian robot costs %d ore and %d clay. Each geode robot costs %d ore and %d obsidian.", 
                &blueprint, &ore_or, &clay_or, &obsidian_or, &obsidian_c, &geode_or, &geode_o);
            
        

        using pii = std::pair<int, int>;
        int mx = 0;
        int cnt = 0;

        // int8_t cache[8][15][8][15][8][15][25];

        auto comp = [](vector<int> a, vector<int> b){
            for(int i = 0; i < a.size(); i ++){
                if (a[i] < b[i]) return true;
                if (a[i] > b[i]) return false;
            }
            return false;
        };

        map<vector<int>, uint8_t, decltype(comp)> CACHE;


        std::function<int(pii, pii, pii, pii, int)> rec = [&](pii ore, pii clay, pii obsidian, pii geode, int time) -> int{
            // cout << ore.first << " " << ore.second << " " << clay.first << " " << clay.second << " " << obsidian.first << " " << obsidian.second << " " << geode.first << " " << geode.second << " " << time << endl;
            if (time == 25){
                return  geode.second;
            }

            if(ore.first < 16 && ore.second < 30 && clay.first < 15 && clay.second < 30 && obsidian.first < 16 && obsidian.second < 30)
            if (CACHE.find({ore.first, ore.second, clay.first, clay.second, obsidian.first, obsidian.second, 25-time}) != CACHE.end()){
                int res = (25-time) * geode.first + geode.second + CACHE[{ore.first, ore.second, clay.first, clay.second, obsidian.first, obsidian.second, 25-time}];
                return res;
            }
            

            int geode_ = std::min(obsidian.second/geode_o, ore.second/geode_or);

            int MX = 0;

            for(int i = 0; i <= geode_; i ++){

                int obsidian_ = std::min(clay.second/obsidian_c, (ore.second - i * geode_or)/obsidian_or);

                for(int j = 0; j <= obsidian_; j ++){

                    int clay_ = (ore.second - i * geode_or - j * obsidian_or)/clay_or;

                    for(int k = 0; k <= clay_; k ++){

                        int ore_ = (ore.second - i * geode_or - j * obsidian_or - k * clay_or)/ore_or;

                        for(int l = 0; l <= ore_; l ++){
                            
                            
                            // cout << "ore: " << l << " clay: " << k << " obsidian: " << j << " geode: " << i << endl;
                            int ore__ = (ore.second - i * geode_or - j * obsidian_or - k * clay_or - l * ore_or) + ore.first;
                            int clay__ = (clay.second - j * obsidian_c) + clay.first;
                            int obsidian__ = (obsidian.second - i * geode_o) + obsidian.first;
                            int geode__ = (geode.second) + geode.first;

                            MX = std::max(rec({ore.first + l, ore__}, 
                                {clay.first + k, clay__}, 
                                {obsidian.first + j, obsidian__}, 
                                {geode.first + i, geode__}, 
                                time + 1), MX);
                        }
                    }
                }
            }

            if(ore.first < 16 && ore.second < 30 && clay.first < 15 && clay.second < 30 && obsidian.first < 16 && obsidian.second < 30)
            CACHE[{ore.first, ore.second, clay.first, clay.second, obsidian.first, obsidian.second, 25-time}] = MX - (25-time) * geode.first - geode.second;

            return MX;
        };

        
        mx = rec({1, 0}, {0, 0}, {0, 0}, {0, 0}, 0);
        
        res += blueprint * mx;


        cout << blueprint << " " << mx << endl;
    }

    cout << res << endl;
    
    
    fin.close();
    return 0;
}