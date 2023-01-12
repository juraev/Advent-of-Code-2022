#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>

using std::cout;
using std::cin;

int main(){
    
    std::ifstream fin = std::ifstream("inputs/day1.txt", std::ios::in);

    std::string s;

    std::priority_queue<int, std::vector<int>, std::greater_equal<int>> pq;

    int sm = 0;
    int mx = 0;
    
    while(getline(fin, s)){

        if (s == ""){
            if (pq.size() == 3 and pq.top() < sm){
                pq.pop();
            }
            
            if (pq.size() < 3){
                pq.push(sm);
                cout << sm << std::endl;
            }
            sm = 0;
        } else {
            sm += std::stoi(s);
        }
    }

    while(!pq.empty()){
        sm = pq.top();
        mx += sm;
        pq.pop();
    }

    cout << mx << "\n";
    
    fin.close();

}