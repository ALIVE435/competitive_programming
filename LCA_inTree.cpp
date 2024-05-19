#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
//lca in O((log^2)n)
//lowest common ancestor of any two nodes in tree, lca(x,y):lowest node such that both nodes are in its subtree
//lca(x,y)=farthest node from root for which both x and y are int its subtree
//lca(x,y)=the lowest parent of x for which y is in its subtree or vice-versa-->Binary searching on on parents
//check if kth parents of x has y in its subtree in O(1) using in-out trick
//1. find out kth parent of x(say z)-->O(logn)
//2. check if x is an ancestor of y-->O(1) :in-out trick

void dfs_in_out(int parent,int curr_node,vector<vector<int>>&adj,vector<int>&In,vector<int>&Out,int &globalTime){
    globalTime++;
    In[curr_node]=globalTime;
    for(auto child:adj[curr_node]){
        if(child!=parent){
            dfs_in_out(curr_node,child,adj,In,Out,globalTime);
        }
    }
    globalTime++;
    Out[curr_node]=globalTime;
}
void dfs(int parent,int curr_node,vector<vector<int>>&adj,vector<vector<int>>&parentsList){
    parentsList[curr_node][0]=parent;
    for(auto child:adj[curr_node]){
        if(child!=parent){
            dfs(curr_node,child,adj,parentsList);
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
bool isAncestor(int x,int y,vector<int>&In,vector<int>&Out){
    return ((In[y]>In[x]) && (Out[x]>Out[y]));//true if x is ancestor of y
}


//lowest common ancestor: O(logn.logn) ie O((log^2)n)
int lca(int x,int y,vector<vector<int>>&parentsList,vector<int>&In,vector<int>&Out){
    if(isAncestor(x,y,In,Out)) return x;
    if(isAncestor(y,x,In,Out)) return y;
    int start=0,end=parentsList.size();//size of row ie 1st dimension=n
    int ans=end;
    while(start<=end){  //O(logn)
        int mid=(start+end)/2;
        int parentOf_x=kthParent(mid,x,parentsList); //O(logn)
        if((parentOf_x==-1) || isAncestor(parentOf_x,y,In,Out)){//O(1)
            ans=min(ans,mid);
            end=mid-1;
        }
        else start=mid+1;  
    }
    return kthParent(ans,x,parentsList);
}
int main()
{
    int n,q; cin>>n>>q;
    vector<vector<int>>adj(n,vector<int>());
    for(int i=0;i<n-1;i++){
        int a,b;cin>>a>>b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    int root=0;//any random node can be root hera
    int maxParents=log2(n)+1;
    vector<vector<int>>parentsList(n,vector<int>(maxParents,-1));
    dfs(-1,root,adj,parentsList);//populate first ie 2^0th parents of all nodes

    for(int j=1;j<maxParents;j++){//populate all 2^jth parents of all nodes
        for(int i=0;i<n;i++){
            int intermediate=parentsList[i][j-1];
            if(intermediate!=-1) parentsList[i][j]=parentsList[intermediate][j-1];
        }
    }
    vector<int>inTime(n),outTime(n);
    int globalTime=0;
    dfs_in_out(-1,root,adj,inTime,outTime,globalTime);

    while(q--){ //for q queries
        int x,y; cin>>x>>y;
        x--,y--;
        if(x==y){
            cout<<x+1<<'\n';
        }
        else{
            cout<<lca(x,y,parentsList,inTime,outTime)+1<<"\n";
        }
    }

return 0;
}
