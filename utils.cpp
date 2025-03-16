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

void saveResultsToFile(string filename, string algorithmName, string instance, double runtime, int score, int size, int* solution, int numEvaluations, int numPerformedMoves) {
    ofstream outFile(filename, ios::app);
    
    if (!outFile) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    outFile << "Algorithm: " << algorithmName << "\t";
    outFile << "Instance: " << instance << "\t";
    outFile << "Runtime: " << runtime << " nanoseconds\t";
    outFile << "Score: " << score << "\t";
    outFile << "Number of Evaluations: " << numEvaluations << "\t";
    outFile << "Number of Performed Moves: " << numPerformedMoves << "\t";
    outFile << "Solution: \t";

    for (int i = 0; i < size; i++) {
        outFile << solution[i] << " ";
    }
    outFile << "\n";
    outFile.close();
    cout << "Results successfully saved to " << filename << endl;
}
