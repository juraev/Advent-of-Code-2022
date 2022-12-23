#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;

int main(){
    
    ifstream fin = ifstream("inputs/day2.txt", std::ios::in);
    string s;

    int res{};

    while(getline(fin, s)){
        int him = s[0]-'A';
        int me = s[2]-'X';

        if (me == 0){
            me = (him + 2) % 3;
        } else if(me == 1){
            res += 3;
            me = him;
        } else {
            res += 6;
            me = (him + 4) % 3;
        }

        res += 1 + me;
    }

    cout << res << endl;


    fin.close();
    return 0;
}

int main1(){
    
    ifstream fin = ifstream("inputs/day2.txt", std::ios::in);
    string s;

    int res{};

    while(getline(fin, s)){
        int him = s[0]-'A';
        int me = s[2]-'X';

        cout << him << " " << me << endl;

        res += 1 + me;

        if (him == me)
            res += 3;
        else if(((me-him) + 3) % 3 == 1){
            res += 6;
        }
    }

    cout << res << endl;


    fin.close();
    return 0;
}