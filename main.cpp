#include <iostream>
#include "random.h"
#include "time_measure.h"

using namespace std;

/**
 * @brief Test function, iterates over a double loop and assigns a value to a variable squared n times.
 * 
 * @param n Number of iterations of the double nested loop.
 */
void test_func1(int n){
    int val = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            val = i+j;
        }
    }
}

/**
 * @brief Test function, iterates over a double loop and assigns a value to a variable n x m times.
 * 
 * @param n Number of iterations of the outside loop.
 * @param m Number of iterations of the inner loop.
 */
void test_func2(int n, int m){
    int val = 0;
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
            val = i+j;
        }
    }
}

// Test with: g++ -o bio_alg main.cpp random.cpp -std=c++17
// ./bio_alg

int main() {
    srand(time(0));
    int n = 10;
    int* arr = generateRandomPerturbation(n);
    cout << "Generated array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    cout << "\n";
    delete[] arr;
    
    pair<int, int> randomValues = getRandomPair(n);
    int first = randomValues.first;
    int second = randomValues.second;
    cout << "Random values: " << first << " and " << second << "\n";

    cout << "Time Measuring \n";
    double speed_test_1;
    double speed_test_2;
    speed_test_1 = measureFunctionRuntime(test_func1, 1000);
    speed_test_2 = measureFunctionRuntime(test_func2, 3000, 5000);

    cout << "Speed test 1" << speed_test_1 << " nanoseconds" << "\n";
    cout << "Speed test 2" << speed_test_2 << " nanoseconds" << "\n";
    return 0;
}