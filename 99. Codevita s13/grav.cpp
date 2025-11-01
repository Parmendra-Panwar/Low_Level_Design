#include <bits/stdc++.h>
using namespace std;

struct RampSegment {
    int startX, startY, endX, endY;
    int slope;          
    int interceptVal;
    int leftX, rightX;
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<RampSegment> ramps(n);
    for (int i = 0; i < n; ++i) {
        cin >> ramps[i].startX >> ramps[i].startY >> ramps[i].endX >> ramps[i].endY;
        ramps[i].leftX = min(ramps[i].startX, ramps[i].endX);
        ramps[i].rightX = max(ramps[i].startX, ramps[i].endX);

        if (ramps[i].startX == ramps[i].endX) {
            ramps[i].slope = 0;
            ramps[i].interceptVal = 0;
        } else {
            int dy = ramps[i].endY - ramps[i].startY;
            int dx = ramps[i].endX - ramps[i].startX;
            int slopeCalc = dy / dx;
            if (slopeCalc == 1) {
                ramps[i].slope = 1;
                ramps[i].interceptVal = ramps[i].startY - ramps[i].startX;
            } else {
                ramps[i].slope = -1;
                ramps[i].interceptVal = ramps[i].startY + ramps[i].startX;
            }
        }
    }

    int ballX, ballY;
    long long energy;
    cin >> ballX >> ballY >> energy;

    while (ballY > 0) {
        bool didMove = false;
        vector<int> rampsUnderBall;
        int idxSlide = -1;
        int dirSlide = 0;

        for (int i = 0; i < n; ++i) {
            if (ballX < ramps[i].leftX || ballX > ramps[i].rightX) continue;

            bool onRamp = false;
            if (ramps[i].slope == 1 && ballY - ballX == ramps[i].interceptVal) onRamp = true;
            if (ramps[i].slope == -1 && ballY + ballX == ramps[i].interceptVal) onRamp = true;

            if (onRamp) {
                rampsUnderBall.push_back(i);
                if (ramps[i].slope == 1 && ballX > ramps[i].leftX) {
                    idxSlide = i;
                    dirSlide = -1;
                }
                if (ramps[i].slope == -1 && ballX < ramps[i].rightX) {
                    idxSlide = i;
                    dirSlide = 1;
                }
            }
        }

        if (rampsUnderBall.size() > 1) {
            long long unlockCost = (long long)ballX * ballY;
            if (energy >= unlockCost) {
                energy -= unlockCost;
                if (idxSlide != -1 && energy > 0) {
                    ballX += dirSlide;
                    ballY--;
                    energy--;
                    didMove = true;
                } else if (idxSlide != -1 && energy == 0) {
                    break;
                }
            } else {
                break;
            }
        } else if (idxSlide != -1) {
            if (energy > 0) {
                ballX += dirSlide;
                ballY--;
                energy--;
                didMove = true;
            } else {
                break;
            }
        }

        if (!didMove) {
            int nextY = 0;
            for (int i = 0; i < n; ++i) {
                if (ballX >= ramps[i].leftX && ballX <= ramps[i].rightX) {
                    int intersectY = -1;
                    if (ramps[i].slope == 1) intersectY = ballX + ramps[i].interceptVal;
                    if (ramps[i].slope == -1) intersectY = ramps[i].interceptVal - ballX;

                    if (intersectY != -1 && intersectY < ballY && intersectY > nextY) {
                        nextY = intersectY;
                    }
                }
            }
            if (ballY == nextY) break;
            ballY = nextY;
            if (ballY == 0) break;
        }
    }

    cout << ballX << ' ' << ballY;
    return 0;
}
