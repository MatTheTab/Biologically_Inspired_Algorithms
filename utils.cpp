#include "utils.h"
#include <iostream>
#include <fstream>

using namespace std;

int** createMatrix(int size) {
    int** matrix = new int*[size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new int[size];
    }
    return matrix;
}


void deleteMatrix(int** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int** copyMatrix(int** original, int rows, int cols) {
    int** copy = new int*[rows];
    for (int i = 0; i < rows; i++) {
        copy[i] = new int[cols];
        for (int j = 0; j < cols; j++) {
            copy[i][j] = original[i][j];
        }
    }
    return copy;
}

int* copyArray(int* original, int size) {
    int* copy = new int[size];
    for (int i = 0; i < size; i++) {
        copy[i] = original[i];
    }
    return copy;
}

void saveRuntimeResultsToFile(string filename, string algorithmName, string instance, double runtime) {
    ofstream outFile(filename, ios::app);
    
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "Algorithm: " << algorithmName << "\t";
    outFile << "Instance: " << instance << "\t";
    outFile << "Runtime: " << runtime << " nanoseconds\t";
 
    outFile << "\n";
    outFile.close();
    // cout << "Runtime results successfully saved to " << filename << endl;
}

void savePerformanceResultsToFile(string filename, string algorithmName, string instance, int initialScore, int score, 
    int size, int* solution, int numEvaluations, int numPerformedMoves, int numBestSolutionUpdates, int optScore, int* optSolution) {
    ofstream outFile(filename, ios::app);
    
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "Algorithm: " << algorithmName << "\t";
    outFile << "Instance: " << instance << "\t";
    outFile << "Initial Score: " << initialScore << "\t";
    outFile << "Score: " << score << "\t";
    outFile << "Number of Evaluations: " << numEvaluations << "\t";
    outFile << "Number of Performed Moves: " << numPerformedMoves << "\t";
    outFile << "Number of Best Solution Updates: " << numBestSolutionUpdates << "\t";
    outFile << "Solution: \t";

    for (int i = 0; i < size; i++) {
        outFile << solution[i] << " ";
    }
    outFile << "\t";
    
    outFile << "Optimal Score: " << optScore << "\t";
    outFile << "Optimal Solution: \t";
    
    for (int i = 0; i < size; i++) {
        outFile << optSolution[i] << " ";
    }

    outFile << "\n";
    outFile.close();
    // cout << "Performance results successfully saved to " << filename << endl;
}



