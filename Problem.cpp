#include "Problem.h"
#include "Problem.h"

Problem::Problem(const std::string& instance_dir, const std::string& instance_name) {
    loadInstance(instance_dir, instance_name);
}

Problem::~Problem() {
    for (int i = 0; i < size; i++) {
        delete[] matrixA[i];
        delete[] matrixB[i];
    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] opt_solution;
}

void Problem::loadInstance(const std::string& instance_dir, const std::string& instance_name) {
    std::string instance_file = instance_dir + instance_name + ".dat";
    std::string solution_file = instance_dir + instance_name + ".sln";
    
    std::ifstream file(instance_file);
    if (!file) {
        std::cerr << "File error: " << instance_file << std::endl;
        return;
    }
    
    file >> size;
    matrixA = new int*[size];
    matrixB = new int*[size];
    
    for (int i = 0; i < size; i++) {
        matrixA[i] = new int[size];
        matrixB[i] = new int[size];
    }
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> matrixA[i][j];
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> matrixB[i][j];
    
    file.close();
    
    // Load solution file
    std::ifstream sol_file(solution_file);
    if (!sol_file) {
        std::cerr << "Solution file error: " << solution_file << std::endl;
        return;
    }
    
    int sol_size;
    sol_file >> sol_size >> opt_score;
    
    if (sol_size != size) {
        std::cerr << "Solution size mismatch: expected " << size << " but got " << sol_size << std::endl;
        return;
    }
    
    opt_solution = new int[size];
    for (int i = 0; i < size; i++) {
        sol_file >> opt_solution[i];
    }
    
    sol_file.close();
}

void Problem::displayInstance() const {
    std::cout << "Matrix A:" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrixA[i][j] << " ";
        }
        std::cout << std::endl;
    }
    
    std::cout << std::endl << "Matrix B:" << std::endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; ++j) {
            std::cout << matrixB[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Problem::displayOptimalSolution() const {
    std::cout << "Optimal score: " << opt_score << std::endl;
    std::cout << std::endl << "Solution: ";
    for (int i = 0; i < size; i++) {
        std::cout << opt_solution[i] << " ";
    }
}
