#include <bits/stdc++.h>
using namespace std;

vector<string> segmentLines(const vector<string> &inputLines, int stepSize) {
    int maxLength = 0;
    for (const auto &line : inputLines)
        maxLength = max(maxLength, (int)line.size());

    vector<string> paddedLines = inputLines;
    for (auto &line : paddedLines)
        if ((int)line.size() < maxLength)
            line += string(maxLength - line.size(), ' ');

    if (maxLength < 3) return {};

    int blocksCount = (maxLength + (stepSize - 3)) / stepSize;
    vector<string> segments;

    for (int idx = 0; idx < blocksCount; idx++) {
        int startIndex = idx * stepSize;
        string combinedBlock;
        for (int row = 0; row < 3; row++) {
            string rowString = paddedLines[row];
            if (startIndex + 3 > (int)rowString.size())
                rowString += string(startIndex + 3 - rowString.size(), ' ');
            combinedBlock += rowString.substr(startIndex, 3);
        }
        segments.push_back(combinedBlock);
    }
    return segments;
}

vector<string> identifyBlocks(const vector<string> &inputLines, int expectedBlocks = -1) {
    vector<string> byStep4 = segmentLines(inputLines, 4);
    vector<string> byStep3 = segmentLines(inputLines, 3);

    if (expectedBlocks > 0) {
        if ((int)byStep4.size() == expectedBlocks)
            return byStep4;
        if ((int)byStep3.size() == expectedBlocks)
            return byStep3;
    }

    auto nonEmptyCount = [](const vector<string> &blocks) {
        int count = 0;
        for (const auto &block : blocks) {
            bool isEmpty = true;
            for (char ch : block)
                if (ch != ' ') {
                    isEmpty = false;
                    break;
                }
            if (!isEmpty) count++;
        }
        return count;
    };

    return (nonEmptyCount(byStep4) >= nonEmptyCount(byStep3)) ? byStep4 : byStep3;
}

string convertToBinary(const string &block) {
    string binaryStr;
    for (char ch : block)
        binaryStr += (ch == ' ') ? '0' : '1';
    return binaryStr;
}

map<string, string> createPatternMap(const vector<string> &inputLines, const vector<string> &symbols) {
    auto codeBlocks = identifyBlocks(inputLines, (int)symbols.size());
    map<string, string> patternToSymbol;
    for (size_t i = 0; i < min(codeBlocks.size(), symbols.size()); i++)
        patternToSymbol[convertToBinary(codeBlocks[i])] = symbols[i];
    return patternToSymbol;
}

vector<string> parseTokens(const vector<string> &inputLines, const map<string, string> &patternMapping) {
    auto codeBlocks = identifyBlocks(inputLines);
    vector<string> resultTokens;
    string tempBuffer;

    for (const auto &block : codeBlocks) {
        string binaryVal = convertToBinary(block);
        auto it = patternMapping.find(binaryVal);
        if (it != patternMapping.end()) {
            const string &sym = it->second;
            if (isdigit(sym[0]))
                tempBuffer += sym;
            else {
                if (!tempBuffer.empty()) {
                    resultTokens.push_back(tempBuffer);
                    tempBuffer.clear();
                }
                resultTokens.push_back(sym);
            }
        }
    }

    if (!tempBuffer.empty())
        resultTokens.push_back(tempBuffer);

    return resultTokens;
}

string binaryOr(const string &val1, const string &val2) {
    int length = max(val1.size(), val2.size());
    string padded1 = string(length - val1.size(), '0') + val1;
    string padded2 = string(length - val2.size(), '0') + val2;
    string output;
    for (int i = 0; i < length; i++)
        output += (padded1[i] == '1' || padded2[i] == '1') ? '1' : '0';
    return output;
}

string binaryAnd(const string &val1, const string &val2) {
    int length = max(val1.size(), val2.size());
    string padded1 = string(length - val1.size(), '0') + val1;
    string padded2 = string(length - val2.size(), '0') + val2;
    string output;
    for (int i = 0; i < length; i++)
        output += (padded1[i] == '1' && padded2[i] == '1') ? '1' : '0';
    return output;
}

