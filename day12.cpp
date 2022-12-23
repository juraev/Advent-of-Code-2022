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
    
    ifstream fin = ifstream("inputs/day12.txt", std::ios::in);
    string s, t;

    vector<vector<int>> graph;
    std::queue<std::pair<int, int>> queue;
    std::bitset<4000> visited;

    int row = 0, column;
    int n{}, m;
    int start{}, end{};
    int cur{};

    while(getline(fin, s)){
        m = s.length();
        column = 0;
        graph.resize(row * m + m);
        for (auto & c : s){
            if (c == 'S' or c == 'a'){
            // if (c == 'S'){
                start = cur, c = 'a';
                queue.push({start, 0});
                visited.set(start);
            }
            if (c == 'E')
                end = cur, c = 'z';

            if (column > 0 and (s[column-1] - c) <= 1)
                graph[cur].push_back(cur - 1);
            if (column > 0 and (s[column-1] - c) >= -1)
                graph[cur - 1].push_back(cur); 
            
            if (row > 0 and (t[column] - c) <= 1)
                graph[cur].push_back(cur - m);
            if (row > 0 and (t[column] - c) >= -1)
                graph[cur - m].push_back(cur);

            ++column;
            ++cur;
        }
        ++ row;
        t = s;
    }

    n = row;
    cout << m * n << endl;

    while (!queue.empty()){
        auto [node, dist] = queue.front();
        queue.pop();
        if (node == end){
            cout << dist << endl;
            break;
        }
        for (auto & i : graph[node]){
            if (!visited[i]){
                visited.set(i);
                queue.push({i, dist + 1});
            }
        }
    }
    
   
    fin.close();
    return 0;
}
