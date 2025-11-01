#include <bits/stdc++.h>
using namespace std;

void shiftRow(vector<vector<char>>& mat, int r, char d) {
    int sz = mat.size();
    if (d == 'L') {
        char temp = mat[r][0];
        for (int j = 0; j < sz - 1; j++) mat[r][j] = mat[r][j + 1];
        mat[r][sz - 1] = temp;
    } else {
        char temp = mat[r][sz - 1];
        for (int j = sz - 1; j > 0; j--) mat[r][j] = mat[r][j - 1];
        mat[r][0] = temp;
    }
}

void shiftCol(vector<vector<char>>& mat, int c, char d) {
    int sz = mat.size();
    if (d == 'U') {
        char temp = mat[0][c];
        for (int i = 0; i < sz - 1; i++) mat[i][c] = mat[i + 1][c];
        mat[sz - 1][c] = temp;
    } else {
        char temp = mat[sz - 1][c];
        for (int i = sz - 1; i > 0; i--) mat[i][c] = mat[i - 1][c];
        mat[0][c] = temp;
    }
}

bool sameMatrix(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] != b[i][j]) return false;
    return true;
}

bool oneDiff(const vector<vector<char>>& a, const vector<vector<char>>& b) {
    int cnt = 0, n = a.size(), m = a[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (a[i][j] != b[i][j]) cnt++;
    return cnt == 1;
}

int main() {
    int n; 
    cin >> n;
    vector<vector<char>> init(n, vector<char>(n)), fin(n, vector<char>(n));
    for (auto& r : init) for (auto& c : r) cin >> c;
    for (auto& r : fin) for (auto& c : r) cin >> c;
    int t; 
    cin >> t;
    vector<string> ops(t);
    for (int i = 0; i < t; i++) cin >> ops[i];

    vector<vector<char>> cur = init;
    for (auto& s : ops) {
        char typ = s[0], dir = s[2];
        int id = s[1] - '0';
        if (typ == 'R') shiftRow(cur, id, dir);
        else shiftCol(cur, id, dir);
    }

    if (sameMatrix(cur, fin)) {
        cout << "Cube Solved";
        return 0;
    }

    if (oneDiff(init, fin)) {
        cout << "Cube Faulty";
        return 0;
    }

    for (int i = 0; i < t; i++) {
        vector<vector<char>> temp = init;
        for (int j = 0; j < t; j++) {
            if (i == j) continue;
            char typ = ops[j][0], dir = ops[j][2];
            int id = ops[j][1] - '0';
            if (typ == 'R') shiftRow(temp, id, dir);
            else shiftCol(temp, id, dir);
        }
        if (sameMatrix(temp, fin)) {
            cout << "Instruction Faulty at step " << i + 1;
            return 0;
        }
    }

    cout << "Cannot Determine";
    return 0;
}