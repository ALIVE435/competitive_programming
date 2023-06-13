#include<bits/stdc++.h>
using namespace std;
void fun(int ind,int cnt, vector<int>&heights,int n,int &ans){     //frog jump:https://www.codingninjas.com/codestudio/problems/frog-jump_3621012
    if(ind==n-1){                                                  //going from 0 t0 n ie bottom-up approach
        ans=min(cnt,ans);                                          //at each index from 0 to n-1 , either go +1 or +2
        return;
    }
    cnt+=abs(heights[ind+1]-heights[ind]);
    fun(ind+1,cnt,heights,n,ans);
    if(ind< n-1)cnt-=abs(heights[ind+1]-heights[ind]);
    if(ind<n-2){
        cnt+=abs(heights[ind+2]-heights[ind]);
        fun(ind+2,cnt,heights,n,ans);
        if(ind< n-2)cnt+=abs(heights[ind+2]-heights[ind]);
    }
}
int main()
{
    int n; cin>>n;
    vector<int>heights(n,0);
    for(int i=0;i<n;i++)cin>>heights[i];
    int ans=INT_MAX;
    fun(0,0,heights,n,ans);
    cout<<ans;

return 0;
}

//top-down method: from n to 0
#include <bits/stdc++.h> 
using namespace std;

int fun(int ind,vector<int> &heights){
    if(ind==0)return 0;
    int left=fun(ind-1,heights)+abs(heights[ind]-heights[ind-1]);
    int right=INT_MAX;
    if(ind>1)
    right=fun(ind-2,heights)+abs(heights[ind]-heights[ind-2]);
    return min(left,right);

}
int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    return fun(n-1,heights);   
}

//dp approach:top-down ie. memoization :recursive dp
#include <bits/stdc++.h> 
using namespace std;

int fun(int ind,vector<int> &heights,vector<int> &dp){
    if(ind==0)return 0;
    if(dp[ind]!=-1)return dp[ind];
    int left=fun(ind-1,heights,dp)+abs(heights[ind]-heights[ind-1]);
    int right=INT_MAX;
    if(ind>1)
    right=fun(ind-2,heights,dp)+abs(heights[ind]-heights[ind-2]);
    dp[ind]= min(left,right);
    return dp[ind];

}
int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int>dp(n,-1);
    return fun(n-1,heights,dp);
}

//dp approach: tabulation: bottom-up: iterative dp
#include <bits/stdc++.h> 

int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    vector<int>dp(n,0);
    dp[0]=0;
    for(int i=1;i<n;i++){
        int left=dp[i-1]+(abs(heights[i]-heights[i-1]));
        int right=INT_MAX;
        if(i>1)right=dp[i-2]+(abs(heights[i]-heights[i-2]));
        dp[i]=min(left,right);
    }
    return dp[n-1];
}

//most optimised space: space optimization
#include <bits/stdc++.h> 

int frogJump(int n, vector<int> &heights)
{
    // Write your code here.
    int pre=0;
    int pre2=0;
    for(int i=1;i<n;i++){
        int left=pre+abs(heights[i]-heights[i-1]);
        int right=INT_MAX;
        if(i>1)right=pre2+abs(heights[i]-heights[i-2]);

        int curr=min(left,right);
        pre2=pre;
        pre=curr;
    }
    return pre;
    
}
