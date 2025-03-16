#include <iostream>
#include "random.h"
#include "time_measure.h"
#include "Problem.h"
#include "solution.h"
#include "utils.h"

using namespace std;

//TODO: startuj z konsoli

// For documentation: doxygen Doxyfile
// Test with: g++ -o bio_alg main.cpp random.cpp Problem.cpp solution.cpp utils.cpp -std=c++17
// ./bio_alg

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
    int* P2 = new int[size] {0, 1, 2};

    int score_1 = calculateScore(size, P1, A, B);
    int score_2 = calculateScore(size, P2, A, B);
    cout << "score 1: " << score_1 << "\n";
    cout << "score 2: " << score_2 << "\n";

    int numEvaluations1 = 0;
    int numMoves1 = 0;
    int numEvaluations2 = 0;
    int numMoves2 = 0;

    
    greedyLocalSearchSolve(size, P1, A, B, score_1, numEvaluations1, numMoves1);
    steepestLocalSearchSolve(size, P2, A, B, score_2, numEvaluations2, numMoves2);
    cout << "Permutation (Greedy): " << P1[0] << " " << P1[1] << " " << P1[2] << "\n";
    cout << "Permutation (Steepest): " << P2[0] << " " << P2[1] << " " << P2[2] << "\n";
    cout << "Final Score 1: " << score_1 << " number of evaluations: " << numEvaluations1 << " number of moves: " << numMoves1 << "\n";
    cout << "Final Score 2: " << score_2 << " number of evaluations: " << numEvaluations2 << " number of moves: " << numMoves2 << "\n";

    string filename = "results.txt";
    string algorithmName1 = "Greedy_Algorithm";
    string algorithmName2 = "Steepest_Algorithm";
    string instance = "Test_Instance_1";

    double runtime1 = measureFunctionRuntime(greedyLocalSearchSolve, size, P1, A, B, score_1, numEvaluations1, numMoves1);
    double runtime2 = measureFunctionRuntime(steepestLocalSearchSolve, size, P2, A, B, score_2, numEvaluations2, numMoves2);

    saveResultsToFile(filename, algorithmName1, instance, runtime1, score_1, size, P1, numEvaluations1, numMoves1);
    saveResultsToFile(filename, algorithmName2, instance, runtime2, score_1, size, P1, numEvaluations1, numMoves1);
 
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