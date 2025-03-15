#include <iostream>
#include "random.h"
#include "time_measure.h"
#include "Problem.h"
#include "solution.h"

using namespace std;

void test_func1(int n);
void test_func2(int n, int m);

// Test with: g++ -o bio_alg main.cpp random.cpp Problem.cpp solution.cpp -std=c++17
// ./bio_alg

int** createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    return matrix;
}

// Function to delete a dynamically allocated 2D array
void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    //string filename = "data/qap/bur26a.dat";
    //Problem problem(filename);
    //problem.displayInstance();

    int size = 3;

    int** A = createMatrix(size);
    int flowData[3][3] = {
        {0, 5, 2},
        {5, 0, 3},
        {2, 3, 0}
    };
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            A[i][j] = flowData[i][j];

    int** B = createMatrix(size);
    int distData[3][3] = {
        {0, 2, 3},
        {2, 0, 1},
        {3, 1, 0}
    };
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            B[i][j] = distData[i][j];

    int* P1 = new int[size] {0, 1, 2};
    int* P2 = heuristicSolve(size, A, B);

    int score_1 = calculateScore(size, P1, A, B);
    int score_2 = calculateScore(size, P2, A, B);
    cout << "score 1: " << score_1 << "\n";
    cout << "score 2: " << score_2 << "\n";

    
    greedyLocalSearchSolve(size, P1, A, B);
    cout << "Permutation: " << P1[0] << " " << P1[1] << " " << P1[2] << "\n";
    int score_3 = calculateScore(size, P1, A, B);
    cout << "Final Score: " << score_3 << "\n";
 
    // srand(time(0));
    // int n = 10;
    // int* arr = generateRandomPerturbation(n);
    // cout << "Generated array: ";
    // for (int i = 0; i < n; i++) {
    //     std::cout << arr[i] << " ";
    // }
    // cout << "\n";
    // delete[] arr;
    
    // pair<int, int> randomValues = getRandomPair(n);
    // int first = randomValues.first;
    // int second = randomValues.second;
    // cout << "Random values: " << first << " and " << second << "\n";

    // cout << "Time Measuring \n";
    // double speed_test_1;
    // double speed_test_2;
    // speed_test_1 = measureFunctionRuntime(test_func1, 1000);
    // speed_test_2 = measureFunctionRuntime(test_func2, 3000, 5000);

    // cout << "Speed test 1" << speed_test_1 << " nanoseconds" << "\n";
    // cout << "Speed test 2" << speed_test_2 << " nanoseconds" << "\n";
    return 0;
}

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
