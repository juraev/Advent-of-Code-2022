#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <bit>
#include <map>
#include <bitset>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;



int main(){
    
    ifstream fin = ifstream("inputs/day8.txt", std::ios::in);
    string s;
    vector<string> table;


    while(getline(fin, s)){
        string_view sv = s;
        table.push_back(s);
    }

    int n = table.size();
    int m = table[0].size();

    int res =  n + n + m + m - 4;
    std::vector<int> mp(n * m, 1);

    int k;

    for (int i = 1; i < n - 1; ++i){
        vector<int> v(10, 0);
        k = i * m + 1;

        for (int j = 1; j < m - 1; ++j){
            int now = table[i][j] - '0';
            int pos = *std::max_element(v.begin() + now, v.end());
            mp[k] *= j - pos;
            v[now] = j;
            ++ k;
        }
    }

    for (int i = 1; i < n - 1; ++i){
        vector<int> v(10, m - 1);
        k = i * m + m - 2;

        for (int j = m - 2; j > 0; --j){
            int now = table[i][j] - '0';
            int pos = *std::min_element(v.begin() + now, v.end());
            mp[k] *= pos - j;
            v[now] = j;
            -- k;
        }
    }

    for (int j = 1; j < m - 1; ++j){
        vector<int> v(10, 0);
        k = j + m;

        for (int i = 1; i < n - 1; ++i){
            int now = table[i][j] - '0';
            int pos = *std::max_element(v.begin() + now, v.end());
            mp[k] *= i - pos;
            v[now] = i;

            k += m;
        }
    }

    for (int j = 1; j < m - 1; ++j){
        vector<int> v(10, n - 1);
        k = (n - 2) * m + j;

        for (int i = n-2; i > 0; --i){
            int now = table[i][j] - '0';
            int pos = *std::min_element(v.begin() + now, v.end());
            mp[k] *= pos - i;
            v[now] = i;
            k -= m;
        }
    }

    res = *std::max_element(mp.begin(), mp.end());

    cout << res << endl;

    fin.close();
    return 0;
}
