#include <iostream>
#include <map>
#include <chrono>
#include <cmath>

int main () {
    std::map <int, int> mp;
    int n{};
    for (int i{}; i < 5; i++) {
        mp.clear();
        n = std::ceil(std::pow(10, i)); // округление вверх, floor -> вниз
        auto t1 = std::chrono::high_resolution_clock::now();
        for (int j{}; j < n; j++) {
            mp[j] = j;
        }
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = t2 - t1;
        std::cout << elapsed.count() << " " << 2 * sizeof(int) * n << " ";
    }
    std::cout << std::endl;
    return 0;
}