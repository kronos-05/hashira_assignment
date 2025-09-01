#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include "nlohmann/json.hpp"  // downloaded nlohmann/json single header

using json = nlohmann::json;

// Convert digit char to int
int charToDigit(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    if ('a' <= c && c <= 'f') return 10 + (c - 'a');
    if ('A' <= c && c <= 'F') return 10 + (c - 'A');
    return -1; // invalid
}

// Convert string number of given base to decimal
long long baseToDecimal(const std::string& val, int base) {
    long long res = 0;
    for (char c : val) {
        int d = charToDigit(c);
        if (d < 0 || d >= base) {
            std::cerr << "Invalid digit in number\n";
            exit(1);
        }
        res = res * base + d;
    }
    return res;
}

int main() {
    std::ifstream fin("input2.json");
    if (!fin) {
        std::cerr << "File input.json not found\n";
        return 1;
    }

    json j;
    fin >> j;

    // Extract n and k (inside "keys")
    int n = j["keys"]["n"];
    int k = j["keys"]["k"];

    // Store bases and values
    std::map<int, int> bases;
    std::map<int, std::string> values;

    // Iterate through JSON keys (skip "keys" object)
    for (auto it = j.begin(); it != j.end(); ++it) {
        std::string key = it.key();
        if (key == "keys") continue; // skip metadata
        if (std::all_of(key.begin(), key.end(), ::isdigit)) {
            int idx = std::stoi(key);
            bases[idx] = std::stoi(it.value()["base"].get<std::string>());
            values[idx] = it.value()["value"].get<std::string>();
        }
    }

    if ((int)bases.size() < k || (int)values.size() < k) {
        std::cerr << "Not enough roots to solve polynomial\n";
        return 1;
    }

    // Collect keys with both base and value
    std::vector<int> keys;
    for (auto const& kv : bases) {
        if (values.find(kv.first) != values.end())
            keys.push_back(kv.first);
    }

    std::sort(keys.begin(), keys.end());
    if ((int)keys.size() < k) {
        std::cerr << "Not enough roots with base and value\n";
        return 1;
    }

    // Prepare points for interpolation
    std::vector<long long> xs(k), ys(k);
    for (int i = 0; i < k; ++i) {
        xs[i] = i + 1; // x = 1, 2, 3...
        ys[i] = baseToDecimal(values[keys[i]], bases[keys[i]]);
    }

    // Compute polynomial value at x=0 (constant term) via Lagrange interpolation
    long double constantTerm = 0.0;
    for (int i = 0; i < k; ++i) {
        long double term = ys[i];
        for (int j = 0; j < k; ++j) {
            if (i != j)
                term *= (0.0 - xs[j]) / (xs[i] - xs[j]);
        }
        constantTerm += term;
    }

    long long final_answer = std::llround(constantTerm);

    std::cout << "Constant term (f(0)) = " << final_answer << "\n";
    return 0;
}
