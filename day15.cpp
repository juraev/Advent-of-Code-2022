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
    
    ifstream fin = ifstream("inputs/day15.txt", std::ios::in);
    string s, t;

    int xs, ys, xb, yb;
    const int SIZE = 4000001;

    vector<std::list<std::pair<int, int> > > ranges{SIZE};
    // vector<std::set<int> > beacons{SIZE};

    while(getline(fin, s)){

        sscanf(s.c_str(), 
            "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d", 
            &xs, &ys, &xb, &yb);

        int dist = abs(xs - xb) + abs(ys - yb);

        if (yb >= 0 && yb < SIZE && xb >= 0 && xb < SIZE){
            ranges[yb].push_back({xb, xb});
        }
        
        for (int yline = 0;  yline< SIZE; ++yline){
            int toline = abs(ys - yline);
            if(dist >= toline){
                int l = xs - (dist - toline);
                int r = xs + (dist - toline);
                if (r >= 0 and l < SIZE){
                    l = std::max(l, 0);
                    r = std::min(r, SIZE-1);
                    ranges[yline].push_back({l, r});
                }
            }
            
            // if (yb == yline){
            //     beacons[yline].insert(xb);
            // }
        }
    }

    for (int yline = 0; yline < SIZE; ++yline){
        ranges[yline].sort();
        vector<std::pair<int, int>> newranges;

        while(ranges[yline].size() > 1){
            auto [l1, r1] = ranges[yline].front();
            auto [l2, r2] = *(++ranges[yline].begin());

            if(r1 >= l2 - 1){
                ranges[yline].front() = {l1, std::max(r1, r2)};
                ranges[yline].erase(++ranges[yline].begin());
            } else {
                newranges.push_back(ranges[yline].front());
                ranges[yline].erase(ranges[yline].begin());
            }
        }
        newranges.push_back(ranges[yline].front());

        int count = 0;
        for(auto [l, r] : newranges){
            count += r - l + 1;
        }
        
        if (count != SIZE){
            cout << yline << endl;
            
            long long res = (newranges[0].second + 1ll) * 4000000 + yline;
            cout << res << endl;
        }

        // for(auto b : beacons[yline]){
        //     for(auto [l, r] : newranges){
        //         if(b >= l && b <= r){
        //             count--;
        //             break;
        //         }
        //     }
        // }
    }

    fin.close();
    return 0;
}
