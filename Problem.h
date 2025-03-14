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
         * @param filename Path to instance .dat file.
         */
        Problem(const std::string& filename);
        
        /**
         * @brief Loads instance from a .dat file.
         * @param filename Path to instance .dat file.
         */
        void loadInstance(const std::string& filename);
        
        /**
         * @brief Displays the matrices.
         */
        void displayInstance() const;

    private:
        int size;  ///< Instance size.
        std::vector<std::vector<int>> matrixA; ///< Matrix A.
        std::vector<std::vector<int>> matrixB; ///< Matrix B.
};
#endif