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

        /**
         * @brief Retrieves matrixA of the problem.
         * 
         * @return matrixA
         */
        int** getMatrixA();

        /**
         * @brief Retrieves matrixB of the problem.
         * 
         * @return matrixB
         */
        int** getMatrixB();

        /**
         * @brief Retrieves size of the problem.
         * 
         * @return size
         */
        int getSize();

        /**
         * @brief Retrieves optimal score of the problem.
         * 
         * @return optScore
         */
        int getOptScore();

        /**
         * @brief Retrieves the optimal solution of the problem.
         * 
         * @return optSolution
         */
        int* getOptSolution();

        /**
         * @brief Retrieves the problem instance.
         * 
         * @return instance
         */
        std::string getInstance();


    private:
        std::string instance; ///< Instance name.
        int size;  ///< Instance size.
        int** matrixA; ///< Matrix A.
        int** matrixB; ///< Matrix B.
        int optScore; ///< Optimal solution score.
        int* optSolution; ///< Optimal solution vector.
};
#endif