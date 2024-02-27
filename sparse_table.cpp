#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007  //range min/max query//gcd query as well 
                        //no updation

/*A 2d array, which stores the values of mn[i][j]=min element of an array which starts at index
i and has a length 2^j, for all 1<=i<=n and for all 0<=j<= ceil(logn)*/
/* j is the length equals to power of 2*/

/* min(l,r):
let x be the greatest power of 2<=(r-l+1), then min(l,r)=min(mn[l][x],mn[r-2^x+1][x])*/

/*mn[i][3]= min(mn[i][2],mn[i+2^2][2])
mn[i][j]=min(mn[i][j-1],mn[i+2^(j-1)][j-1])*/

int main()
{
    int n; cin>>n;
    vector<int>arr(n+1,0);
    for(int i=1;i<=n;i++)cin>>arr[i];
    int N=20; //max n can be 2^20;
    vector<vector<int>>mn(n+1,vector<int>(N+1,0));
    
    for(int i=1;i<=n;i++){      //base case
        mn[i][0]=arr[i];
    }
    for(int j=1;j<=N;j++){
        for(int i=1;(i+(1<<j)-1)<=n;i++){   //(i+2^j)-1<=n
            mn[i][j]=min(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
        }
    }
    int q; cin>>q;
    while(q--){
        int l,r; cin>>l>>r;
        int len=(r-l+1);
        int pw= 31-__builtin_clz(len);/*clz: count of leading zeroes in binary rep of no*/
                                      //greatest power of 2<=len
        cout<<min(mn[l][pw],mn[r-(1<<pw)+1][pw])<<" \n";

    }

return 0;
}
