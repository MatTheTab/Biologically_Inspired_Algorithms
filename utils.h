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
 * @param score The computed score/result of the algorithm.
 * @param size The size of the solution.
 * @param solution Pointer to an array containing the solution.
 * @param numEvaluations The number of evaluations performed during execution.
 * @param numPerformedMoves The number of moves performed by the algorithm.
 */
void saveResultsToFile(string filename, string algorithmName, string instance, double runtime, int score, int size, int* solution, int numEvaluations, int numPerformedMoves);

#endif