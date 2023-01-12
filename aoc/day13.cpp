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
#include <variant>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;
using std::stoi;


struct VariableDepthList : std::variant<std::vector<VariableDepthList>, int> {
private:
    using base = std::variant<std::vector<VariableDepthList>, int>;
public:
    using base::base;
    VariableDepthList(std::initializer_list<VariableDepthList> v) : base(v) {}


    void emplace_back(VariableDepthList v) {
        if (is_list()){
            std::get<std::vector<VariableDepthList>>(*this).emplace_back(v);
        } else {
            std::get<std::vector<VariableDepthList>>(*this) = {std::get<int>(*this), v};
        }
    }

    void emplace_back(int v) {
        if (is_list()){
            std::get<std::vector<VariableDepthList>>(*this).emplace_back(v);
        } else {
            std::get<std::vector<VariableDepthList>>(*this) = {std::get<int>(*this), v};
        }
    }

    VariableDepthList & operator[](size_t i) {
        return std::get<std::vector<VariableDepthList>>(*this)[i];
    }

    const VariableDepthList & operator[](size_t i) const {
        return std::get<std::vector<VariableDepthList>>(*this)[i];
    }

    bool is_list() const { return std::holds_alternative<std::vector<VariableDepthList>>(*this); }
    bool is_int() const { return std::holds_alternative<int>(*this); }
    bool empty() const { return is_list() ? std::get<std::vector<VariableDepthList>>(*this).empty() : false; }
    size_t size() const { return is_list() ? std::get<std::vector<VariableDepthList>>(*this).size() : 0; }
    bool operator==(const VariableDepthList & v) const { return std::get<int>(*this) == std::get<int>(v); }
    bool operator!=(const VariableDepthList & v) const { return std::get<int>(*this) != std::get<int>(v); }
    bool operator<(const VariableDepthList & v) const { return std::get<int>(*this) < std::get<int>(v); }

    void print() const {
        if (is_list()){
            cout << "[";
            for (auto & i : std::get<std::vector<VariableDepthList>>(*this)){
                i.print();
                cout << ", ";
            }
            cout << "]";
        } else {
            cout << std::get<int>(*this);
        }
    }

};


VariableDepthList parse_using_stack(string_view sv){
    std::stack<VariableDepthList> s;
    s.push(VariableDepthList{});
    for (size_t i = 0; i < sv.size(); ++i){
        if (sv[i] == '['){
            s.push(VariableDepthList{});
        } else if (sv[i] == ']'){
            auto v = s.top();
            s.pop();
            s.top().emplace_back(v);
        } else if (sv[i] == ','){
            continue;
        } else {
            size_t j = i;
            while (j < sv.size() and sv[j] != ',' and sv[j] != ']') ++j;
            s.top().emplace_back(stoi(string(sv.substr(i, j - i))));
            i = j - 1;
        }
    }
    return s.top()[0];
}


int compare(const VariableDepthList & vdl1, const VariableDepthList & vdl2){

    if (vdl1.is_int() and vdl2.is_int()){
        return (vdl1 == vdl2) ? 0 : (vdl1 < vdl2 ? -1 : 1);
    } else if (vdl1.is_list() and vdl2.is_list()){

        size_t mn = std::min(vdl1.size(), vdl2.size());

        for (size_t i = 0; i < mn; ++i){
            int res = compare(vdl1[i], vdl2[i]);
            if (res!=0) return res;
        }

        if (vdl1.size() == vdl2.size()) return 0;
        return vdl1.size() < vdl2.size() ? -1 : 1;
    } else {
        if (vdl1.is_int()) {
            VariableDepthList vdl3 = {};
            vdl3.emplace_back(vdl1);
            return compare(vdl3, vdl2);
        } else {
            VariableDepthList vdl3 = {};
            vdl3.emplace_back(vdl2);
            return compare(vdl1, vdl3);
        }
    }
}


int main(){
    
    ifstream fin = ifstream("inputs/day13.txt", std::ios::in);
    string s, t;

    vector<VariableDepthList> vdl{};

    while(getline(fin, s)){
        if (s.empty()) continue;

        VariableDepthList vdl1 = parse_using_stack(string_view(s));
        
        vdl.emplace_back(vdl1);
    }

    auto low = parse_using_stack("[[2]]");
    auto high = parse_using_stack("[[6]]");
    vdl.emplace_back(low);
    vdl.emplace_back(high);

    sort(vdl.begin(), vdl.end(), [](VariableDepthList & vdl1, VariableDepthList & vdl2){
        return compare(vdl1, vdl2) == -1;
    });


    auto ptr = std::upper_bound(vdl.begin(), vdl.end(), low, [](const VariableDepthList & vdl1, const VariableDepthList & vdl2){
        return compare(vdl1, vdl2) == -1;
    });

    auto ptr2 = std::upper_bound(vdl.begin(), vdl.end(), high, [](const VariableDepthList & vdl1, const VariableDepthList & vdl2){
        return compare(vdl1, vdl2) == -1;
    });

    cout << ptr - vdl.begin() << endl;
    cout << ptr2 - vdl.begin() << endl;

    int res = (ptr - vdl.begin()) * (ptr2 - vdl.begin());

    cout << res << endl;

    fin.close();
    return 0;
}
