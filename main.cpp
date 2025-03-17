#include <iostream>
#include <string>
#include "random.h"
#include "time_measure.h"
#include "Problem.h"
#include "solution.h"
#include "utils.h"

using namespace std;

// For documentation: doxygen Doxyfile
// Test with: g++ -o bio_alg main.cpp random.cpp Problem.cpp solution.cpp utils.cpp -std=c++17
// ./bio_alg heuristic data/qap/bur26a.dat results.txt
// ./bio_alg random data/qap/bur26a.dat results.txt
// ./bio_alg antiheuristic data/qap/bur26a.dat results.txt
// ./bio_alg heuristic data/qap/bur26a.dat results.txt greedy_LS
// ./bio_alg heuristic data/qap/bur26a.dat results.txt steepest_LS
// ./bio_alg random data/qap/bur26a.dat results.txt greedy_LS
// ./bio_alg antiheuristic data/qap/bur26a.dat results.txt greedy_LS

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <initial_algorithm> <problem_file> <results_file> [<local_search_algorithm>]" << endl;
        return 1;
    }
    
    string initial_algorithm = argv[1];
    string filename = argv[2];
    string results_filename = argv[3];
    string local_search_algorithm = (argc > 4) ? argv[4] : "";
    
    Problem problem(filename);
    int size = problem.size;
    int** matrixA = problem.matrixA;
    int** matrixB = problem.matrixB;
    
    int *P = new int[size];
    double runtime_initial;
    int scoreInitial;
    
    if (initial_algorithm == "heuristic") {
        runtime_initial = measureFunctionRuntime(heuristicSolve, size, matrixA, matrixB, P);
    } else if (initial_algorithm == "random") {
        runtime_initial = measureFunctionRuntime(generateRandomPerturbation, size, P);
    } else if (initial_algorithm == "antiheuristic") {
        runtime_initial = measureFunctionRuntime(antiHeuristicSolve, size, matrixA, matrixB, P);
    } else {
        cerr << "Unknown initial algorithm: " << initial_algorithm << endl;
        delete[] P;
        return 1;
    }
    
    scoreInitial = calculateScore(size, P, matrixA, matrixB);
    saveResultsToFile(results_filename, initial_algorithm, filename, runtime_initial, scoreInitial, size, P, 1, 1);
    
    if (!local_search_algorithm.empty()) {
        int tempMoves = 0;
        int tempNumEvaluations = 0;
        int* scoreLS = &scoreInitial;
        int* numMoves = &tempMoves;
        int* numEvaluations = &tempNumEvaluations;
        
        double runtime_LS;
        if (local_search_algorithm == "greedy_LS") {
            runtime_LS = measureFunctionRuntime(greedyLocalSearchSolve, size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);
        } else if (local_search_algorithm == "steepest_LS") {
            runtime_LS = measureFunctionRuntime(steepestLocalSearchSolve, size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);
        } else {
            cerr << "Unknown local search algorithm: " << local_search_algorithm << endl;
            delete[] P;
            return 1;
        }
        
        saveResultsToFile(results_filename, local_search_algorithm, filename, runtime_LS, *scoreLS, size, P, *numEvaluations, *numMoves);
    }
    
    delete[] P;
    return 0;
}
