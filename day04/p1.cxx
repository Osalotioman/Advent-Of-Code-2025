#include <bits/stdc++.h>
using namespace std;
int main(){
    vector<string> g, g1;
    string s; 
    int r = 0;
    while(cin >> s){
        g.push_back(s);
    }
    //g1 = g;
    // Loop through grid, for each position, run check
    for(int i=0; i<g.size(); ++i){
        for(int j=0; j<s.size(); ++j){
            if(g[i][j] == '@'){
                // Count number of @ in 8 adjacents
                int ac = 0;
                string as = "";
                as += i-1 > -1 && j-1 > -1 ? g[i-1][j-1] : '.';
                as += j-1 > -1 ? g[i][j-1] : '.';
                as += i+1 < g.size() && j-1 > -1 ? g[i+1][j-1] : '.'; 
                as += i+1 < g.size() ? g[i+1][j] : '.';
                as += i+1 < g.size() && j+1 < s.size() ? g[i+1][j+1] : '.';
                as += j+1 < s.size() ? g[i][j+1] : '.'; 
                as += i-1 > -1 && j+1 < s.size() ? g[i-1][j+1] : '.';
                as += i-1 > -1 ? g[i-1][j] : '.';
                string v1 = as;
                sort(as.begin(), as.end());
                /* 
                if(i == 0 && j == 3){
                    cout << "0, 3: " << as << " v1: " << v1 << '\n';
                }
                */
                if(as[4] != '@'){
                    ++r;
                    //cout << "index: " << '(' << i << ", " << j << "), string: " << as << '\n';
                    //g1[i][j] = 'x';
                }
            }
        }
    }
    cout << r << '\n';
    /* 
    for(string row : g1){
        cout << row << '\n';
    }
        */
    //cout << ('@' > '.' ? "YES" : "NO") << '\n';
    
    return 0;
}
/*
..xx.xx@x.
x@@.@.@.@@
@@@@@.x.@@
@.@@@@..@.
x@.@@@@.@x
.@@@@@@@.@
.@.@.@.@@@
x.@@@.@@@@
.@@@@@@@@.
x.x.@@@.x.
*/