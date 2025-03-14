#include "Problem.h"

Problem::Problem(const std::string& filename) {
    loadInstance(filename);
}

void Problem::loadInstance(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }
    
    file >> size;

    matrixA.resize(size, std::vector<int>(size));
    matrixB.resize(size, std::vector<int>(size));
    
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            file >> matrixA[i][j];
    
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            file >> matrixB[i][j];
}

void Problem::displayInstance() const {
    std::cout << "Matrix A:" << std::endl;
    for (const auto& row : matrixA) {
        for (int a : row){
            std::cout << a << " ";
        }

        std::cout << std::endl;
    }
    
    std::cout << std::endl << "Matrix B:" << std::endl;
    for (const auto& row : matrixB) {
        for (int b : row){
            std::cout << b << " ";
        }

        std::cout << std::endl;
    }
}
