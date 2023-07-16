#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
void solve(){
    int n, m, k;
    cin>>n>>m>>k;
    vector<priority_queue<int>>dist(n+1);
    unordered_map<int,list<pair<int,int>>>adjList;
    for(int i=0;i<m;i++){
        int u, v, d; cin>>u>>v>>d;
        adjList[u].push_back({v,d});
    }
    
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,1}); dist[1].push(0);
    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(d>dist[node].top()) continue;
        for(auto i:adjList[node]){
            if(dist[i.first].size()<k){
                dist[i.first].push(d+i.second);
                pq.push({d+i.second,i.first});
            }
            else if((d+i.second<dist[i.first].top())){
                dist[i.first].push(d+i.second);
                dist[i.first].pop();
                pq.push({d+i.second,i.first});
            }
        }
    }
    vector<int>ans;
    while(!dist[n].empty()){
        ans.push_back(dist[n].top());
        dist[n].pop();
    }
    reverse(ans.begin(),ans.end());
    for(int i=0; i<k; i++){
        cout<<ans[i]<<" ";
    } cout<<"\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    solve();
    
}