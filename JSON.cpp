#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <cmath>
#include <nlohmann/json.hpp>// External JSON library
using json = nlohmann::json;
using namespace std;
long long baseToDecimal(string value, int base) {
    long long result = 0;
    for (char digit : value) {
        result *= base;
        if (isdigit(digit)) {
            result += digit - '0';
        } else {
            result += digit - 'a' + 10; 
        }
    }
    return result;
}
long long lagrangeInterpolation(vector<pair<int, long long>> points) {
    long long c = 0;
    int k = points.size();
    for (int i = 0; i < k; i++) {
        long long xi = points[i].first;
        long long yi = points[i].second;

        long long term = yi;
        for (int j = 0; j < k; j++) {
            if (i != j) {
                long long xj = points[j].first;
                term *= (-xj);
                term /= (xi - xj);
            }
        }
        c += term;
    }
    return c;
}
int main() {
    ifstream file("test.json");
    json input;
    file >> input;
    int n = input["keys"]["n"];
    int k = input["keys"]["k"];
    vector<pair<int, long long>> points;
    for (auto it = input.begin(); it != input.end(); ++it) {
        if (it.key() == "keys") continue; 
        int x = stoi(it.key());
        int base = stoi(it.value()["base"].get<string>());
        string value = it.value()["value"].get<string>();
        long long y = baseToDecimal(value, base);
        points.push_back({x, y});
    }
    sort(points.begin(), points.end());
    points.resize(k);
    long long secret = lagrangeInterpolation(points);
    cout << "Secret (Constant term C): " << secret << endl;
    return 0;
}
