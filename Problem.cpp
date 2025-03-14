#include "Problem.h"

Problem::Problem(const std::string& filename) {
    loadInstance(filename);
}

Problem::~Problem(){
    for (int i = 0; i < size; i++)
        delete[] matrixA[i];
    
    for (int i = 0; i< size; i++)
        delete[] matrixB[i];

    delete[] matrixA;
    delete[] matrixB;
}

void Problem::loadInstance(const std::string& filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }
    
    file >> size;
    matrixA = new int*[size];
    matrixB = new int*[size];

    for (int i=0; i<size; i++)
        matrixA[i] = new int[size];
    
    for (int i=0; i<size; i++)
        matrixB[i] = new int[size];
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> matrixA[i][j];
    
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            file >> matrixB[i][j];
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
