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
    
    ifstream fin = ifstream("inputs/day16.txt", std::ios::in);
    string s;
    char S[8][9];
    char t[3];

    vector<vector<int>> gr(50);
    std::map<string, int> pipes;
    vector<int> pressure(50, 0);
    int cnt{0};
    int SOURCE = -1;

    while(getline(fin, s)){
        int pres;

        int n = sscanf(s.c_str(), 
            "Valve %s has flow rate=%d; %s %s to %s %s %s %s %s %s", 
            t, &pres,
            S[0], S[1], S[2], S[3], S[4], S[5], S[6], S[7]);
        
        if (pipes.find(t) == pipes.end()){
            pipes[t] = cnt++;
        }
        pressure[pipes[t]] = pres;
        if (strcmp(t, "AA") == 0) SOURCE = pipes[t];

        for(int i = 3; i < n-2; ++ i){
            S[i][2] = 0;
            if (pipes.find(S[i]) == pipes.end()){
                pipes[S[i]] = cnt++;
            }
            gr[pipes[t]].push_back(pipes[S[i]]);
        }
    }

    using pii = std::pair<int, int>;

    vector<vector<int>> Dist(cnt, vector<int>(cnt, 1e9));

    for (int source = 0; source < cnt; ++ source){
        std::set<pii> q;
        vector<int> dist(cnt, 1e9);
        vector<int> par(cnt, -1);
        dist[source] = 0;

        for(int i = 0; i < cnt; ++ i){
            q.insert({dist[i], i});
        }

        while (not q.empty()){
            int u = q.begin()->second;
            q.erase(q.begin());

            for(int v : gr[u]){
                int alt = dist[u] + 1;
                if (dist[v] > alt){
                    q.erase({dist[v], v});
                    par[v] = u;
                    dist[v] = alt;
                    q.insert({dist[v], v});
                }
            }
        }

        copy(dist.begin(), dist.end(), Dist[source].begin());
    }


    vector<vector<int>> Gr(cnt);
    vector<int> bag(1, SOURCE);

    for (int i = 0; i < cnt; ++ i){
        if (pressure[i] > 0){
            for(int j : bag){
                if (j != 0){
                    Gr[i].push_back(j);
                    Gr[j].push_back(i);
                }
            }
            bag.push_back(i);
            if (Dist[SOURCE][i] < cnt)
                Gr[SOURCE].push_back(i);
        }
    }
    

    

    for(int i: bag){
        sort(Gr[i].begin(), Gr[i].end(), [&](int a, int b){
            return Dist[i][a] < Dist[i][b];
        });
    }

    int mx=-1;
    
    std::function<void(int, int, long long, int, bool)> go = [&](int u, int sm, long long visited, int left_time, bool first){
        visited |= (1LL << u);

        for (int v: Gr[u]){
            if((left_time - Dist[u][v] - 1 <= 0)) break;
            if (visited & (1LL << v)) continue;
            go(v, sm + pressure[v] * (left_time-1-Dist[u][v]),visited, left_time - Dist[u][v] - 1, first);
        }

        if (first)
            go(SOURCE, sm, visited, 26, false);
        else 
            mx = std::max(mx, sm);
    };

    go(SOURCE, 0, 0LL, 26, true);

    cout << mx << endl;

    fin.close();
    return 0;
}
