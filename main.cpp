#include <iostream>
#include <string>
#include "random.h"
#include "time_measure.h"
#include "Problem.h"
#include "solution.h"
#include "utils.h"
#include <random>  // Include this for better randomness

using namespace std;

// For documentation: doxygen Doxyfile
// Test with: g++ -o bio_alg main.cpp random.cpp Problem.cpp solution.cpp utils.cpp -std=c++17
// ./bio_alg performance heuristic 100 0 data/qap/ bur26a performance_results.txt
// ./bio_alg time heuristic 0 0 data/qap/ bur26a runtime_results.txt
// ./bio_alg performance random 100 0 data/qap/ bur26a performance_results.txt
// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt
// ./bio_alg performance antiheuristic 100 0 data/qap/ bur26a performance_results.txt
// ./bio_alg time antiheuristic 0 0 data/qap/ bur26a runtime_results.txt

// ./bio_alg performance randomwalk 100 156340 data/qap/ bur26a performance_results.txt
// ./bio_alg performance randomsearch 100 156340 data/qap/ bur26a performance_results.txt

// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt greedyLS
// ./bio_alg performance random 100 0 data/qap/ bur26a performance_results.txt greedyLS
// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt steepestLS
// ./bio_alg performance random 100 0 data/qap/ bur26a performance_results.txt steepestLS


void runTimePerformanceTest(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm);
void runQualityPerformanceTests(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm, int num_runs, int randomDuration); 
void setRandomSeed();

int main(int argc, char* argv[]) {
    if (argc < 6) {
        cerr << "Usage: " << argv[0] << " <test_type> <algorithm> <num_runs> <random_duration> <problem_folder> <problem_name> <results_file> [<local_search_algorithm>]" << endl;
        return 1;
    }
    
    string test_type = argv[1];
    string algorithm = argv[2];
    int num_runs = stoi(argv[3]);
    int randomDuration = stoi(argv[4]);
    string instance_dir = argv[5];
    string instance_name = argv[6];
    string results_filename = argv[7];
    string local_search_algorithm = (argc > 8) ? argv[8] : "";

    Problem problem(instance_dir, instance_name);

    if (test_type == "time") {
        runTimePerformanceTest(algorithm, problem, results_filename, local_search_algorithm);
    } else if (test_type == "performance") {
        runQualityPerformanceTests(algorithm, problem, results_filename, local_search_algorithm, num_runs, randomDuration);
    } else {
        cerr << "Unknown test type: " << test_type << endl;
        return 1;
    }
    
    return 0;
}

void runQualityPerformanceTests(const string& algorithm, Problem& problem, const string& results_filename, 
    const string& local_search_algorithm, int num_runs, int randomDuration) {
    int size = problem.size;
    int** matrixA = problem.matrixA;
    int** matrixB = problem.matrixB;
    int* P = new int[size];
    int initialScore = 0;

    int numMoves = 0;
    int numEvaluations = 0;
    int bestScore = 0;
    int numBestSolutionUpdates = 0;

    int* pointNumMoves = &numMoves;
    int* pointNumEvaluations = &numEvaluations;
    int* pointBestFoundScore = &bestScore;
    int* pointNumBestSolutionUpdates = &numBestSolutionUpdates;

    while (num_runs>0){
        num_runs--;

        *pointBestFoundScore = 0;
        *pointNumMoves = 0;
        *pointNumEvaluations = 0;
        
        setRandomSeed(); // Prevents the same random perturbations

        if (!local_search_algorithm.empty()) {
            if (algorithm == "heuristic") {
                setRandomSeed();
                heuristicSolveNonDeterministic(size, matrixA, matrixB, P);
            } else if (algorithm == "random") {
                generateRandomPerturbation(size, P);
            } else if (algorithm == "antiheuristic") {
                antiHeuristicSolve(size, matrixA, matrixB, P);
            } else {
                cerr << "Unknown initial algorithm: " << algorithm << endl;
                delete[] P;
                return;
            }
            initialScore = calculateScore(size, P, matrixA, matrixB);
            *pointBestFoundScore = initialScore;
    
            if (local_search_algorithm == "greedyLS") {
                greedyLocalSearchSolve(size, P, matrixA, matrixB, pointBestFoundScore, pointNumEvaluations, pointNumMoves);
            } else if (local_search_algorithm == "steepestLS") {
                steepestLocalSearchSolve(size, P, matrixA, matrixB, pointBestFoundScore, pointNumEvaluations, pointNumMoves);
            } else {
                cerr << "Unknown local search algorithm: " << local_search_algorithm << endl;
                delete[] P;
                return;
            }
            
            string combinedAlgorithm = algorithm.substr(0, 1) + local_search_algorithm;

            savePerformanceResultsToFile(results_filename, combinedAlgorithm, problem.instance, initialScore, bestScore, size, P, 
                numEvaluations, numMoves, numMoves, problem.optScore, problem.optSolution);
    
        } else {
            P = new int[size];
            *pointBestFoundScore = 0;
            *pointNumEvaluations = 0;
            *pointNumBestSolutionUpdates = 0;

            if (algorithm == "heuristic") {
                setRandomSeed();
                heuristicSolveNonDeterministic(size, matrixA, matrixB, P);
                bestScore = calculateScore(size, P, matrixA, matrixB);
                savePerformanceResultsToFile(results_filename, algorithm, problem.instance, 0, bestScore, size, P,
                    1, 1, 1, problem.optScore, problem.optSolution);

            } else if (algorithm == "randomwalk") {
                randomWalk(size, P, matrixA, matrixB, pointBestFoundScore, randomDuration, pointNumEvaluations, pointNumBestSolutionUpdates);
                
                savePerformanceResultsToFile(results_filename, algorithm, problem.instance, 0, bestScore, size, P,
                    numEvaluations, numEvaluations, numBestSolutionUpdates, problem.optScore, problem.optSolution);

            } else if (algorithm == "randomsearch") {
                randomSearch(size, P, matrixA, matrixB, pointBestFoundScore, randomDuration, pointNumEvaluations, pointNumBestSolutionUpdates);

                savePerformanceResultsToFile(results_filename, algorithm, problem.instance, 0, bestScore, size, P,
                    numEvaluations, numEvaluations, numBestSolutionUpdates, problem.optScore, problem.optSolution);

            } else if (algorithm == "antiheuristic") {
                antiHeuristicSolve(size, matrixA, matrixB, P);
                bestScore = calculateScore(size, P, matrixA, matrixB);
            
                savePerformanceResultsToFile(results_filename, algorithm, problem.instance, 0, bestScore, size, P,
                    1, 1, 1, problem.optScore, problem.optSolution);
            } else {
                cerr << "Unknown initial algorithm: " << algorithm << endl;
                delete[] P;
                return;
            }
        }
    }

    delete[] P;
}

