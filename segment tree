#include<bits/stdc++.h> 
using namespace std;


//https://codeforces.com/contest/1927/problem/D :used segment tree(max and min query)

int segmax[800004];
int segmin[800004];
void build(int left,int right,int node,int arr[]){
    if(left==right){
        segmax[node]=left;
        segmin[node]=left;
        return;
    }
    int mid=(left+right)/2;
    build(left,mid,2*node+1,arr);
    build(mid+1,right,2*node+2,arr);
    segmax[node]=arr[segmax[2*node+1]]>arr[segmax[2*node+2]]?segmax[2*node+1]:segmax[2*node+2];
    segmin[node]=arr[segmin[2*node+1]]<arr[segmin[2*node+2]]?segmin[2*node+1]:segmin[2*node+2];
    return;
}
int mxquery(int left,int right,int ql,int qr,int node,int arr[],int n){
    if(right<ql || left>qr)return INT_MAX;
    else if(ql<=left && qr>=right)return segmax[node];
    else{
        int mid=(left+right)/2;
        int l=mxquery(left,mid,ql,qr,2*node+1,arr,n);
        int r=mxquery(mid+1,right,ql,qr,2*node+2,arr,n);
        if((l>=0 && l<=n-1) && (r>=0 && r<=n-1)){
            if(arr[l]<arr[r])return r;
            else return l;
        }
        else if(l>=0 && l<=n-1)return l;
        else return r;
    }
}
int mnquery(int left,int right,int ql,int qr,int node,int arr[],int n){
    if(right<ql || left>qr)return INT_MAX;
    else if(ql<=left && qr>=right)return segmin[node];
    else{
        int mid=(left+right)/2;
        int l=mnquery(left,mid,ql,qr,2*node+1,arr,n);
        int r=mnquery(mid+1,right,ql,qr,2*node+2,arr,n);
        if((l>=0 && l<=n-1) && (r>=0 && r<=n-1)){
            if(arr[l]<arr[r])return l;
            else return r;
        }
        else if(l>=0 && l<=n-1)return l;
        else return r;
    }
}

int main() {
    int t;cin>>t;
    while (t--) {
        int n; cin>>n;
        int arr[n];
        for(int i=0;i<n;i++)cin>>arr[i];
        build(0,n-1,0,arr);
        int q; cin>>q;
        while(q--){
            int l,r; cin>>l>>r;
            l--,r--;
            int mx=mxquery(0,n-1,l,r,0,arr,n);
            int mn=mnquery(0,n-1,l,r,0,arr,n);
            if(arr[mx]==arr[mn])cout<<"-1 -1\n";
            else cout<<++mx<<" "<<++mn<<"\n";
        }
    }

    return 0;
}
