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
// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt 
// ./bio_alg performance random 100 0 data/qap/ bur26a performance_results.txt greedyLS
// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt steepestLS
// ./bio_alg performance random 100 0 data/qap/ bur26a performance_results.txt steepestLS
// ./bio_alg time random 0 0 data/qap/ bur26a runtime_results.txt iterativeImprovement

void runTimePerformanceTest(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm);
void runQualityPerformanceTests(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm, int num_runs, int randomDuration); 
void setRandomSeed();
void executeLocalSearch(const string& local_search_algorithm, int size, int* P, int** matrixA, int** matrixB, 
    int* bestScore, int* numEvaluations, int* numMoves);

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

    int size = problem.getSize();
    int** matrixA = problem.getMatrixA();
    int** matrixB = problem.getMatrixB();
    std::string instance = problem.getInstance();
    int optScore = problem.getOptScore();
    int* optSolution = problem.getOptSolution();

    int* P = new int[size];
    int initialScore = 0;

    int numMoves = 0, numEvaluations = 0, bestScore = 0, numBestSolutionUpdates = 0;

    while (num_runs--) {
        bestScore = numMoves = numEvaluations = numBestSolutionUpdates = 0;
        setRandomSeed();

        if (algorithm == "heuristic") {
            heuristicSolveNonDeterministic(size, matrixA, matrixB, P);
        } else if (algorithm == "random") {
            generateRandomPerturbation(size, P);
        } else if (algorithm == "antiheuristic") {
            antiHeuristicSolve(size, matrixA, matrixB, P);
        } 
        // else {
        //     cerr << "Unknown initial algorithm: " << algorithm << endl;
        //     return;
        // }

        initialScore = calculateScore(size, P, matrixA, matrixB);
        bestScore = initialScore;

        if (!local_search_algorithm.empty()) {
            executeLocalSearch(local_search_algorithm, size, P, matrixA, matrixB, &bestScore, &numEvaluations, &numMoves);
            string combinedAlgorithm = algorithm.substr(0, 1) + local_search_algorithm;
            savePerformanceResultsToFile(results_filename, combinedAlgorithm, instance, initialScore, bestScore, size, P,
                numEvaluations, numMoves, numBestSolutionUpdates, optScore, optSolution);
        } else if (algorithm == "randomwalk"){
            randomWalk(size, P, matrixA, matrixB, &bestScore, randomDuration, &numEvaluations, &numBestSolutionUpdates);
            savePerformanceResultsToFile(results_filename, algorithm, instance, 0, bestScore, size, P,
                numEvaluations, numEvaluations, numBestSolutionUpdates, optScore, optSolution);
        } else if (algorithm == "randomsearch"){
            randomSearch(size, P, matrixA, matrixB, &bestScore, randomDuration, &numEvaluations, &numBestSolutionUpdates);
            savePerformanceResultsToFile(results_filename, algorithm, instance, 0, bestScore, size, P,
                numEvaluations, numEvaluations, numBestSolutionUpdates, optScore, optSolution);
        } else {
            savePerformanceResultsToFile(results_filename, algorithm, instance, 0, bestScore, size, P,
                1, 1, 1, optScore, optSolution);
        }
    }
    delete[] P;
}

void runTimePerformanceTest(const string& algorithm, Problem& problem, const string& results_filename, const string& local_search_algorithm) {
    // cout<<results_filename;
    int size = problem.getSize();
    int** matrixA = problem.getMatrixA();
    int** matrixB = problem.getMatrixB();
    std::string instance = problem.getInstance();
    int optScore = problem.getOptScore();
    int* optSolution = problem.getOptSolution();
    
    int* P = new int[size];
    int score_initial;

    if (!local_search_algorithm.empty()) {
        if (algorithm != "random") {
            cerr << "Only 'random' can be used as start algorithm in time tests: " << algorithm << endl;
            return;
        }

        int numRuns = 0, numEvaluations = 0, numMoves = 0;
        int score = 0;
        double totalTime = 0;

        auto measureTime = [&](auto searchFunc) {
            auto start = high_resolution_clock::now();
            do {
                setRandomSeed();
                generateRandomPerturbation(size, P);
                score = calculateScore(size, P, matrixA, matrixB);
                searchFunc(size, P, matrixA, matrixB, &score, &numEvaluations, &numMoves);
                numRuns++;
            } while (duration_cast<seconds>(high_resolution_clock::now() - start).count() < 100 && numRuns < 100);
            return duration_cast<nanoseconds>(high_resolution_clock::now() - start).count() / numRuns;
        };

        if (local_search_algorithm == "greedyLS") {
            totalTime = measureTime(greedyLocalSearchSolve);
        } else if (local_search_algorithm == "steepestLS") {
            totalTime = measureTime(steepestLocalSearchSolve);
        } else if (local_search_algorithm == "iterativeImprovement"){
            totalTime = measureTime(iterativeImprovementFast);
        }else {
            cerr << "Unknown local search algorithm: " << local_search_algorithm << endl;
            return;
        }

        saveRuntimeResultsToFile(results_filename, local_search_algorithm, instance, totalTime);
    } else {
        double runtime;
        if (algorithm == "heuristic") {
            setRandomSeed();
            runtime = measureFunctionRuntime(heuristicSolveNonDeterministic, size, matrixA, matrixB, P);
        } else if (algorithm == "antiheuristic") {
            runtime = measureFunctionRuntime(antiHeuristicSolve, size, matrixA, matrixB, P);
        } else if (algorithm == "random") {
            runtime = measureFunctionRuntime(generateRandomPerturbation, size, P);
        } else {
            cerr << "Unknown initial algorithm: " << algorithm << endl;
            return;
        }
        saveRuntimeResultsToFile(results_filename, algorithm, instance, runtime);
    }
    delete[] P;
}

void setRandomSeed() {
    std::random_device rd;
    std::mt19937 gen(rd());
    srand(gen());
}

void executeLocalSearch(const string& local_search_algorithm, int size, int* P, int** matrixA, int** matrixB,
    int* bestScore, int* numEvaluations, int* numMoves) {
    if (local_search_algorithm == "greedyLS") {
        greedyLocalSearchSolve(size, P, matrixA, matrixB, bestScore, numEvaluations, numMoves);
    } else if (local_search_algorithm == "steepestLS") {
        steepestLocalSearchSolve(size, P, matrixA, matrixB, bestScore, numEvaluations, numMoves);
    } else if (local_search_algorithm == "iterativeImprovement"){
        iterativeImprovementFast(size, P, matrixA, matrixB, bestScore, numEvaluations, numMoves);
    } else {
        cerr << "Unknown local search algorithm: " << local_search_algorithm << endl;
        exit(1);
    }
}