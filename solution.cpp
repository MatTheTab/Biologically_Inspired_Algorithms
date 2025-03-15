#include "solution.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>

//TODO: Add <= to greedy local search, add steepest, update weights more intelligently

int calculateScore(int size, int* permutation, int** matrixA, int** matrixB){
    int score = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            score += matrixA[i][j] * matrixB[permutation[i]][permutation[j]];
        }
    }
    return score;
}

int* heuristicSolve(int size, int** matrixA, int** matrixB){
    int* rowSumA = new int[size]();
    int* rowSumB = new int[size]();
    int* indexesA = new int[size];
    int* indexesB = new int[size];
    int* solution = new int[size];

    for (int i = 0; i < size; i++){
        indexesA[i] = i;
        indexesB[i] = i;
        for (int j = 0; j < size; j++){
            rowSumA[i] += matrixA[i][j];
            rowSumB[i] += matrixB[i][j];
        }
    }

    std::sort(indexesA, indexesA + size, [&](int a, int b) {
        return rowSumA[a] > rowSumA[b];
    });

    std::sort(indexesB, indexesB + size, [&](int a, int b) {
        return rowSumB[a] < rowSumB[b];
    });

    for (int i = 0; i < size; i++){
        solution[indexesB[i]] = indexesA[i];
    }

    delete[] rowSumA;
    delete[] rowSumB;
    delete[] indexesA;
    delete[] indexesB;

    return solution;
}

std::pair<int, int>* get2NeighborhoodMoves(std::pair<int, int>* pairs, int n) {
    if (n <= 1) {
        return nullptr;
    }

    std::srand(std::time(0));
    int random1 = std::rand() % n;
    int random2 = std::rand() % n;
    int index = 0;
    int iRand;
    int jRand;
    for (int i = 1; i < n; i++) {
        iRand = (i + random1) % (n-1);
        if (iRand == 0) iRand = n-1;
        for (int j = 0; j < iRand; j++) {
            jRand = (j + random2) % iRand;
            pairs[index] = {jRand, iRand};
            index ++;
        }
    }
    return pairs;
}

void performMove(int * permutation, std::pair<int, int> move){
        int index1 = move.first;
        int index2 = move.second;
        std::swap(permutation[index1], permutation[index2]);
}


int calculateDelta(int size, int score, int* permutation, std::pair<int, int> move, int** matrixA, int** matrixB){
    int* arrCopy = new int[size];
    for (int i = 0; i < size; ++i) {
        arrCopy[i] = permutation[i];
    }
    performMove(arrCopy, move);
    int newScore = calculateScore(size, arrCopy, matrixA, matrixB) - score;
    delete [] arrCopy;
    return newScore;
}


void greedyLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB){
    int currentScore = calculateScore(size, permutation, matrixA, matrixB);
    bool improvement = true;
    int numMoves = (size * (size - 1)) / 2;
    std::pair<int, int>* moves = new std::pair<int, int>[numMoves];
    std::pair<int, int> move;
    int deltaScore;

    while (improvement) {
        improvement = false;
        moves = get2NeighborhoodMoves(moves, size);
        for (int i = 0; i < numMoves; i++){
            move = moves[i];
            deltaScore = calculateDelta(size, currentScore, permutation, move, matrixA, matrixB);
            if (deltaScore < 0){
                currentScore += deltaScore;
                performMove(permutation, move);
                improvement = true;
                break;
            }
        }
        if (!improvement){
            break;
        }
    }
    delete[] moves;
}