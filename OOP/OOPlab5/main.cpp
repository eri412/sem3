#include <algorithm>
#include <iostream>
#include <string>

#include "pentagon.hpp"
#include "stack.hpp"

int main() {
    Stack<Pentagon<int>> stack;
    std::string input;
    while (std::cin >> input) {
        if (input == "add") {
            int x, y, a;
            std::cin >> x >> y >> a;
            std::pair<int, int> fuck;
            fuck.first = x;
            fuck.second = y;
            Pentagon<int> temp(fuck, a);
            stack.push(temp);
        }
        else if (input == "delete") {
            int pos;
            std::cin >> pos;
            auto iter = stack.begin();
            for (int i = 0; i < pos; ++i) {
                ++iter;
            }
            stack.erase(iter);
        }
        else if (input == "print") {
            for (auto item : stack) {
                std::cout << item.data;
            }
        }
        else if (input == "lessthan") {
            int a;
            std::cin >> a;
            int res = std::count_if(stack.begin(), stack.end(), [&](Stack<Pentagon<int>>::Node node) {return node.data.area < a;});
            std::cout << res << "\n";
        }
    }

    return 0;
}