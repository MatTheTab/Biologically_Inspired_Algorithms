#ifndef RANDOM_H
#define RANDOM_H

#include <utility>

/**
 * @brief Generates a random permutation of numbers of size n.
 * 
 * @param n The size of the final perturbation array.
 * @return A pointer to the resulting, dynamically allocated perturbation array.
 * @note The caller is responsible for deleting the allocated array after it is no longer needed.
 */
int* generateRandomPerturbation(int n);

/**
 * @brief Generates a random pair of integers from 0 to n.
 * 
 * @param n The upper limit for the generated values.
 * @return An `std::pair<int, int>` containing two random integers.
 * @note The resulting numbers will never be equal to one another, so the result is a pair of distinct integers.
 */
std::pair<int, int> getRandomPair(int n);

#endif
