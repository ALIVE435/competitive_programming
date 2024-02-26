#include<bits/stdc++.h>//there is 2D BIT also :https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/

using namespace std; //fenwick tree(Binary Indexed Tree/BIT)//n-sized array not a tree
#define mod 1000000007  //prefix sum => range sum
                        
// point update(not range update) change the value at an index by x,assign
// the value at an index to x

/*a fenwick tree is a simple array, lets call it G.
g[i]=sum of all elements of the subarray which end at i, and has a length of 2^x, where x is the least
significant bit in the binary rep of i.*/

const int N=2e5+1; //size of array
int fen[N];  //1-based indexing

void update(int i,int add){
    while(i<=N){
        fen[i]+=add;   //all those fen that include a[i] in their sum,needs to be updated(incresed by add)
        i+=(i& (-i)); //in case of a[i] is assigned add,fen[i]+=(add-a[i]) where i is the given index
    }            //i=i+2^(lsb(i))
}
int sum(int i){   //gives prefix sum of index i
    int s=0;
    while(i>0){
        s+=fen[i];
        i=i-(i& (-i));/*this is the  way to get 2^x, where x is the lsb of i
                      i & (-i)=2^(lsb(i))*/
    }
    return s;
}
int range_sum(int l,int r){
    return sum(r)-sum(l-1);
}
int main()
{
    int x=1;
    cout<<(1&(-1));   
return 0;
}