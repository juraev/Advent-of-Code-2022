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

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;
using std::stoi;

using TYPE = unsigned long long;

struct Monkey{
    int id;
    vector<TYPE> items;
    std::function<TYPE(TYPE)> op;
    int test;
    int trueM;
    int falseM;

    TYPE inspected{};
};

void print_monkey(Monkey & m){
    cout << m.id << endl;
    for (auto & i : m.items){
        cout << i << " ";
    }
    cout << endl;
    cout << m.test << " " << m.trueM << " " << m.falseM << endl;
    cout << m.inspected << endl;
}


int main(){
    
    ifstream fin = ifstream("inputs/day11.txt", std::ios::in);
    string s;

    vector<Monkey> monkeys;

    TYPE bigtest = 1;


    while(getline(fin, s)){
        auto id = stoi(s.substr(6, s.length() - 7));

        getline(fin, s);
        string_view sv = s;
        sv.remove_prefix(18);
        std::stringstream ss(sv.data());

        getline(fin, s);
        sv = s;
        sv.remove_prefix(23);
        std::function<TYPE(TYPE)> op;

        if (sv[0] == '*'){
            if (sv.substr(2) == "old")
                op = [](TYPE x)->TYPE{return x * x;};
            else {
                auto coef = stoi(sv.substr(2).data());
                op = [coef](TYPE x)->TYPE{return x * coef;};
            }
        } else {
            auto coef = stoi(sv.substr(2).data());
            op = [coef](TYPE x)->int{return x + coef;};
        }
        
        getline(fin, s);
        sv = s;
        auto test = stoi(sv.substr(sv.find_last_of(' ')).data());

        getline(fin, s);
        sv = s;
        auto trueM = stoi(sv.substr(sv.find_last_of(' ')).data());

        getline(fin, s);
        sv = s;
        auto falseM = stoi(sv.substr(sv.find_last_of(' ')).data());

        Monkey m = {id, {}, op, test, trueM, falseM};

        while (getline(ss, s, ',')){
            m.items.push_back(stoi(s));
        }

        monkeys.push_back(m);

        bigtest *= test;

        getline(fin, s);
    }

    int rounds = 10000;
    int divide = 1;

    for(int i = 0; i < rounds; ++ i){

        for (auto& monkey : monkeys){
            auto& items = monkey.items;
            for (auto item : items){
                item = monkey.op(item);
                item = item % bigtest;
                item /= divide;
                int next;
                if (item % monkey.test == 0)
                    next = monkey.trueM;
                else
                    next = monkey.falseM;                
                monkeys[next].items.push_back(item);
                monkey.inspected++;
            }
            items.clear();

            cout << monkey.inspected << " ";
        }
        cout << endl;
    }

    std::sort(monkeys.begin(), monkeys.end(), [](const Monkey& m1, const Monkey& m2){
        return m1.inspected > m2.inspected;
    });

    // for(auto& monkey: monkeys){
    //     print_monkey(monkey);
    //     cout << "--------------------------------" << endl;
    // }


    cout << monkeys[0].inspected * monkeys[1].inspected << endl;



    fin.close();
    return 0;
}