void runTimePerformanceTest(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm) {
    int size = problem.size;
    int** matrixA = problem.matrixA;
    int** matrixB = problem.matrixB;
    int* P = new int[size];
    int score_initial;

    if (!local_search_algorithm.empty()) {
        if (algorithm != "random") {
            cerr << "Only 'random' can be used as start algorithm in time tests: " << algorithm << endl;
            delete[] P;
            return;
        }

        int tempMoves = 0;
        int tempNumEvaluations = 0;
        int* scoreLS = &score_initial;
        int* numMoves = &tempMoves;
        int* numEvaluations = &tempNumEvaluations;

        double runtime_LS;
        if (local_search_algorithm == "greedyLS") {
            auto start = high_resolution_clock::now();
            auto end = start;
            int num_runs = 0;
                do {
                    *numEvaluations = 0;
                    *numMoves = 0;
                    setRandomSeed(); // Prevents the same random perturbations TODO verify if adding this is fair
                    
                    generateRandomPerturbation(size, P);
                    *scoreLS = calculateScore(size, P, matrixA, matrixB);
                    
                    greedyLocalSearchSolve(size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);

                    end = high_resolution_clock::now();
                    num_runs ++;
                } while (duration_cast<seconds>(end - start).count() < 100 && num_runs < 100);

            runtime_LS = duration_cast<nanoseconds>(end - start).count()/num_runs;
        
        } else if (local_search_algorithm == "steepestLS") {
            auto start = high_resolution_clock::now();
            auto end = start;
            int num_runs = 0;
                do {
                    *numEvaluations = 0;
                    *numMoves = 0;
                    setRandomSeed(); // Prevents the same random perturbations TODO verify if adding this is fair
                    
                    generateRandomPerturbation(size, P);
                    *scoreLS = calculateScore(size, P, matrixA, matrixB);
                    
                    steepestLocalSearchSolve(size, P, matrixA, matrixB, scoreLS, numEvaluations, numMoves);

                    end = high_resolution_clock::now();
                    num_runs ++;
                } while (duration_cast<seconds>(end - start).count() < 100 && num_runs < 100);

            runtime_LS = duration_cast<nanoseconds>(end - start).count()/num_runs;
        
        } else {
            cerr << "Unknown local search algorithm: " << local_search_algorithm << endl;
            delete[] P;
            return;
        }
        
        saveRuntimeResultsToFile(results_filename, local_search_algorithm, problem.instance, runtime_LS);

    } else { // These functions can be measured with measure function runtime without the need for resetting values
        double runtime;
        if (algorithm == "heuristic") {
            setRandomSeed();
            runtime = measureFunctionRuntime(heuristicSolveNonDeterministic, size, matrixA, matrixB, P);
            saveRuntimeResultsToFile(results_filename, algorithm, problem.instance, runtime);
            
        } else if (algorithm == "antiheuristic") {
            runtime = measureFunctionRuntime(antiHeuristicSolve, size, matrixA, matrixB, P);
            saveRuntimeResultsToFile(results_filename, algorithm, problem.instance, runtime);
            
        } else if (algorithm == "random") {
            runtime = measureFunctionRuntime(generateRandomPerturbation, size, P);
            saveRuntimeResultsToFile(results_filename, algorithm, problem.instance, runtime);

        } else {
            cerr << "Unknown initial algorithm: " << algorithm << endl;
            delete[] P;
            return;
        }   
    }

    delete[] P;
}

void setRandomSeed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    srand(gen());
}