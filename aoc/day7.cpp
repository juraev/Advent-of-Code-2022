#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include <algorithm>
#include <bit>
#include <map>

using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::vector;
using std::endl;
using std::string_view;
using std::map;

struct file{
    bool isFolder;
    string name;
    int size;
    file *parent;
    map<string, file*> files;
};

void print(file * f, int depth){
    for (int i = 0; i < depth; i++){
        cout << " ";
    }
    cout << f->name << " " << f->size << endl;
    for (auto & [name, file] : f->files){
        print(file, depth + 1);
    }
}

void calcSize(file * f, int & sum){
    if (f->isFolder){
        for (auto & [name, file] : f->files){
            calcSize(file, sum);
            f->size += file->size;
        }

        if (f->size < 100000){
            cout << f->name << " " << f->size << endl;
            sum += f->size;
        }
    }
}

void calcMin(file * f, const int mn, int & res){
    if (f->isFolder){
        for (auto & [name, file] : f->files){
            calcMin(file, mn, res);
        }

        if (f->size >= mn and res > f->size){
            res = f->size;
        }
    }
}


int main(){
    
    ifstream fin = ifstream("inputs/day7.txt", std::ios::in);
    string s;

    file * cur = new file{true, "root", 0, nullptr, {}};
    file * root = cur;

    while(getline(fin, s)){
        string_view sv = s;

        if (sv.substr(2, 2) == "cd"){
            sv.remove_prefix(5);
            auto name = sv.data();
            
            if (sv == ".."){
                cur = cur->parent;
            } else {
                if (cur->files.find(name) == cur->files.end())
                    cur->files[name] = new file{true, name, 0, cur, {}};
                cur = cur->files[name];
            }
        } else if (sv.substr(2, 2) != "ls"){
            if (sv.substr(0, 3) == "dir"){
                auto name = sv.substr(4, sv.size() - 4).data();
                cur->files[name] = new file{true, name, 0, cur, {}};
            } else {
                auto size = std::stoi(sv.substr(0, sv.find(" ")).data());
                auto name = sv.substr(sv.find(" ") + 1, sv.size() - sv.find(" ") - 1).data();
                cur->files[name] = new file{false, name, size, cur, {}};
            }
        }
    }

    int sum{};
    calcSize(root, sum);

    int res{root->size};
    int mn{root->size - 40000000};
    cout << root->size << " " << mn << endl;
    calcMin(root, mn, res);

    cout << res << endl;


    fin.close();
    return 0;
}
