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
    
    ifstream fin = ifstream("inputs/day6.txt", std::ios::in);
    string s;

    int res{};

    while(getline(fin, s)){
        string_view sv = s;

        vector<char> v(14, 0);
        
        for (char c : sv){
            ++ res;
            
            for (int i = 0; i < 14; ++ i){
                if (v[i] == c){
                    copy(v.begin() + i + 1, v.end(), v.begin());
                    fill(v.begin() + 13 - i, v.end(), 0);
                    break;
                }
            }
            int i = 0;
            for(; i < 14; ++ i){
                if (v[i] == 0){
                    v[i] = c;
                    break;
                }
            }
            if (i == 13){
                break;
            }
        }
    }

    cout << res << endl;


    fin.close();
    return 0;
}
