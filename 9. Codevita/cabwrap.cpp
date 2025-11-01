#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> grid(n, vector<char>(m));

    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row; 
        for (int j = 0; j < m; ++j) {
            grid[i][j] = row[j];
        }
    }

    int sts = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == 'R') {
                
                if (j > 0 && j < m - 1 && grid[i][j - 1] == 'C' && grid[i][j + 1] == 'C') {
                    sts++;
                }
                
                else if (i > 0 && i < n - 1 && grid[i - 1][j] == 'C' && grid[i + 1][j] == 'C') {
                    sts++;
                }
            }
        }
    }

    cout<<sts<<endl;
}