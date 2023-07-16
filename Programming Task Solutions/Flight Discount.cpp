#include<bits/stdc++.h>
using namespace std;
 
#define int long long int
 
int djikstramodified(int n, int m, unordered_map<int,list<pair<int,int>>> &adjList){
    if(n==1) return 0;
    vector<int>dist(n+1,LLONG_MAX);
    vector<int>disc(n+1,LLONG_MAX);
    priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>>pq;
    pq.push({0,{1,0}}); dist[1]=0; 
    while(!pq.empty()){
        int d = pq.top().first;
        int node = pq.top().second.first;
        bool couponUsed = pq.top().second.second;
        pq.pop();
        if(couponUsed==0){
            if(dist[node]<d){
                continue;
            }
        }
        else{
            if(disc[node]<d){
                continue;
            }
        }
        for(auto i:adjList[node]){
            int v = i.first; int c = i.second;
            if(couponUsed==0){
                //either preserve coupon
                if((d+c)<dist[v]){
                    dist[v]=d+c;
                    pq.push({dist[v],{v,0}});
                }
                //or use it
                if((d+c/2)<disc[v]){
                    disc[v]=d+c/2;
                    pq.push({disc[v],{v,1}});
                }
            }
            else{
                //you cant use coupon now and we will only be able to alter discounted price array
                if((d+c)<disc[v]){
                    disc[v]=d+c;
                    pq.push({disc[v],{v,1}});
                }
            }
        }
    }
    return disc[n];
}
 
void solve(){
    int n; int m;
    cin>>n>>m;
    unordered_map<int,list<pair<int,int>>> adjList;
    for(int i=0; i<m;i++){
        int u, v, d;
        cin>>u>>v>>d;
        adjList[u].push_back({v,d});
    }
    cout<<djikstramodified(n,m,adjList)<<"\n";
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    solve();
 
 
    return 0;
}