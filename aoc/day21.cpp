
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


struct Monkey{
    string name;
    long long value;

    int op;
    Monkey* left;
    Monkey* right;
};

int main(){
    
    ifstream fin = ifstream("inputs/day21.txt", std::ios::in);
    string s, name, m1, m2, op;

    std::map<string, Monkey*> monkeys;

    std::function<Monkey*(string)> get = [&](string name){
        auto M = monkeys[name];
        if (M == nullptr){
            M = new Monkey();
            monkeys[name] = M;
        }
        return M;
    };

    while(getline(fin, s)){
        
        name = s.substr(0, 4);
        m1 = s.substr(s.find(' ') + 1, s.find(' ') - s.find(' ') - 1);

        auto M = get(name);

        if (isnumber(m1[0])){
            M->name = name;
            M->value = stoi(m1);
            M->op = 0;
            M->left = nullptr;
            M->right = nullptr;
        }else{
            op = s.substr(11, 1);
            m1 = s.substr(6, 4);
            m2 = s.substr(13, s.size() - 13);
            M->name = name;
            M->value = 0;
            M->op = op[0] == '+' ? 1 : (op[0] == '-' ? 2 : (op[0] == '*' ? 3 : 4));
            M->left = get(m1);
            M->right = get(m2);
        }
    }


    std::function<long long(Monkey*)> eval = [&](Monkey* m){
        if (m->op == 0){
            return m->value;
        }else{
            eval(m->left);
            eval(m->right);

            if (m->op == 1){
                m->value = m->left->value + m->right->value;
            }else if (m->op == 2){
                m->value = m->left->value - m->right->value;
            }else if (m->op == 3){
                m->value = m->left->value * m->right->value;
            }else{
                cout << " here " << endl;
                m->value = m->left->value / m->right->value;
            }
            
            return m->value;
        }
    };


    for (int i = 0; i < 1; ++ i){
        monkeys["humn"]->value = i;
        
        long long L = eval(monkeys["root"]->left);
        long long R = eval(monkeys["root"]->right);

        cout << i << " " << L << " " << R << endl;
    }


    fin.close();
    return 0;
}