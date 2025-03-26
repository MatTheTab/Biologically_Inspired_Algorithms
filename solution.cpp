#include "solution.h"
#include "random.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <iostream>

int calculateScore(int size, int* permutation, int** matrixA, int** matrixB){
    int score = 0;
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            score += matrixA[i][j] * matrixB[permutation[i]][permutation[j]];
        }
    }
    return score;
}

int* heuristicSolve(int size, int** matrixA, int** matrixB, int* solution){
    int* rowSumA = new int[size]();
    int* rowSumB = new int[size]();
    int* indexesA = new int[size];
    int* indexesB = new int[size];

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

int* antiHeuristicSolve(int size, int** matrixA, int** matrixB, int* solution){
    int* rowSumA = new int[size]();
    int* rowSumB = new int[size]();
    int* indexesA = new int[size];
    int* indexesB = new int[size];

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
        return rowSumB[a] > rowSumB[b];
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

void get2NeighborhoodMoves(std::pair<int, int>* pairs, int n) {
    if (n > 1) {
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
    }
}

void performMove(int * permutation, std::pair<int, int> move){
        int index1 = move.first;
        int index2 = move.second;
        std::swap(permutation[index1], permutation[index2]);
}


int calculateDelta(int size, int score, int* permutation, std::pair<int, int> move, int** matrixA, int** matrixB) {
    int i = move.first;
    int j = move.second;    
    int delta = 0;
    int pi_i = permutation[i];
    int pi_j = permutation[j];
    
    for (int k = 0; k < size; ++k) {
        if (k != i && k != j) {
            delta += (matrixA[i][k] * (matrixB[pi_j][permutation[k]] - matrixB[pi_i][permutation[k]])) +
                     (matrixA[j][k] * (matrixB[pi_i][permutation[k]] - matrixB[pi_j][permutation[k]])) +
                     (matrixA[k][i] * (matrixB[permutation[k]][pi_j] - matrixB[permutation[k]][pi_i])) +
                     (matrixA[k][j] * (matrixB[permutation[k]][pi_i] - matrixB[permutation[k]][pi_j]));
        }
    }
    delta += (matrixA[i][j] * (matrixB[pi_j][pi_i] - matrixB[pi_i][pi_j])) +
             (matrixA[j][i] * (matrixB[pi_i][pi_j] - matrixB[pi_j][pi_i]));    
    return delta;
}

int* greedyLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves){
    bool improvement = true;
    int numAvailableMoves = (size * (size - 1)) / 2;
    std::pair<int, int>* moves = new std::pair<int, int>[numAvailableMoves];
    std::pair<int, int> move;
    int deltaScore;

    while (improvement) {
        improvement = false;
        get2NeighborhoodMoves(moves, size);
        for (int i = 0; i < numAvailableMoves; i++){
            move = moves[i];
            deltaScore = calculateDelta(size, *currentScore, permutation, move, matrixA, matrixB);
            *numEvaluations += 1;
            if (deltaScore < 0){
                *currentScore += deltaScore;
                performMove(permutation, move);
                *numPerformedMoves += 1;
                improvement = true;
                break;
            }
        }
        if (!improvement){
            break;
        }
    }
    delete[] moves;

    return permutation;
}

int* steepestLocalSearchSolve(int size, int* permutation, int** matrixA, int** matrixB, int* currentScore, int* numEvaluations, int* numPerformedMoves){
    bool improvement = true;
    int numAvailableMoves = (size * (size - 1)) / 2;
    std::pair<int, int>* moves = new std::pair<int, int>[numAvailableMoves];
    std::pair<int, int> move;
    std::pair<int, int> best_move;
    int deltaScore;
    int best_delta;


    while (improvement) {
        best_delta = 0;
        improvement = false;
        get2NeighborhoodMoves(moves, size);
        for (int i = 0; i < numAvailableMoves; i++){
            move = moves[i];
            deltaScore = calculateDelta(size, *currentScore, permutation, move, matrixA, matrixB);
            *numEvaluations += 1;
            if (deltaScore < best_delta){
                best_delta = deltaScore;
                best_move = move;
                improvement = true;
            }
        }
        if (!improvement){
            break;
        }
        else{
            *currentScore += best_delta;
            performMove(permutation, best_move);
            *numPerformedMoves += 1;
        }
    }
    delete[] moves;

    return permutation;
}

int* randomWalk(int size, int* solution, int** matrixA, int** matrixB, int* bestScore, int durationNano, int* numEvaluations, int* numBestSolutionUpdates) {
    generateRandomPerturbation(size, solution);
    *bestScore = calculateScore(size, solution, matrixA, matrixB);
    int currentScore = *bestScore;
    int* currentSolution = new int[size];
    std::copy(solution, solution + size, currentSolution);

    std::pair<int, int> move = getRandomPair(size);
    int delta = 0;

    auto start = std::chrono::high_resolution_clock::now();
    while (std::chrono::high_resolution_clock::now() - start < std::chrono::nanoseconds(durationNano)) {
        move = getRandomPair(size);
        delta = calculateDelta(size, currentScore, currentSolution, move, matrixA, matrixB);
        
        (*numEvaluations)++;

        currentScore += delta;
        if (currentScore < *bestScore) {
            *bestScore = currentScore;
            (*numBestSolutionUpdates)++;
            std::copy(currentSolution, currentSolution + size, solution);
        }
        
        performMove(currentSolution, move);
    }
    delete[] currentSolution;

    return solution;
}

int* randomSearch(int size, int* solution, int** matrixA, int** matrixB, int* bestScore, int durationNano, int* numEvaluations, int* numBestSolutionUpdates) {
    int* newSolution = new int[size];
    int newScore = 0;
    
    auto start = std::chrono::high_resolution_clock::now();
    generateRandomPerturbation(size, newSolution);
    *bestScore = calculateScore(size, newSolution, matrixA, matrixB);
    
    while (true) {
        auto now = std::chrono::high_resolution_clock::now();
        if (std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count() >= durationNano)
            break;
    
        // perturbRandomly(size, newSolution); // TODO verify if this is better? not creating refilling the array
        generateRandomPerturbation(size, newSolution);

        newScore = calculateScore(size, newSolution, matrixA, matrixB);
        (*numEvaluations)++;
        
        if (newScore < *bestScore) {
            *bestScore = newScore;
            (*numBestSolutionUpdates)++;
            std::copy(newSolution, newSolution + size, solution);
        }
    }
    delete[] newSolution;
    return solution;
}
