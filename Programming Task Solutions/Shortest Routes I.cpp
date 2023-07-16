#include<bits/stdc++.h>
using namespace std;
 
#define int long long
 
void solve(){
    int n; int m;
    cin>>n>>m;
    unordered_map<int,list<pair<int,int>>> adjList;
    for(int i=0; i<m;i++){
        int u, v, d;
        cin>>u>>v>>d;
        adjList[u].push_back({v,d});
    }
    vector<int>dist(n+1,LLONG_MAX);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
    pq.push({0,1}); dist[1]=0; 
    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        if(dist[node]<d) continue;
        for(auto i:adjList[node]){
            if(dist[i.first]>(d+i.second)){
                dist[i.first]=d+i.second;
                pq.push({dist[i.first],i.first});
            }
        }
    }
    for(int i=1;i<=n;i++){
        cout<<dist[i]<<" ";
    } cout<<"\n";
 
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    solve();
 
 
    return 0;
}