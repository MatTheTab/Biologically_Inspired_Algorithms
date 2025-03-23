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
         * @param instance_dir Path to instance directory.
         * @param instance_name Instance name.
         */
        Problem(const std::string& instance_dir, const std::string& instance_name);

        /**
         * @brief Destructor to clean up dynamically allocated memory.
         */
        ~Problem();
        
        /**
         * @brief Loads instance from a .dat and .sln file.
         * @param instance_dir Path to instance directory.
         * @param instance_name Instance name.
         */
        void loadInstance(const std::string& instance_dir, const std::string& instance_name);
        
        /**
         * @brief Displays the matrices.
         */
        void displayInstance() const;

        /**
         * @brief Displays the optimal solution.
         */
        void displayOptimalSolution() const;

    //private:
        int size;  ///< Instance size.
        int** matrixA; ///< Matrix A.
        int** matrixB; ///< Matrix B.
        int opt_score; ///< Optimal solution score.
        int* opt_solution; ///< Optimal solution vector.
};
#endif