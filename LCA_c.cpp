https://cses.fi/problemset/result/7408903/  :problem solution
//LCA in O(logn):standard approach
//Bring x and y to the same level
//find out the biggest kth parent of x for which it is not equal to the kth parent of y=z(say)
//return first parent of z

#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

void dfs(int parent,int curr_node,vector<vector<int>>&adj,vector<vector<int>>&parentsList,vector<int>&level){
    parentsList[curr_node][0]=parent;
    if(parent!=-1)level[curr_node]=level[parent]+1;
    for(auto child:adj[curr_node]){
        if(child!=parent){
            dfs(curr_node,child,adj,parentsList,level);
        }
    }
}
int kthParent(int k,int x,vector<vector<int>>&parentsList){
    int maxParent=parentsList[0].size();
    for(int i=0;i<maxParent;i++){
        if((k>>i) &1){
            if(x!=-1) x=parentsList[x][i];
        }
    }
    return x;
}

//lowest common ancestor: 
int lca(int x,int y,vector<vector<int>>&parentsList,vector<int>&level){
    if(x==y) return x;
    ///bring both x and y to the same level
    if(level[x]<level[y]) swap(x,y);
    int differenceInLevel=level[x]-level[y];
    x=kthParent(differenceInLevel,x,parentsList);//O(logn)
    if(x==y) return x;

    int maxParent=parentsList[0].size();//O(logn)
    for(int i=maxParent-1;i>=0;i--){
        int parentOfX=parentsList[x][i];
        int parentOfY=parentsList[y][i];
        if(parentOfX!=parentOfY){
            x=parentOfX;
            y=parentOfY;
        }
    }
    return parentsList[x][0];//at last return first parent of x;
}
int main()
{
    int n,q; cin>>n>>q;
    vector<vector<int>>adj(n,vector<int>());
    for(int i=1;i<n;i++){
        int a;cin>>a;
        adj[a-1].push_back(i);
    }
    int root=0;
    int maxParents=log2(n)+1;
    vector<vector<int>>parentsList(n,vector<int>(maxParents,-1));
    vector<int>level(n);
    dfs(-1,root,adj,parentsList,level);//populate first ie 2^0th parents of all nodes
    for(int j=1;j<maxParents;j++){//populate all 2^jth parents of all nodes
        for(int i=0;i<n;i++){
            int intermediate=parentsList[i][j-1];
            if(intermediate!=-1) parentsList[i][j]=parentsList[intermediate][j-1];
        }
    }

    while(q--){
        int x,y; cin>>x>>y;
        x--,y--;
        if(x==y){
            cout<<x+1<<'\n';
        }
        else{
            cout<<lca(x,y,parentsList,level)+1<<"\n";
        }
    }

return 0;
}
