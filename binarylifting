#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007

//Given a tree find kth parent of node x in O(log(n))

void dfs(int parent,int curr_node,vector<vector<int>>&adj,vector<vector<int>>&parentsList){
    parentsList[curr_node][0]=parent;//2^0th ie 1st parent of each node
    for(auto child:adj[curr_node]){
        if(child!=parent){
            dfs(curr_node,child,adj,parentsList);
        }
    }
}
int kthParent(int x,int k,vector<vector<int>>&parentsList){
    int maxParent=parentsList[0].size();//log2(n)
    for(int i=0;i<maxParent;i++){
        if((k>>i)&1){
            if(x!=-1) x=parentsList[x][i]; //x--> 2^ith parent of x
        }
    }
    return x;
}
int main()
{
    int n; cin>>n;
    vector<vector<int>>adj(n);
    for(int i=0;i<n-1;i++){ //creating adjacency list
        int a,b; cin>>a>>b;
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }
    int root; cin>>root;
    int maxParent=log2(n)+1;
    vector<vector<int>>parentsList(n,vector<int>(maxParent,-1));//store 2^jth parent of each ith node
    dfs(-1,root,adj,parentsList);

    for(int j=1;j<maxParent;j++){ //O(logn)
        for(int i=0;i<n;i++){      //O(n)
            //populate parentsList[i][j] ie 2^j th parent of ith node
            //2^j th parent of i= 2^(j-1)th parent of (2^(j-1)th parent of i)
            int intermediate=parentsList[i][j-1];
            if(intermediate!=-1){
                parentsList[i][j]=parentsList[intermediate][j-1];
            }

        }
    }
    // we can put this loop inside the dfs function itself cause we know all the parents of curr_node everytime while dfs traversal
    /*void dfs(int parent,int curr_node,vector<vector<int>>&adj,vector<vector<int>>&parentsList){
        parentsList[curr_node][0]=parent;
        for(int j=1;j<maxParent;j++){
                int intermediate=parentsList[curr_node][j-1];
                if(intermediate!=-1){
                    parentsList[curr_node][j]=parentsList[intermediate][j-1];
                }
            }
        }
        for(auto child:adj[curr_node]){
            if(child!=parent){
                dfs(curr_node,child,adj,parentsList);
            }
        }
    }*/
    int x,k; cin>>x>>k;
    cout<<kthParent(x,k,parentsList);


return 0;
}
