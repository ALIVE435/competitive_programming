#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007/*range update and sum*/
//building,quering,and updating(lazy propagation)

const int N=2e5+5;
long long tree[4*N];
long long lazy[4*N];
long long arr[N];

long long construct(int ss, int se, int si) {
    if (ss == se) {
        return tree[si] = arr[ss];
    }
    int mid = (ss + se) / 2;
    tree[si] = construct(ss, mid, 2*si + 1) + construct(mid + 1, se, 2*si + 2);
    return tree[si];
}

void update(int ss, int se, int si, int l, int r, long long x) {
    if (lazy[si] > 0) {
        tree[si] += (se - ss + 1) * lazy[si];
        if (ss != se) {
            lazy[2*si + 1] += lazy[si];
            lazy[2*si + 2] += lazy[si];
        }
        lazy[si] = 0;
    }
    if (r < ss || l > se) return;
    if (ss >= l && se <= r) {
        tree[si] += (se - ss + 1) * x;
        if (ss != se) {
            lazy[2*si + 1] += x;
            lazy[2*si + 2] += x;
        }
        return;
    } 
    int mid = (ss + se) / 2;
    update(ss, mid, 2*si + 1, l, r, x);
    update(mid + 1, se, 2*si + 2, l, r, x);
    tree[si] = tree[2*si + 1] + tree[2*si + 2];
    
}

long long query(int ss, int se, int si, int l, int r) {
    if (lazy[si] > 0) {
        tree[si] += (se - ss + 1) * lazy[si];
        if (ss != se) {
            lazy[2*si + 1] += lazy[si];
            lazy[2*si + 2] += lazy[si];
        }
        lazy[si] = 0;
    }
    if (r < ss || l > se) return 0;
    if (ss >= l && se <= r) return tree[si];
    int mid = (ss + se) / 2;
    long long left_sum = query(ss, mid, 2*si + 1, l, r);
    long long right_sum = query(mid + 1, se, 2*si + 2, l, r);
    return left_sum + right_sum;
}

int main() {
    memset(lazy, 0, sizeof(lazy));
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) cin >> arr[i];
    construct(0, n - 1, 0);
    while (q--) {
        int k;
        cin >> k;
        if (k == 1) {
            int a, b;
            long long u;
            cin >> a >> b >> u;
            update(0, n - 1, 0, --a, --b, u);
        } else {
            int l;
            cin >> l;
            cout << query(0, n - 1, 0, l - 1, l - 1) << "\n";
        }
    }

    return 0;
}