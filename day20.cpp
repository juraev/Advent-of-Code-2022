
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

typedef struct item *pitem;
struct item {
	int pr, cnt;
    double key;
    long long value;
	
	pitem l,r;
	item(double Key, long long val): pr(rand()),
    cnt(1), 
    key(Key), value(val),
    l(0),r(0) {}
};

int cnt(pitem it){return it?it->cnt:0;}

void update(pitem it){
	if(it){
		it->cnt=cnt(it->l)+cnt(it->r)+1;
	}
}
void merge(pitem& t, pitem l, pitem r){
	if(!l||!r)t=l?l:r;
	else if(l->pr>r->pr)merge(l->r,l->r,r),t=l;
	else merge(r->l,l,r->l),t=r;
	update(t);
}
void splitL(pitem t, pitem& l, pitem& r, int sz){ // sz:desired size of l
	if(!t){l=r=0;return;}
	if(sz<=cnt(t->l))splitL(t->l,l,t->l,sz),r=t;
	else splitL(t->r,t->r,r,sz-1-cnt(t->l)),l=t;
	update(t);
}
void splitV(pitem t, pitem& l, pitem& r, double Key){
    if(!t){l=r=0;return;}
    if(Key<=t->key)splitV(t->l,l,t->l,Key),r=t;
    else splitV(t->r,t->r,r,Key),l=t;
    update(t);
}

void collect(pitem t, vector<long long>& v){
    if (!t) return;
    collect(t->l, v);
    v.push_back(t->value);
    collect(t->r, v);
}



int main(){
    
    ifstream fin = ifstream("inputs/day20.txt", std::ios::in);
    string s;

    pitem t = 0;

    int n = 0;

    while(getline(fin, s)){
        int x;
        sscanf(s.c_str(), "%d", &x);
        merge(t, t, new item(n, x * 811589153LL));
        ++ n;
    }

    vector<double> search(n);
    std::iota(search.begin(), search.end(), 0);

    merge(t, t, new item(n, 0LL));


    for (int j = 0; j < 10; ++ j){
    for (int i = 0; i < n; ++ i){

        pitem l, r, m, m1, m2;
        splitV(t, l, r, search[i]);
        splitL(r, m, r, 1);

        int pos = cnt(l);
        int new_pos = ((pos + m->value) % (n - 1) + n - 1) % (n - 1);

        merge(t, l, r);

        splitL(t, l, r, new_pos);
        splitL(r, m1, r, 1);

        if (new_pos == 0){
            m->key = (m1->key - 1) / 2;
        } else {
            splitL(l, l, m2, new_pos - 1);
            m->key = (m1 -> key + m2 -> key) / 2;
            merge(l, l, m2);
        }
        
        search[i] = m -> key;

        merge(m, m, m1);
        merge(t, l, m);
        merge(t, t, r);

    }
        // vector<long long> reslist;
        // collect(t, reslist);

        // reslist.pop_back();

        // for (long long x : reslist){
        //     cout << x << " ";
        // }
        // cout << endl;
    }

    vector<long long> reslist;
    collect(t, reslist);

    reslist.pop_back();

    int i = std::find(reslist.begin(), reslist.end(), 0) - reslist.begin();

    cout << (reslist[(1000 + i) % reslist.size()] 
            + reslist[(2000 + i) % reslist.size()] 
            + reslist[(3000 + i) % reslist.size()]);

    
    
    fin.close();
    return 0;
}