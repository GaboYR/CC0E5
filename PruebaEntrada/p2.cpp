#include<iostream>
#include<vector>
#include<map>
#include<cmath>
#include<algorithm>
#include<set>
int res = 0;
int vis[1005] = {0};
std::vector<int> g[1005];
void dfs(int u,int value) {
    res = std::max(res,value);
    vis[u] = 1;
    for (int i = 0; i < g[u].size(); i ++) {
        if (!vis[g[u][i]]) {
            dfs(g[u][i],value + 1);
        }
    }
}
void allDFS() {
    std::fill(vis,vis + 1005,0);
    for (int i = 0; i < 1005; i ++) {
        if (!vis[i] && !g[i].empty()) {
            dfs(i,1);
        }
    }
}
int main () {
    std::cin.tie(nullptr)->sync_with_stdio(false);
    int t;  std::cin >> t;
    
    for (int _t = 0; _t < t;_t ++) {
        int n;  std::cin >> n;
        std::map<std::pair<int,int>,int> mp;
        mp[{1,2}] = 1;
        mp[{1,3}] = 1;
        mp[{2,3}] = 1;
        for (int i = 4; i <= n ; i ++) {
            int u,v;    std::cin >> u >> v;
            if (u > v) std::swap(u,v);
            // Si tenemos el par u, v conectados
            // Y se quiere conecat u, i con i, v
            // Esto genera mayor tama;o de ciclo
            mp[{u,i}] = 1;
            mp[{v,i}] = 1;
            if (mp.count({u,v}) == 1) {    
                mp[{u,v}] ++;
            }
        }
        for (auto it = mp.begin(); it != mp.end(); it ++) {
            // Si el par u,v se recorre mas de 1 vez, se elimina
            if (it->second == 1) {
                g[it->first.first].push_back(it->first.second);
                g[it->first.second].push_back(it->first.first);
            }   
        }
        for (int i = 0; i < 1005;i ++) {
            std::sort(g[i].begin(),g[i].end());
            g[i].erase(std::unique(g[i].begin(),g[i].end()),g[i].end());
        }
        allDFS();
        std::cout << "Case #" << _t + 1<< ": " << res << "\n";
        res = 0;
    }
    return 0;
}