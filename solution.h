#ifndef SOLUTION_H
#define SOLUTION_H

#include <utility>

/**
 * @brief Calculates score for the QAP problem.
 * 
 * @param size The size of the permutation.
 * @param permutation Permutation, representing the solution for QAP.
 * @param matrixA matrix A of QAP, matrix of flows.
 * @param matrixB matrix B of QAP, matrix of distances.
 * @return A score representing the final solution.
 */
int calculateScore(int size, int* permutation, int** matrixA, int** matrixB);


/**
 * @brief Solves the QAP problem with a simple heuristics.
 * 
 * @param size The size of the permutation.
 * @param matrixA matrix A of QAP, matrix of flows.
 * @param matrixB matrix B of QAP, matrix of distances.
 * @return An array representing the permutation (solution).
 */
int* heuristicSolve(int size, int** matrixA, int** matrixB, int* solution);

/**
 * @brief Solves the QAP problem with a simple anti-heuristics (tries to find a very poor solution quickly).
 * 
 * @param size The size of the permutation.
 * @param matrixA matrix A of QAP, matrix of flows.
 * @param matrixB matrix B of QAP, matrix of distances.
 * @return An array representing the permutation (solution).
 */
int* antiHeuristicSolve(int size, int** matrixA, int** matrixB, int* solution);

/**
 * @brief Produces a simple 2-Opt Neighborhood for the QAP.
 * 
 * @param pairs an array of pairs showing moves, will be created in-place.
 * @param n number of elements, size of the problem.
 * @param numMoves number of moves in total
 */
void get2NeighborhoodMoves(std::pair<int, int>* pairs, int n, int& numMoves);

/**
 * @brief Performs a move exchanging two elements by index.
 * 
 * @param permutation an array representing the current solution.
 * @param move pair representing the move by indexes.
 */
void performMove(int * permutation, std::pair<int, int> move);

/**
 * @brief Calculates the change in the QAP score.
 * 
 * @param size size of the problem.
 * @param permutation array of the current solution.
 * @param move a pair representing the current move.
 * @param matrixA a 2d-array representing the matrix of flows.
 * @param matrixB a 2d-array representing the matrix of distances.
 * @return delta value as an integer.
 */
int calculateDelta(int size, int score, int* permutation, std::pair<int, int> move, int** matrixA, int** matrixB);

/**
 * @brief Solves a QAP instance with greedy local search.
 * 
 * @param size integer representing  the size of the instance.
 * @param permutation an array representing the current solution.
 * @param matrixA a 2d-array representing the matrix of flows.
 * @param matrixB a 2d-array representing the matrix of distances.
 * @param currentScore the current score of the solution.
 * @param numEvaluations the number of perfomed delta evaluations, at the start should be 0.
 * @param numPerformedMoves the number of performed moves, at the start should be 0.
 * @return An array representing the permutation (solution).
 */
int* greedyLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves);

/**
 * @brief Solves a QAP instance with steepest local search.
 * 
 * @param size integer representing  the size of the instance.
 * @param permutation an array representing the current solution.
 * @param matrixA a 2d-array representing the matrix of flows.
 * @param matrixB a 2d-array representing the matrix of distances.
 * @param currentScore the current score of the solution.
 * @param numEvaluations the number of perfomed delta evaluations, at the start should be 0.
 * @param numPerformedMoves the number of performed moves, at the start should be 0.
 * @return An array representing the permutation (solution).
 */
int* steepestLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves);

/**
 * @brief Solves a QAP instance with random walk.
 * 
 * @param size integer representing  the size of the instance.
 * @param solution an array representing the current solution.
 * @param matrixA a 2d-array representing the matrix of flows.
 * @param matrixB a 2d-array representing the matrix of distances.
 * @param bestScore the score of the best solution found.
 * @param durationNano running time limit in nanoseconds.
 * @param numEvaluations the number of perfomed delta evaluations, at the start should be 0.
 * @param numBestSolutionUpdates the number of best solution updates, at the start should be 0.
 * @return best solution found.
 */
int* randomWalk(int size, int* solution, int** matrixA, int** matrixB, int* bestScore, int durationNano, int* numEvaluations, int* numBestSolutionUpdates);

/**
 * @brief Solves a QAP instance with random search.
 * 
 * @param size integer representing  the size of the instance.
 * @param solution an array representing the current solution.
 * @param matrixA a 2d-array representing the matrix of flows.
 * @param matrixB a 2d-array representing the matrix of distances.
 * @param bestScore the score of the best solution found.
 * @param durationNano running time limit in nanoseconds.
 * @param numEvaluations the number of perfomed delta evaluations, at the start should be 0.
 * @param numBestSolutionUpdates the number of best solution updates, at the start should be 0.
 * @return best solution found.
 */
int* randomSearch(int size, int* solution, int** matrixA, int** matrixB, int* bestScore, int durationNano, int* numEvaluations, int* numBestSolutionUpdates);

#endif
