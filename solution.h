#ifndef SOLUTION_H
#define SOLUTION_H

#include <utility>
#include <chrono>

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
 * @brief Solves the QAP problem with a simple heuristic.
 * 
 * The heuristic works as follows:
 * 1. Compute the row sums for both matrices:
 *    - `matrixA` (flow matrix): Represents the interaction intensity between facilities.
 *    - `matrixB` (distance matrix): Represents the physical distances between locations.
 * 2. Rank the facilities based on descending order of interaction intensity (higher flow first).
 * 3. Rank the locations based on ascending order of distance sum (closer locations first).
 * 4. Assign the facility with the highest flow sum to the location with the smallest distance sum,
 *    the second-highest flow facility to the second-smallest distance location, and so on.
 * 
 * This method aims to decrease the risk of multiplying high values in matrix A and matrix B by one another, achieving relatively good solution quickly.
 * 
 * @param size The size of the permutation.
 * @param matrixA matrix A of QAP, matrix of flows.
 * @param matrixB matrix B of QAP, matrix of distances.
 * @return An array representing the permutation (solution).
 */
int* heuristicSolve(int size, int** matrixA, int** matrixB, int* solution);

/**
 * @brief Solves the QAP problem with a simple non-deterministic heuristic.
 * 
 * The heuristic works as follows:
 * 1. Compute the row sums for both matrices:
 *    - `matrixA` (flow matrix): Represents the interaction intensity between facilities.
 *    - `matrixB` (distance matrix): Represents the physical distances between locations.
 * 2. Rank the facilities based on descending order of interaction intensity (higher flow first).
 * 3. Rank the locations based on ascending order of distance sum (closer locations first).
 * 4. Assign the facility with the highest flow sum to the location with the smallest distance sum,
 *    the second-highest flow facility to the second-smallest distance location, and so on.
 *    - if two indexes have the same value of flow in matrixA, then there exists a 50% of switching the indexes, introducing non-determinism
 * 
 * This method aims to decrease the risk of multiplying high values in matrix A and matrix B by one another, achieving relatively good solution quickly.
 * 
 * @param size The size of the permutation.
 * @param matrixA matrix A of QAP, matrix of flows.
 * @param matrixB matrix B of QAP, matrix of distances.
 * @return An array representing the permutation (solution).
 */
int* heuristicSolveNonDeterministic(int size, int** matrixA, int** matrixB, int* solution);

/**
 * @brief Solves the QAP problem with a simple anti-heuristics (tries to find a very poor solution quickly).
 * 
 * The antiheuristic works as follows:
 * 1. Compute the row sums for both matrices:
 *    - `matrixA` (flow matrix): Represents the interaction intensity between facilities.
 *    - `matrixB` (distance matrix): Represents the physical distances between locations.
 * 2. Rank the facilities based on descending order of interaction intensity (higher flow first).
 * 3. Rank the locations based on descending order of distance sum (farther locations first).
 * 4. Assign the facility with the highest flow sum to the location with the highest distance sum,
 *    the second-highest flow facility to the second-farthest distance location, and so on.
 * 
 * This method aims to decrease the risk of multiplying high values in matrix A and matrix B by one another, achieving relatively poor solution quickly.
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
 * The function follows these steps:
 * 1. Generate all possible 2-opt moves (swaps of two positions).
 * 2. Evaluate each move by computing its change on the objective function (delta score).
 * 3. Apply the first move that improves the objective function.
 * 4. Repeat until no further improving move is found.
 *
 * This heuristic provides a quick improvement over an initial solution and guarantees the final solution terminating in the local optimum.
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
 * @brief Estimates the initial temperature for Simulated Annealing.
 * 
 * This function calculates an average cost difference (delta) between the current solution 
 * and random neighboring solutions. It then computes an initial temperature that would accept 
 * such uphill moves with a high predefined probability (typically 95%).
 * 
 * Steps:
 * 1. Sample 100 random 2-opt moves and compute their absolute delta costs.
 * 2. Compute the average of these absolute delta values.
 * 3. Apply the formula: T₀ = -ΔE / ln(p), where ΔE is the average difference and p is the acceptance probability (0.95).
 * 
 * Throws if average delta is zero to avoid division by zero.
 * 
 * @param size Integer representing the problem size.
 * @param permutation An array representing the current solution.
 * @param matrixA A 2D array representing the flow matrix.
 * @param matrixB A 2D array representing the distance matrix.
 * @param currentScore Pointer to the current score of the solution.
 * @return A double representing the initial temperature.
 */
double initializeTempreture(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore);

/**
 * @brief Solves a QAP instance using Simulated Annealing.
 * 
 * Simulated Annealing is a metaheuristic inspired by the annealing process in metallurgy. 
 * It allows occasional acceptance of worse solutions to escape local optima.
 * 
 * The algorithm follows these steps:
 * 1. Initialize temperature based on the average cost difference of random moves.
 * 2. At each iteration, generate a list of 2-opt neighbors (swap moves).
 * 3. Accept a move if it improves the solution, or with a probability based on temperature if it worsens it.
 * 4. After a number of moves without improvement (Markov chain length), reduce the temperature.
 * 5. Continue until no improvement is possible or the temperature drops below a threshold.
 * 
 * The best found solution during the process is preserved and returned.
 * 
 * @param size Integer representing the problem size.
 * @param permutation An array representing the initial solution; overwritten by the final solution.
 * @param matrixA A 2D array representing the flow matrix.
 * @param matrixB A 2D array representing the distance matrix.
 * @param currentScore Pointer to the current solution's score; updated in place.
 * @param numEvaluations Pointer to a counter of how many delta evaluations were performed.
 * @param numPerformedMoves Pointer to a counter of how many moves were accepted and performed.
 * @return An array representing the final solution (same pointer as input permutation).
 */
int* simulatedAnnealing(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves);

/**
 * @brief Solves a QAP instance with the quick iterative improvement method.
 * 
 * The function follows these steps:
 * 1. Generate 'dont look bits'.
 * 2. Check for improving moves.
 * 3. Update the 'dont look bits array'
 * 4. Repeat until no further improving move is found.
 *
 * This heuristic provides a quick improvement over an initial solution and guarantees speed-up at a slight performance cost.
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
int* iterativeImprovementFast(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves);

/**
 * @brief Solves a QAP instance with steepest local search.
 * 
  * The function follows these steps:
 * 1. Generate all possible 2-opt moves (swaps of two positions).
 * 2. Evaluate each move by computing its change on the objective function (delta score).
 * 3. Apply the move that improves the objective function the most.
 * 4. Repeat until no further improving move is found.
 *
 * This heuristic provides a quick improvement over an initial solution and guarantees the final solution terminating in the local optimum.
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

int** initializeTabooList(int size);

void deleteTabooList(int** matrix, int size);

int* tabooSearch(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves);

/**
 * @brief Solves a QAP instance with random walk.
 * 
 * The function follows these steps:
 * 1. Start from a randomly perturbed solution.
 * 2. Iteratively apply random moves and compute their impact.
 * 3. If an improving perturbation is found, update the best solution discovered by the method.
 * 4. Continue until the time budget (durationNano) is exhausted.
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
 * The function follows these steps:
 * 1. Start from a randomly perturbed solution.
 * 2. Iteratively produce a new, random solution
 * 3. If a new, better solution is found then update the best found score
 * 4. Continue until the time budget (durationNano) is exhausted.
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
