
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

int gcd(int x, int y) {
    if (y == 0) return x;
    return gcd(y, x % y);
}

int main(){
    
    ifstream fin = ifstream("inputs/day25.txt", std::ios::in);
    string s;

    auto to_dec = [](string_view s){
        long long x = 0;
        for(auto c : s){
            x *= 5;
            if(c <= '2' && c >= '0'){
                x += c - '0';
            } else if (c == '-'){
                x -= 1;
            } else if (c == '='){
                x -= 2;
            }
            // cout << x << endl;
        }
        return x;
    };

    auto to_sf = [](long long x){
        string S;
        int k = 0;
        cout << x << endl;
        while(x){
            
            int c = (x % 5);
            k = 0;

            if (c == 0){
                S = '0' + S;
            } else if (c == 1){
                S = '1' + S;
            } else if (c == 2){
                S = '2' + S;
            } else if (c == 3){
                S = '=' + S;
                k = 1;
            } else if (c == 4){
                S = '-' + S;
                k = 1;
            }
            // cout << S << " " << x << endl;

            x /= 5;
            x += k;
        }
        return S;
    };

    long long L{};

    while(getline(fin, s)){

        L += to_dec(s);
    }

    cout << to_sf(L) << endl;




    fin.close();
    return 0;
}