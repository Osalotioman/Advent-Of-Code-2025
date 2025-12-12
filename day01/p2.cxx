#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; 
    int d = 50, r = 0;
    while(cin >> s){
        int c = s[0] == 'L' ? -1 : 1;
        s[0] = '0';
        int v = stoi(s);
        while(v--){
            d += c;
            d %= 100;
            if(d == 0){
                ++r;
            }
        }
    }
    cout << r;
    return 0;
}