#include <iostream>
#include <string>
#include <string_view>

using namespace std;

int main() {
  string s;
  
  int cycle{};
  int x{1};
  int res{};
  
  string CRT(240, '.');
  

  while(getline(cin, s)){
   int pos = s.find_first_of(' ');
   ++ cycle;
    int tmp = (cycle % 40);
    
    if (abs(x-tmp+1) < 2){
        CRT[cycle-1] = '#';
    }
    
    if (cycle <= 220 and 
     ((s[0] == 'a' and tmp == 19) or tmp == 20) ){
     res += x * (cycle + (20-tmp));
    }
    
    if (s[0] == 'a'){
     ++ cycle;
     int k = stoi(s.substr(pos + 1));
        if (abs(x - (cycle%40) + 1) < 2){
            CRT[cycle-1] = '#';
        }
        x += k;
    }
  }
  
  
  for (int i = 0; i < 6; ++ i){
      cout << CRT.substr(i * 40, 40) << endl;
  }
  
  
  cout << res << endl;
  
  
  return 0;
}