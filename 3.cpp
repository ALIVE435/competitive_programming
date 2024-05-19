#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define int long long

//Rerooting:https://cses.fi/problemset/task/1133

int32_t main(){
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL);  

    int n; cin>>n;
    if(n==1){
        cout<<0;
        return 0;
    }
    vector<vector<int>>adj(n);
    for(int i=0;i<n-1;i++){
        int x,y; cin>>x>>y;
        x--,y--;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    vector<int>subtree_size(n,0),sum(n,0),ans(n,0);

    function<void(int,int)>dfs=[&](int node,int parent)->void{
        subtree_size[node]=1,sum[node]=0;
        for(int child:adj[node])if(child!=parent){
            dfs(child,node);
            subtree_size[node]+=subtree_size[child];
            sum[node]+=sum[child]+subtree_size[child];
        }
    };

    auto change=[&](int node,int child){
        sum[node]-=(sum[child]+subtree_size[child]);
        subtree_size[node]-=subtree_size[child];

        subtree_size[child]+=subtree_size[node];
        sum[child]+=(sum[node]+subtree_size[node]);
    };

    function<void(int,int)>reroot=[&](int node,int parent){
        ans[node]=sum[node];
        for(int child:adj[node])if(child!=parent){
            change(node,child);
            reroot(child,node);
            change(child,node);
        }
    };

    dfs(1,-1);
    reroot(1,-1);

    for(auto x:ans)cout<<x<<" ";
    return 0;
}