#include <iostream>
#include <chrono>

int main() {
    constexpr long long duration_ns = 1000000; // Set duration in nanoseconds (e.g., 1 millisecond)

    auto start = std::chrono::high_resolution_clock::now();
    
    int count = 0;
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::nanoseconds(duration_ns)) {
        count++;
    }   

    std::cout << "Time elapsed: " << duration_ns << " nanoseconds.\n";
    return 0;
}
