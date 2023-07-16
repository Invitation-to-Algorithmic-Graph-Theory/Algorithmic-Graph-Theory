#include<bits/stdc++.h>
using namespace std;
 
#define int long long int
 
void solve(){
    int n, m, q;
    cin>>n>>m>>q;
    vector<vector<int>>dist(n+1,vector<int>(n+1,1e13));
    for(int i=0;i<m;i++){
        int u, v, d; cin>>u>>v>>d;
        dist[u][v]=min(d,dist[u][v]);
        dist[v][u]=min(d,dist[v][u]);
    }
    for(int i=1;i<=n;i++){
        dist[i][i]=0;
    }
 
    for(int k=1; k<=n; k++){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(i==k||j==k || i==j) continue;
                if(dist[i][k]==1e13 || dist[k][j]==1e13) continue;
                dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
            }
        }
    }
 
    for(int i=0;i<q;i++){
        int u,v;
        cin>>u>>v;
        if(dist[u][v]==1e13){
            cout<<-1<<"\n";
        }
        else{
            cout<<dist[u][v]<<"\n";
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    solve();
    
}