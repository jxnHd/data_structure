#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
int maxPoints(vector<int>& benefit1, vector<int>& benefit2, int m) {
    int n = benefit1.size();
    vector<pair<int, int>> differences;
    for (int i = 0; i < n; ++i) {
        differences.push_back({benefit2[i] - benefit1[i], i});
    }
    sort(differences.begin(), differences.end());
    int maxPoints = accumulate(benefit2.begin(), benefit2.end(), 0);
    for (int i = 0; i < m; ++i) {
        int idx = differences[i].second;
        maxPoints += benefit1[idx] - benefit2[idx];
    }
    return maxPoints;
}
int main() {
    int n;   
    cin >> n;
    vector<int> reward1(n);
    for (int i = 0; i < n; ++i) {
        cin >> reward1[i];
    }
    vector<int> reward2(n);
    for (int i = 0; i < n; ++i) {
        cin >> reward2[i];
    }
    int m;
    cin >> m;   
    int result = maxPoints(reward1, reward2, m);
    cout << result << endl;
    return 0;
}