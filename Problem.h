#ifndef PROBLEM_H
#define PROBLEM_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

/**
 * @class Problem
 * @brief Class for storing and loading problem instances.
 */
class Problem {
    public:
        /**
         * @brief Constructor for Problem, loads data from a .dat file.
         * @param instanceDir Path to instance directory.
         * @param instanceName Instance name.
         */
        Problem(const std::string& instanceDir, const std::string& instanceName);

        /**
         * @brief Destructor to clean up dynamically allocated memory.
         */
        ~Problem();
        
        /**
         * @brief Loads instance from a .dat and .sln file.
         * @param instanceDir Path to instance directory.
         * @param instanceName Instance name.
         */
        void loadInstance(const std::string& instanceDir, const std::string& instanceName);
        
        /**
         * @brief Displays the matrices.
         */
        void displayInstance() const;

        /**
         * @brief Displays the optimal solution.
         */
        void displayOptimalSolution() const;

    //private:
        std::string instance; ///< Instance name.
        int size;  ///< Instance size.
        int** matrixA; ///< Matrix A.
        int** matrixB; ///< Matrix B.
        int optScore; ///< Optimal solution score.
        int* optSolution; ///< Optimal solution vector.
};
#endif