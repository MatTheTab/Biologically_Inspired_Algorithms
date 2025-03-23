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
// ./bio_alg heuristic data/qap/ bur26a results.txt
// ./bio_alg random data/qap/ bur26a results.txt
// ./bio_alg antiheuristic data/qap/ bur26a results.txt
// ./bio_alg heuristic data/qap/ bur26a results.txt greedy_LS
// ./bio_alg heuristic data/qap/ bur26a results.txt steepest_LS
// ./bio_alg random data/qap/ bur26a results.txt greedy_LS
// ./bio_alg antiheuristic data/qap/ bur26a results.txt greedy_LS

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <initial_algorithm> <problem_folder> <problem_name> <results_file> [<local_search_algorithm>]" << endl;
        return 1;
    }
    
    string initial_algorithm = argv[1];
    string instance_dir = argv[2];
    string instance_name = argv[3];
    string results_filename = argv[4];
    string local_search_algorithm = (argc > 5) ? argv[5] : "";
    
    Problem problem(instance_dir, instance_name);
    int size = problem.size;
    int** matrixA = problem.matrixA;
    int** matrixB = problem.matrixB;
    int* opt_solution = problem.opt_solution;
    int opt_score = problem.opt_score;
    
    cout << "Instance: " << instance_name << endl;
    cout << "Size: " << size << endl;
    cout << "Optimal score: " << opt_score << endl;
    cout << "Optimal solution: ";
    for (int i = 0; i < size; i++) {
        cout << opt_solution[i] << " ";
    }
    cout << endl;


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
    saveResultsToFile(results_filename, initial_algorithm, instance_name, runtime_initial, scoreInitial, size, P, 1, 1);
    
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
        
        saveResultsToFile(results_filename, local_search_algorithm, instance_name, runtime_LS, *scoreLS, size, P, *numEvaluations, *numMoves);
    }
    
    delete[] P;
    return 0;
}
