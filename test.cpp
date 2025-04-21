// Build with: g++ -o test test.cpp random.cpp Problem.cpp solution.cpp utils.cpp -std=c++17
// Run with: ./test data/qap/ bur26a

#include <iostream>
#include <string>
#include <cstring>
#include "random.h"
#include "Problem.h"
#include "solution.h"
#include "utils.h"
#include <random>

using namespace std;

void setRandomSeed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    srand(gen());
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <problem_folder> <problem_name>" << endl;
        return 1;
    }

    string instance_dir = argv[1];
    string instance_name = argv[2];

    // Load problem instance
    Problem problem(instance_dir, instance_name);
    int size = problem.getSize();
    int** matrixA = problem.getMatrixA();
    int** matrixB = problem.getMatrixB();

    // Allocate and initialize random solution
    int* initialP = new int[size];
    setRandomSeed();
    generateRandomPerturbation(size, initialP);
    int initialScore = calculateScore(size, initialP, matrixA, matrixB);

    cout << "\n=== Initial Solution ===" << endl;
    cout << "Initial Score: " << initialScore << endl;

    // --- Steepest Local Search ---
    int* steepestP = new int[size];
    memcpy(steepestP, initialP, sizeof(int) * size);
    int steepestScore = initialScore;
    int steepestEvaluations = 0;
    int steepestMoves = 0;

    steepestLocalSearchSolve(size, steepestP, matrixA, matrixB, &steepestScore, &steepestEvaluations, &steepestMoves);

    cout << "\n=== Steepest Local Search ===" << endl;
    cout << "Final Score: " << steepestScore << endl;
    cout << "Evaluations: " << steepestEvaluations << endl;
    cout << "Moves: " << steepestMoves << endl;

    // --- Taboo Search ---
    int* tabooP = new int[size];
    memcpy(tabooP, initialP, sizeof(int) * size);
    int tabooScore = initialScore;
    int tabooEvaluations = 0;
    int tabooMoves = 0;
    int tabooTenure = 4;
    int numMovesTermination = 20;

    tabooSearch(size, tabooP, matrixA, matrixB, &tabooScore, &tabooEvaluations, &tabooMoves, tabooTenure, numMovesTermination);

    cout << "\n=== Taboo Search ===" << endl;
    cout << "Final Score: " << tabooScore << endl;
    cout << "Evaluations: " << tabooEvaluations << endl;
    cout << "Moves: " << tabooMoves << endl;

    // --- Simulated Annealing ---
    int* saP = new int[size];
    memcpy(saP, initialP, sizeof(int) * size);
    int saScore = initialScore;
    int saEvaluations = 0;
    int saMoves = 0;
    double tempDecrease = 0.9;
    int markovChainDivisor = 5;

    simulatedAnnealing(size, saP, matrixA, matrixB, &saScore, &saEvaluations, &saMoves, tempDecrease, markovChainDivisor);

    cout << "\n=== Simulated Annealing ===" << endl;
    cout << "Final Score: " << saScore << endl;
    cout << "Evaluations: " << saEvaluations << endl;
    cout << "Moves: " << saMoves << endl;

    // Cleanup
    delete[] initialP;
    delete[] steepestP;
    delete[] tabooP;
    delete[] saP;

    return 0;
}
