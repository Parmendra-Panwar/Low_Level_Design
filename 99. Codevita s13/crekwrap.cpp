#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int rowCount, colCount;
    cin >> rowCount >> colCount;

    vector<string> board(rowCount);
    for (int r = 0; r < rowCount; r++) {
        board[r].resize(colCount);
        for (int c = 0; c < colCount; c++) {
            cin >> board[r][c];
        }
    }

    vector<int> fullRowRods, fullColRods;
    for (int r = 0; r < rowCount; r++) {
        if (all_of(board[r].begin(), board[r].end(), [](char ch){ return ch != '.'; }))
            fullRowRods.push_back(r);
    }
    for (int c = 0; c < colCount; c++) {
        bool colFull = true;
        for (int r = 0; r < rowCount; r++)
            if (board[r][c] == '.') colFull = false;
        if (colFull) fullColRods.push_back(c);
    }

    vector<vector<bool>> crossMark(rowCount, vector<bool>(colCount, false));
    for (int c : fullColRods) {
        for (int r = 0; r < rowCount; r++) {
            int leftCell = c - 1, rightCell = c + 1;
            if (leftCell >= 0 && rightCell < colCount &&
                board[r][leftCell] == 'C' && board[r][rightCell] == 'C')
                crossMark[r][c] = true;
        }
    }
    for (int r : fullRowRods) {
        for (int c = 0; c < colCount; c++) {
            int topCell = r - 1, bottomCell = r + 1;
            if (topCell >= 0 && bottomCell < rowCount &&
                board[topCell][c] == 'C' && board[bottomCell][c] == 'C')
                crossMark[r][c] = true;
        }
    }

    vector<vector<bool>> cablePresence(rowCount, vector<bool>(colCount, false));
    for (int r = 0; r < rowCount; r++)
        for (int c = 0; c < colCount; c++)
            if (board[r][c] == 'C' || crossMark[r][c])
                cablePresence[r][c] = true;

    vector<vector<int>> adjacencyList(rowCount * colCount);
    int dRow[4] = {-1, 0, 1, 0};
    int dCol[4] = {0, 1, 0, -1};

    for (int r = 0; r < rowCount; r++) {
        for (int c = 0; c < colCount; c++) {
            if (!cablePresence[r][c]) continue;
            int currentId = r * colCount + c;
            for (int dir = 0; dir < 4; dir++) {
                int nr = r + dRow[dir], nc = c + dCol[dir];
                if (nr >= 0 && nr < rowCount && nc >= 0 && nc < colCount && cablePresence[nr][nc])
                    adjacencyList[currentId].push_back(nr * colCount + nc);
            }
        }
    }

    int startNode = -1;
    for (int r = 0; r < rowCount && startNode == -1; r++)
        for (int c = 0; c < colCount; c++)
            if (cablePresence[r][c] && adjacencyList[r * colCount + c].size() == 1) {
                startNode = r * colCount + c;
                break;
            }

    vector<bool> visitedNodes(rowCount * colCount, false);
    vector<int> horizontalSum(rowCount, 0), verticalSum(colCount, 0);

    int currentNode = startNode, previousNode = -1;
    visitedNodes[currentNode] = true;

    while (true) {
        int r = currentNode / colCount, c = currentNode % colCount;
        int nextNode = -1;
        for (int neighbor : adjacencyList[currentNode])
            if (neighbor != previousNode && !visitedNodes[neighbor]) {
                nextNode = neighbor;
                break;
            }

        if (crossMark[r][c] && previousNode != -1) {
            int pr = previousNode / colCount, pc = previousNode % colCount;
            int directionSign = (board[r][c] == 'C') ? 1 : -1;

            if (pr == r)
                verticalSum[c] += ((pc < c) ? 1 : -1) * directionSign;
            else
                horizontalSum[r] += ((pr < r) ? 1 : -1) * directionSign;
        }

        if (nextNode == -1) break;
        previousNode = currentNode;
        currentNode = nextNode;
        visitedNodes[currentNode] = true;
    }

    long long result = 0;
    for (int r : fullRowRods) result += abs(horizontalSum[r]) / 2;
    for (int c : fullColRods) result += abs(verticalSum[c]) / 2;

    cout << result;
    return 0;
}
