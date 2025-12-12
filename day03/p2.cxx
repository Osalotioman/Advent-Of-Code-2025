#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
int main(){
    string b;
    ll j_sum = 0;
    while(cin >> b){
        int di = 0;
        char d = b[0];
        for(int j = 0; j<12; ++j){
            for(int i=di; i<b.size()-(11-j); ++i){
                if(b[i] > d){
                    d = b[i];
                    di = i;
                }
            }
            j_sum += (d - '0') * pow(10, 11-j);
            ++di;
            d = b[di];
        }
    }
    cout << j_sum;
    return 0;
}