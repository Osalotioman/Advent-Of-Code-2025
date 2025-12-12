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
    string j = "", k = to_string(v);
    bool w = false;
    for(int i=0; i<k.size()-1; ++i){
        j += k[i];
        int wc = 0;
        if(k.size() %  j.size() == 0){
            // k can be partitioned into j parts
            string j1 = "";
            for(int i1 = 0; i1 < k.size(); ++i1){
                j1 += k[i1];
                if(j1.size() == j.size()){
                    if(j1 == j){
                        // passed
                        j1 = "";
                        ++wc;
                    }else{
                        // failed - this j is not the one
                    }
                }
            }
            if(wc == k.size() / j.size()){ 
                w = true; 
                break;
            }
        }
    }
    return w;
}