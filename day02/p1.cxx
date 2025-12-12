#include <bits/stdc++.h>
typedef unsigned long long ll;
using namespace std;
bool is_palindrome(ll v);
int main(){
    string s; cin >> s;
    ll i_sum = 0;
    vector<pair<string, string>> r;
    vector<string> si(2, "");
    int tg = 0;
    for(int i=0; i<s.size(); ++i){
        if(s[i] == '-'){
            ++tg;
        }else if(s[i] == ','){
            pair<string, string> rv;
            rv.first = si[0];
            rv.second = si[1];
            r.push_back(rv);
            tg = 0;
            si[0] = "";
            si[1] = "";
        }else{
            si[tg] += s[i];
        }
    }
    pair<string, string> rv;
    rv.first = si[0];
    rv.second = si[1];
    r.push_back(rv);
    for(auto v : r){
        //cout << v.first << " : " << v.second << '\n';
        ll st = stoll(v.first), en = stoll(v.second);
        for(ll i=st; i<=en; ++i){
            if(is_palindrome(i)){
                i_sum += i;
            }
        }
    }
    cout << i_sum;
    return 0;
}

bool is_palindrome(ll v){
    string k = to_string(v);
    if(k.size() % 2 != 0){
        return false;
    }
    int n = k.size()/2;
    int j = n;
    for(int i=0; i<n; ++i){
        if(k[i] != k[j]){
            return false;
        }
        ++j;
    }
    //cout << "Invalid: " << v;
    return true;
}