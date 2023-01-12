#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <bit>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;

int main(){
    
    ifstream fin = ifstream("inputs/day3.txt", std::ios::in);
    string s, t, u;

    int res{};

    while(getline(fin, s)){
        getline(fin, t);
        getline(fin, u);
        vector<uint8_t> v(52);

        for (char i : s){
            int j = std::islower(i);
            v[j * (i - 'a') + (1-j)*(26 + i-'A')] |= 1;
        }

        for (char i : t){
            int j = std::islower(i);
            int k = j * (i - 'a') + (1-j)*(26 + i-'A');
            v[k] |= 4;
        }

        for (char i : u){
            int j = std::islower(i);
            int k = j * (i - 'a') + (1-j)*(26 + i-'A');

            if (std::popcount(v[k]) == 2){
                res+= 1 + j * (i - 'a') + (1-j)*(26 + i-'A');
                break;
            }

        }

    }

    cout << res << endl;

    fin.close();
    return 0;
}