string binaryNot(const string &val) {
    string output;
    for (char ch : val)
        output += (ch == '1') ? '0' : '1';
    return output;
}

string convertNumToBinary(const string &numStr, const map<string, string> &numToBinMap) {
    string binOut;
    for (char ch : numStr) {
        string key(1, ch);
        auto it = numToBinMap.find(key);
        binOut += (it != numToBinMap.end()) ? it->second : string(9, '0');
    }
    return binOut;
}

string convertBinaryToNum(const string &binStr, const map<string, string> &binToNumMap) {
    if (binStr.empty())
        return "0";

    string paddedStr = binStr;
    int rem = paddedStr.size() % 9;
    if (rem)
        paddedStr = string(9 - rem, '0') + paddedStr;

    string resultNum;
    for (size_t i = 0; i < paddedStr.size(); i += 9) {
        string segment = paddedStr.substr(i, 9);
        auto it = binToNumMap.find(segment);
        resultNum += (it != binToNumMap.end()) ? it->second : "0";
    }

    size_t idx = 0;
    while (idx + 1 < resultNum.size() && resultNum[idx] == '0')
        idx++;
    return resultNum.substr(idx);
}

string evaluateExpr(const vector<string> &tokens, const map<string, string> &numReverseMap) {
    stack<string> valStack, opStack;

    auto executeOp = [&](const string &op) {
        if (op == "~") {
            if (valStack.empty()) return;
            string v = valStack.top();
            valStack.pop();
            valStack.push(binaryNot(v));
        } else {
            if (valStack.size() < 1) return;
            string operand2 = valStack.top();
            valStack.pop();
            string operand1 = valStack.empty() ? string(9, '0') : valStack.top();
            if (!valStack.empty()) valStack.pop();
            valStack.push((op == "|") ? binaryOr(operand1, operand2) : binaryAnd(operand1, operand2));
        }
    };

    auto getPriority = [&](const string &op) {
        if (op == "~") return 3;
        if (op == "|") return 2;
        if (op == "&") return 1;
        return 0;
    };

    for (const auto &token : tokens) {
        if (token == "(")
            opStack.push(token);
        else if (token == ")") {
            while (!opStack.empty() && opStack.top() != "(") {
                executeOp(opStack.top());
                opStack.pop();
            }
            if (!opStack.empty()) opStack.pop();
        } else if (token == "~" || token == "|" || token == "&") {
            while (!opStack.empty() && opStack.top() != "(" && getPriority(opStack.top()) >= getPriority(token)) {
                executeOp(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        } else {
            valStack.push(convertNumToBinary(token, numReverseMap));
        }
    }

    while (!opStack.empty()) {
        executeOp(opStack.top());
        opStack.pop();
    }

    return valStack.empty() ? "" : valStack.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> inputLines(9);
    for (int i = 0; i < 9; i++)
        getline(cin, inputLines[i]);

    vector<string> digitGrid(inputLines.begin(), inputLines.begin() + 3);
    vector<string> opsGrid(inputLines.begin() + 3, inputLines.begin() + 6);
    vector<string> exprGrid(inputLines.begin() + 6, inputLines.end());

    vector<string> digitSymbols = {"0","1","2","3","4","5","6","7","8","9"};
    vector<string> opsSymbols = {"|", "&", "~", "(", ")"};

    auto digitPatterns = createPatternMap(digitGrid, digitSymbols);
    auto opsPatterns = createPatternMap(opsGrid, opsSymbols);

    map<string, string> fullPatterns = digitPatterns;
    fullPatterns.insert(opsPatterns.begin(), opsPatterns.end());

    map<string, string> reverseDigitMap, digitBinMap;
    for (const auto &pair : digitPatterns) {
        digitBinMap[pair.first] = pair.second;
        reverseDigitMap[pair.second] = pair.first;
    }

    auto tokens = parseTokens(exprGrid, fullPatterns);
    string evalResult = evaluateExpr(tokens, reverseDigitMap);
    cout << convertBinaryToNum(evalResult, digitBinMap);

    return 0;
}
