#pragma GCC optimize("Ofast","inline","-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> findMaxAllure(const vector<vector<int>>& elements, const vector<int>& inquiries) {
    vector<int> responses;

    for (int i = 0; i < inquiries.size(); ++i) {
        int currentInquiry = inquiries[i];
        int maxAllure = 0;

        for (const auto& element : elements) {
            int cost = element[0];
            int allure = element[1];

            if (cost <= currentInquiry) {
                maxAllure = max(maxAllure, allure);
            }
        }

        responses.push_back(maxAllure);
    }

    return responses;
}

int main() {
    int m, n;

    // Input the number of elements
    cin >> m >>n;

    // Input the elements array
    vector<vector<int>> elements(m, vector<int>(2));
    for (int i = 0; i < m; ++i) {
        cin >> elements[i][0] >> elements[i][1];
    }

    
    // Input the inquiries array
    vector<int> inquiries(n);
    for (int i = 0; i < n; ++i) {
        cin >> inquiries[i];
    }

    vector<int> responses = findMaxAllure(elements, inquiries);

    // Print the responses
    //cout << "Responses: ";
    for (int response : responses) {
        cout << response << " ";
    }
    cout << endl;

    return 0;
}
