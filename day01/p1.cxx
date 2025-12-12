#include <bits/stdc++.h>
using namespace std;

int main(){
    string s; 
    int d = 50, r = 0;
    while(cin >> s){
        if(s[0] == 'L'){
            s[0] = '0';
            d -= stoi(s); 
        }else{
            s[0] = '0';
            d += stoi(s);
        }
        d %= 100;
        if(d == 0){
            ++r;
        }
    }
    cout << r;
    return 0;
}