#ifndef UTILS_H
#define UTILS_H

#include <utility>
#include <string>

using namespace std;

/**
 * @brief Dynamically allocates a matrix of a specified size.
 * 
 * @param size The size of the matrix.
 * @return initialized matrix.
 */
int** createMatrix(int size);

/**
 * @brief Safely deletes a specified matrix.
 * 
 * @param matrix The matrix to be deleted.
 * @param size The size of the matrix.
 */
void deleteMatrix(int** matrix, int size);

/**
 * @brief Creates the exact copy of a specified matrix.
 * 
 * @param original The matrix to be copied.
 * @param rows The number of rows.
 * @param cols The number of columns.
 * @return copy of the matrix.
 */
int** copyMatrix(int** original, int rows, int cols);

/**
 * @brief Creates the exact copy of a specified 1-D array.
 * 
 * @param original The array to be copied.
 * @param size The size of the array.
 * @return copy of the array.
 */
int* copyArray(int* original, int size);

/**
 * @brief Saves the results of an algorithm execution to a text file.
 *
 *
 * @param filename The name of the file where results should be saved.
 * @param algorithmName The name of the algorithm used.
 * @param instance The instance identifier or name.
 * @param runtime The execution time of the algorithm in seconds.
 */
void saveRuntimeResultsToFile(string filename, string algorithmName, string instance, double runtime);

/**
 * @brief Saves the results of an algorithm execution to a text file.
 *
 * @param filename The name of the file where results should be saved.
 * @param algorithmName The name of the algorithm used.
 * @param instance The instance identifier or name.
 * @param initialScore The initial score used before LS algorithms.
 * @param score The computed score/result of the algorithm.
 * @param size The size of the solution.
 * @param solution Pointer to an array containing the solution.
 * @param numEvaluations The number of evaluations performed during execution.
 * @param numPerformedMoves The number of moves performed by the algorithm.
 * @param numBestSolutionUpdates The number of best solution updates performed by the algorithm.
 * @param optScore The optimal score of the instance.
 * @param optSolution Pointer to an array containing the optimal solution.
 * 
 * @details
 * The results are written in a tab-separated format for easy parsing. Each record 
 * is stored in a single line with the following structure:
 * 
 * ```
 * Algorithm: <algorithmName>    Instance: <instance>    Initial Score: <initialScore>    
 * Score: <score>    Number of Evaluations: <numEvaluations>    
 * Number of Performed Moves: <numPerformedMoves>    
 * Number of Best Solution Updates: <numBestSolutionUpdates>    
 * Solution: <solution_0> <solution_1> ... <solution_n>    
 * Optimal Score: <optScore>    
 * Optimal Solution: <optSolution_0> <optSolution_1> ... <optSolution_n>
 * ```
 * 
 * The file is opened in append mode (`ios::app`), ensuring that results from 
 * multiple runs do not overwrite previous entries. If the file cannot be opened, 
 * an error message is displayed.
 */
void savePerformanceResultsToFile(string filename, string algorithmName, string instance, int initialScore, int score, 
    int size, int* solution, int numEvaluations, int numPerformedMoves, int numBestSolutionUpdates, int optScore, int* optSolution);

#endif