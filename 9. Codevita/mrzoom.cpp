#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
using namespace std;

vector<string> input_lines;
int position = 0;

vector<string> read_block() {
    vector<string> block;
    while ((int)block.size() < 3 && position < (int)input_lines.size()) {
        block.push_back(input_lines[position]);
        position++;
    }
    int width = 0;
    for (auto &line : block) width = max(width, (int)line.size());
    for (auto &line : block) line += string(width - line.size(), ' ');
    return block;
}

vector<string> split_to_patterns(const vector<string>& block) {
    if (block.empty()) return {};
    int width = (int)block[0].size();
    vector<string> pieces;
    for (int c = 0; c < width; c += 3) {
        string piece;
        for (int r = 0; r < 3; r++) {
            piece += block[r].substr(c, 3);
        }
        if (piece.find_first_not_of(' ') != string::npos) {
            pieces.push_back(piece);
        }
    }
    return pieces;
}

string led_to_bits(const string& block) {
    string bits;
    for (char c : block) bits += (c != ' ' ? '1' : '0');
    return bits;
}

int main() {
    string line;
    while (getline(cin, line)) {
        if (!line.empty() || !input_lines.empty()) {
            input_lines.push_back(line);
        }
    }

    vector<string> digits_block = read_block();
    vector<string> digit_patterns = split_to_patterns(digits_block);
    vector<string> ops_block = read_block();
    vector<string> op_patterns = split_to_patterns(ops_block);
    vector<string> expr_block = read_block();
    vector<string> expr_patterns = split_to_patterns(expr_block);

    vector<string> digit_bits;
    for (auto &pat : digit_patterns) digit_bits.push_back(led_to_bits(pat));
    vector<string> op_bits;
    for (auto &pat : op_patterns) op_bits.push_back(led_to_bits(pat));
    vector<string> expr_bits;
    for (auto &pat : expr_patterns) expr_bits.push_back(led_to_bits(pat));

    unordered_map<string, string> digit_map;
    for (int i = 0; i < 10; i++) digit_map[digit_bits[i]] = to_string(i);

    vector<string> operators = {"||", "&&", "!", "(", ")"};
    unordered_map<string, string> op_map;
    for (int i = 0; i < 5; i++) op_map[op_bits[i]] = operators[i];

    vector<string> tokens;
    for (auto &b : expr_bits) {
        if (digit_map.count(b)) tokens.push_back(digit_map[b]);
        else tokens.push_back(op_map[b]);
    }

    vector<string> final_tokens;
    for (size_t i = 0; i < tokens.size(); i++) {
        if (all_of(tokens[i].begin(), tokens[i].end(), ::isdigit)) {
            string tmp = tokens[i];
            while (i+1 < tokens.size() && all_of(tokens[i+1].begin(), tokens[i+1].end(), ::isdigit)) {
                tmp += tokens[i+1];
                i++;
            }
            final_tokens.push_back(tmp);
        } else {
            final_tokens.push_back(tokens[i]);
        }
    }

    unordered_map<string, string> digit_map_rev;
    for (int i = 0; i < 10; i++) digit_map_rev[to_string(i)] = digit_bits[i];

    auto num_to_bits = [&](const string& num) {
        string res;
        for (char c : num) res += digit_map_rev[string(1, c)];
        return res;
    };

    auto bits_to_num = [&](const string& bits) {
        string out;
        for (size_t i = 0; i < bits.size(); i += 9) {
            string chunk = bits.substr(i, 9);
            out += digit_map[chunk];
        }
        return stoi(out);
    };

    unordered_map<string, int> precedence = {{"!", 3}, {"||", 2}, {"&&", 1}};

    auto apply_op = [&](const string& op, const string& a, const string& b = "") {
        if (op == "!") {
            string res;
            for (char ch : a) res += (ch == '0' ? '1' : '0');
            return res;
        }
        size_t max_len = max(a.size(), b.size());
        string a_pad(max_len - a.size(), '0');
        string b_pad(max_len - b.size(), '0');
        string A = a_pad + a;
        string B = b_pad + b;
        string res(max_len, '0');
        if (op == "&&") {
            for (size_t i = 0; i < max_len; i++) {
                res[i] = (A[i] == '1' && B[i] == '1') ? '1' : '0';
            }
        } else if (op == "||") {
            for (size_t i = 0; i < max_len; i++) {
                res[i] = (A[i] == '1' || B[i] == '1') ? '1' : '0';
            }
        }
        return res;
    };

    vector<string> values_stack;
    vector<string> ops_stack;

    for (size_t i = 0; i < final_tokens.size(); i++) {
        string t = final_tokens[i];
        if (all_of(t.begin(), t.end(), ::isdigit)) {
            values_stack.push_back(num_to_bits(t));
        } else if (t == "(") {
            ops_stack.push_back(t);
        } else if (t == ")") {
            while (!ops_stack.empty() && ops_stack.back() != "(") {
                string op = ops_stack.back();
                ops_stack.pop_back();
                if (op == "!") {
                    string val = values_stack.back(); values_stack.pop_back();
                    values_stack.push_back(apply_op(op, val));
                } else {
                    string b = values_stack.back(); values_stack.pop_back();
                    string a = values_stack.back(); values_stack.pop_back();
                    values_stack.push_back(apply_op(op, a, b));
                }
            }
            if (!ops_stack.empty()) ops_stack.pop_back();
        } else {
            while (!ops_stack.empty() && ops_stack.back() != "(" && precedence[ops_stack.back()] >= precedence[t]) {
                string op = ops_stack.back();
                ops_stack.pop_back();
                if (op == "!") {
                    string val = values_stack.back(); values_stack.pop_back();
                    values_stack.push_back(apply_op(op, val));
                } else {
                    string b = values_stack.back(); values_stack.pop_back();
                    string a = values_stack.back(); values_stack.pop_back();
                    values_stack.push_back(apply_op(op, a, b));
                }
            }
            ops_stack.push_back(t);
        }
    }

    while (!ops_stack.empty()) {
        string op = ops_stack.back();
        ops_stack.pop_back();
        if (op == "!") {
            string val = values_stack.back(); values_stack.pop_back();
            values_stack.push_back(apply_op(op, val));
        } else {
            string b = values_stack.back(); values_stack.pop_back();
            string a = values_stack.back(); values_stack.pop_back();
            values_stack.push_back(apply_op(op, a, b));
        }
    }

    cout << bits_to_num(values_stack.back());
    return 0;
}
