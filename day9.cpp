#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <bit>
#include <map>
#include <set>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;



int main(){
    
    ifstream fin = ifstream("inputs/day9.txt", std::ios::in);
    string s;

    int k = 10;
    vector<std::pair<int, int>> rope(k, {0, 0});

    std::set<std::pair<int, int>> visited;
    visited.insert({0, 0});


    while(getline(fin, s)){
        char dir = s[0];
        int dist = stoi(s.substr(2));

        for (int i = 0; i < dist; ++i){

            switch(dir){
                case 'U':
                    rope[0].second++;
                    break;
                case 'D':
                    rope[0].second--;
                    break;
                case 'L':
                    rope[0].first--;
                    break;
                case 'R':
                    rope[0].first++;
                    break;
            }

            for (int j = 1; j < k; ++j){
                if (rope[j-1].first != rope[j].first and rope[j-1].second != rope[j].second) {
                    if (abs(rope[j].first-rope[j-1].first) + abs(rope[j].second-rope[j-1].second) != 2) {
                        rope[j].first += 1 - 2 * (rope[j-1].first < rope[j].first);
                        rope[j].second += 1 - 2 * (rope[j-1].second < rope[j].second);
                    }
                } else if(rope[j-1].first != rope[j].first) {
                    if (abs(rope[j].first-rope[j-1].first) != 1)
                        rope[j].first += 1 - 2 * (rope[j-1].first < rope[j].first);
                } else if(rope[j-1].second != rope[j].second){
                    if (abs(rope[j].second-rope[j-1].second) != 1)
                        rope[j].second += 1 - 2 * (rope[j-1].second < rope[j].second);
                }
            }

            visited.insert(rope.back());
        }
    }

    cout << visited.size() << endl;


    fin.close();
    return 0;
}
