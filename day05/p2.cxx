#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
vector<ll> ch(string s);
bool inArr(vector<ll> a, ll v);
int main(){
    vector<string> r;
    vector<ll> a;
    vector<pair<ll, ll>> si;
    string s;
    ll a1;
    while(cin >> s){
        vector<ll> c = ch(s);
        if(c[0]){
            pair<ll, ll> ss = {c[1], c[2]};
            si.push_back(ss);
        }
    }
    pair<ll, ll> v = {-1, -1};
    for(pair<ll, ll> &b : si){
        for(pair<ll, ll> &c : si){
            if(b != c && b != v && c != v){
                // Adjust range if overlap exist.
                if(b.first <= c.first && b.second >= c.second){
                    // This means the interval c is contained in the interval b.
                    // Take out the interval c
                    c.first = -1;
                    c.second = -1;
                }else if(b.first <= c.first && b.second >= c.first && b.second < c.second){
                    // c starts in the range of b, so takes out from a point in the interval of b to the end of b.
                    // adjust c to start from the end of b
                    c.first = b.second + 1;
                }else if(b.first <= c.second && b.second >= c.second && b.first < c.second){
                    c.second = b.first  - 1;
                }
            }
        }
    }
    ll gi = 0;
    for(pair<ll, ll> b : si){
        if(b != v){ 
            gi += b.second - b.first + 1;
        }
    }
    cout << gi;
    return 0;
}

bool inArr(vector<ll> a, ll v){
    for(ll c : a){
        if(v == c){
            return true;
        }
    }
    return false;
}

vector<ll> ch(string s){
    for(ll i = 0; i< s.size(); ++i){
        if(s[i] == '-'){
            ll fp = stoll(s.substr(0, i));
            ll sp = stoll(s.substr(i+1, s.size()-i-1));
            return {1, fp, sp};
        }
    }
    return {0, 0};
}