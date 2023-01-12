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
    
    ifstream fin = ifstream("inputs/day18.txt", std::ios::in);
    string s;

    int res{};
    vector<vector<int>> v;
    std::set<std::pair<int, std::pair<int, int>>> cubes;
    std::map<std::pair<int, std::pair<int, int>>, int> cands;


    while(getline(fin, s)){

        int x, y, z;

        sscanf(s.c_str(), "%d,%d,%d", &x, &y, &z);

        res += 6;

        for(auto& a: v)
            if((a[0] == x && a[1] == y && abs(a[2]-z)==1) 
                || (a[0] == x && a[2] == z && abs(a[1]-y)==1)
                || (a[1] == y && a[2] == z && abs(a[0]-x)==1))
                res -= 2;

        cands[{x, {y, z}}] = -1000;
        cubes.insert({x, {y, z}});

        cands[{x-1, {y, z}}] += 1;
        cands[{x+1, {y, z}}] += 1;
        cands[{x, {y-1, z}}] += 1;
        cands[{x, {y+1, z}}] += 1;
        cands[{x, {y, z-1}}] += 1;
        cands[{x, {y, z+1}}] += 1;

        v.push_back({x, y, z});
    }
    
    while (not cands.empty()){
        auto it = cands.begin();
        auto a = *it;

        if (a.second < 1){
            cands.erase(a.first);
            continue;
        }
        
        std::queue<std::pair<std::pair<int, std::pair<int, int>>, int>> q;
        std::set<std::pair<int, std::pair<int, int>>> visited;
        visited.insert(a.first);
        q.push(a);
        cands.erase(a.first);

        int k{};
        int cnt{};

        while(not q.empty()){
            auto [b, c] = q.front();
            q.pop();
                
            if (cnt > 10000){
                k = 0;
                break;
            }

            k += c;
            
            vector<std::pair<int, std::pair<int, int>>> P = {
                {b.first-1, {b.second.first, b.second.second}}, 
                {b.first+1, {b.second.first, b.second.second}},
                {b.first, {b.second.first-1, b.second.second}},
                {b.first, {b.second.first+1, b.second.second}},
                {b.first, {b.second.first, b.second.second-1}},
                {b.first, {b.second.first, b.second.second+1}}
            };
            
            for (auto p: P){
                if (cubes.find(p) != cubes.end())
                    continue;
                if (visited.find(p) != visited.end())
                    continue;
                auto it = cands.find(p);
                if (it != cands.end()){
                    q.push({p, it->second});
                    cands.erase(p);
                } else {
                    q.push({p, 0});
                    cnt ++;
                }
                visited.insert(p);
            }
        }

        res -= k;

    }


    cout << res << endl;
    
    fin.close();
    return 0;
}
