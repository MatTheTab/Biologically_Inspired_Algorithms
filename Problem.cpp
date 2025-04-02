#include "Problem.h"
#include "Problem.h"

Problem::Problem(const std::string& instanceDir, const std::string& instanceName)
    : instance(instanceName), size(0), matrixA(nullptr), matrixB(nullptr), optSolution(nullptr) {
    loadInstance(instanceDir, instanceName);
}

Problem::~Problem() {
    for (int i = 0; i < size; i++) {
        delete[] matrixA[i];
        delete[] matrixB[i];
    }
    delete[] matrixA;
    delete[] matrixB;
    delete[] optSolution;
}

void Problem::loadInstance(const std::string& instanceDir, const std::string& instanceName) {
    std::string instanceFile = instanceDir + instanceName + ".dat";
    std::string solutionFile = instanceDir + instanceName + ".sln";
    
    std::ifstream file(instanceFile);
    if (!file) {
        std::cerr << "File error: " << instanceFile << std::endl;
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
    std::ifstream solFile(solutionFile);
    if (!solFile) {
        std::cerr << "Solution file error: " << solutionFile << std::endl;
        return;
    }
    
    int solSize;
    solFile >> solSize >> optScore;
    
    if (solSize != size) {
        std::cerr << "Solution size mismatch: expected " << size << " but got " << solSize << std::endl;
        return;
    }
    
    optSolution = new int[size];
    for (int i = 0; i < size; i++) {
        solFile >> optSolution[i];
    }
    
    solFile.close();
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
    std::cout << "Optimal score: " << optScore << std::endl;
    std::cout << std::endl << "Solution: ";
    for (int i = 0; i < size; i++) {
        std::cout << optSolution[i] << " ";
    }
}

int** Problem::getMatrixA() {
    return matrixA;
}

int** Problem::getMatrixB() {
    return matrixB;
}

int Problem::getSize() {
    return size;
}

int Problem::getOptScore() {
    return optScore;
}

int* Problem::getOptSolution() {
    return optSolution;
}

std::string Problem::getInstance(){
    return instance;
}