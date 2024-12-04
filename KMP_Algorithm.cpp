#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
#define int long long
/* lps[i] = length of the longest proper prefix which is also a proper suffix of st[0, ..., i]
NOTE: Prefix and suffix can be overlapping but they should not be equal to the entire string.
eg. aaaa -> aaa ie lps[n-1] = 3
abab -> ab ie lps[n-1] = 2
*/

void findLPS(string &st, vector<int> &lps) { //https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/   O(n+n)
    int n = st.length();                     //https://www.geeksforgeeks.org/problems/check-if-strings-are-rotations-of-each-other-or-not-1587115620/1
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

//O(n+m)
vector<int> kmp(string &String, string &pattern, vector<int> &lps) { //https://www.youtube.com/watch?v=qases-9gOpk&t=2347s&ab_channel=codestorywithMIK
    int n = String.length(), m = pattern.length();                  //https://www.youtube.com/watch?v=V5-7GzOfADQ&ab_channel=AbdulBari
    pattern = " " + pattern;
    vector<int>piTable(m + 1, 0);
    vector<int> ans;
    for (int i = 1; i <= m; i++) piTable[i] = lps[i - 1];
    int i = 0, j = 0;
    while (i < n) {
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
