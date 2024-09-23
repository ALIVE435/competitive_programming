#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define int long long

void findLPS(string &st, vector<int> &lps) {
    int n = st.length();
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < n) {
        if (st[i] == st[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else // (st[i] != st[len])
        {
            if (len != 0) {
                len = lps[len - 1];
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> kmp(string &String, string &pattern, vector<int> &lps) {
    int n = String.length(), m = pattern.length();
    pattern = " " + pattern;
    vector<int>piTable(m + 1, 0);
    vector<int> ans;
    for (int i = 1; i <= m; i++) piTable[i] = lps[i - 1];
    int i = 0, j = 0;
    while (i < n) {
        cout << i << " " << j << "\n";
        if (j == m) {
            ans.push_back(i - j + 1);
            j = piTable[j];
        }
        else if (String[i] == pattern[j + 1]) i++, j++;
        else {
            if (j != 0) j = piTable[j];
            else i++;
        }
    }
    if (j == m) {
        ans.push_back(i - j + 1);
    }
    return ans;
}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string String, pattern; cin >> String >> pattern;
    vector<int>lps(pattern.length(), 0);
    findLPS(pattern, lps);
    for (auto x : lps) cout << x << " ";
    cout << "\n";
    vector<int> ans = kmp(String, pattern, lps);
    for (auto x : ans) cout << x << " ";
    return 0;
}