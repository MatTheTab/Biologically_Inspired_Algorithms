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
int* heuristicSolve(int size, int** matrixA, int** matrixB);

std::pair<int, int>* get2NeighborhoodMoves(std::pair<int, int>* pairs, int n, int& numMoves);

void performMove(int * permutation, std::pair<int, int> move);

int calculateDelta(int size, int score, int* permutation, std::pair<int, int> move, int** matrixA, int** matrixB);

void greedyLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB);

#endif
