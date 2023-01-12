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
using std::string_view;

int main(){
    
    ifstream fin = ifstream("inputs/day4.txt", std::ios::in);
    string s;

    int res{};

    while(getline(fin, s)){
        int pos = s.find_last_of(',');
        int sep = s.find_first_of('-');
        int sep2 = s.find_last_of('-');
        
        int l1 = stoi(s.substr(0, sep));
        int r1 = stoi(s.substr(sep+1, pos));

        int l2 = stoi(s.substr(pos+1, sep2));
        int r2 = stoi(s.substr(sep2+1, s.length()));

        // if (not ((l1 > l2 and r2 < r1) or (l1 < l2 and r2 > r1))){
        //     res ++;
        // }

        if (not ((r1 < l2 or r2 < l1))){
            res ++;
        }
    }

    cout << res << endl;

    fin.close();
    return 0;
}
