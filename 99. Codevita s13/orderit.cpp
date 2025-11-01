#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string dummy;
    cin >> dummy;
    cin.ignore();

    vector<string> src(n), dst(n);
    for (int i = 0; i < n; ++i) getline(cin, src[i]);
    cin >> dummy;
    cin.ignore();
    for (int i = 0; i < n; ++i) getline(cin, dst[i]);

    if (src == dst) {
        cout << 0;
        return 0;
    }

    unordered_map<string, int> indexMap;
    for (int i = 0; i < n; ++i) indexMap[dst[i]] = i;

    vector<int> permA(n), permB(n);
    for (int i = 0; i < n; ++i) permA[i] = indexMap[src[i]];
    iota(permB.begin(), permB.end(), 0);

    map<vector<int>, int> distA, distB;
    queue<vector<int>> qA, qB;
    distA[permA] = 0;
    distB[permB] = 0;
    qA.push(permA);
    qB.push(permB);

    auto generateMoves = [&](const vector<int>& arr) {
        vector<vector<int>> states;
        for (int l = 0; l < n; ++l) {
            for (int r = l; r < n; ++r) {
                vector<int> reduced;
                for (int x = 0; x < l; ++x) reduced.push_back(arr[x]);
                for (int x = r + 1; x < n; ++x) reduced.push_back(arr[x]);
                for (int pos = 0; pos <= (int)reduced.size(); ++pos) {
                    if (pos == l) continue;
                    vector<int> curr = reduced;
                    curr.insert(curr.begin() + pos, arr.begin() + l, arr.begin() + r + 1);
                    states.push_back(curr);
                }
            }
        }
        return states;
    };

    while (!qA.empty() && !qB.empty()) {
        if (qA.size() <= qB.size()) {
            int sz = qA.size();
            while (sz--) {
                auto now = qA.front(); qA.pop();
                int d = distA[now];
                for (auto& nxt : generateMoves(now)) {
                    if (distA.count(nxt)) continue;
                    if (distB.count(nxt)) {
                        cout << d + 1 + distB[nxt];
                        return 0;
                    }
                    distA[nxt] = d + 1;
                    qA.push(nxt);
                }
            }
        } else {
            int sz = qB.size();
            while (sz--) {
                auto now = qB.front(); qB.pop();
                int d = distB[now];
                for (auto& nxt : generateMoves(now)) {
                    if (distB.count(nxt)) continue;
                    if (distA.count(nxt)) {
                        cout << d + 1 + distA[nxt];
                        return 0;
                    }
                    distB[nxt] = d + 1;
                    qB.push(nxt);
                }
            }
        }
    }

    cout << n;
    return 0;
}