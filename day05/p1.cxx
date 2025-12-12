#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;
vector<ll> ch(string s);
bool isfresh(vector<pair<ll, ll>> a, ll v);
int main(){
    vector<string> r;
    vector<ll> a;
    vector<pair<ll, ll>> si;
    string s;
    ll a1;
    while(cin >> s){
        vector<ll> c = ch(s);
        if(!c[0]){
            a.push_back(stoll(s));
        }else{
            pair<ll, ll> ss = {c[1], c[2]};
            si.push_back(ss);
            r.push_back(s);
        }
    }

    //for(string v : r){cout << v << '\n';} 
    //for(pair<ll, ll>  v : si){cout << "fp: " << v.first << "  sp: " << v.second << '\n';}
    //cout<<"end\n";
    //for(ll v : a){cout << v << '\n';}
    ll sk = 0;
    for(ll v : a){
        if(isfresh(si, v)){
            ++sk;
        }
    }
    cout << sk;
    return 0;
}

bool isfresh(vector<pair<ll, ll>> a, ll v){
    for(pair<ll, ll> b : a){
        if(v >= b.first && v <= b.second){
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