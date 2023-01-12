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
    
    ifstream fin = ifstream("inputs/day5.txt", std::ios::in);
    string s;

    int res{};
    vector<vector<char>> stacks;

    while(getline(fin, s)){
        if (s.empty()) break;
        stacks.resize((s.size() + 1) / 4);

        for (int i = 1; i < s.size(); i += 4){
            if (isalpha(s[i])){
                stacks[i / 4].push_back(s[i]);
            }
        }
    }
    for(auto& stack : stacks){
        reverse(stack.begin(), stack.end());
    }


    while(getline(fin, s)){
        if (s.empty()) break;
        
        int cnt, fr, to;
        sscanf(s.c_str(), "move %d from %d to %d", &cnt, &fr, &to);
        fr--; to--;

        // move(stacks[fr].rbegin(), stacks[fr].rbegin()+cnt, back_inserter(stacks[to]));
        move(stacks[fr].end() - cnt, stacks[fr].end(), back_inserter(stacks[to]));
        stacks[fr].erase(stacks[fr].end() - cnt, stacks[fr].end());  
    }



    string res1;
    for (auto& stack : stacks){
        res1 += stack.back();
    }

    cout << res1 << endl;

    fin.close();
    return 0;
}
