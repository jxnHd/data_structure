#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int maxConsecutiveGardens(int initial, int final, vector<int>& reserved) {
    sort(reserved.begin(), reserved.end());
    
    int maxConsecutive = 0;
    int consecutive = 0;

    for (int i = initial; i <= final; ++i) {
        if (binary_search(reserved.begin(), reserved.end(), i)) {
            
            consecutive = 0;
        } else {  
            ++consecutive;
            maxConsecutive = max(maxConsecutive, consecutive);
        }
    }

    return maxConsecutive;
}

int main() {
    int initial, final, n;
    
    cin >> initial;

    cin >> final;
    
    cin >> n;

    vector<int> reserved(n);
    
    for (int i = 0; i < n; ++i) {
        cin >> reserved[i];
    }

    
    int result = maxConsecutiveGardens(initial, final, reserved);

    // 輸出結果
    cout << result << endl;

    return 0;
}
