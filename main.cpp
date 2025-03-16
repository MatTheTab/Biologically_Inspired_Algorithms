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
// ./bio_alg greedy_LS data/qap/bur26a.dat results.txt
// ./bio_alg steepest_LS data/qap/bur26a.dat results.txt

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <algorithm> <problem_file> <results_file>" << endl;
        return 1;
    }
    
    string algorithm = argv[1];
    string filename = argv[2];
    string results_filename = argv[3];
    string instanceName = filename;
    
    Problem problem(filename);
    int size = problem.size;
    int** matrixA = problem.matrixA;
    int** matrixB = problem.matrixB;
    
    int *P = new int[size];
    double runtime_heuristic = measureFunctionRuntime(heuristicSolve, size, matrixA, matrixB, P);
    int scoreHeuristic = calculateScore(size, P, matrixA, matrixB);
    
    if (algorithm == "heuristic") {
        saveResultsToFile(results_filename, "Heuristic", instanceName, runtime_heuristic, scoreHeuristic, size, P, 1, 1);
    } else if (algorithm == "greedy_LS" || algorithm == "steepest_LS") {
        string intermediate_name = (algorithm == "greedy_LS") ? "Heuristic_Greedy" : "Heuristic_Steepest";
        saveResultsToFile(results_filename, intermediate_name, instanceName, runtime_heuristic, scoreHeuristic, size, P, 1, 1);
        
        int tempMoves = 0;
        int tempNumEvaluations = 0;
        int* scoreLS = &scoreHeuristic;
        int* numMoves = &tempMoves;
        int* numEvaluations = &tempNumEvaluations;
        
        double runtime_LS;
        if (algorithm == "greedy_LS"){runtime_LS = measureFunctionRuntime(greedyLocalSearchSolve, size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);}
        else {runtime_LS = measureFunctionRuntime(steepestLocalSearchSolve, size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);}
        
        saveResultsToFile(results_filename, algorithm, instanceName, runtime_LS, *scoreLS, size, P, *numEvaluations, *numMoves);
    } else {
        cerr << "Unknown algorithm: " << algorithm << endl;
        return 1;
    }
    
    delete[] P;
    return 0;
}
