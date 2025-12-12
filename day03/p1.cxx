#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
int main(){
    string b;
    ll j_sum = 0;
    while(cin >> b){
        // Find the largest digit thats not at the edge.
        char d1 = b[0];
        int d1i = 0;
        for(int i=0; i<b.size()-1; ++i){
            if(b[i] > d1){
                d1 = b[i];
                d1i = i;
            }
        }
        // Starting from the index after the max num, find the next max num
        char d2 = b[d1i+1];
        for(int i=d1i+1; i<b.size(); ++i){
            if(b[i] > d2){
                d2 = b[i];
            }
        }
        j_sum += (d1 - '0') * 10 + (d2 - '0');
    }
    cout << j_sum;
    return 0;
}