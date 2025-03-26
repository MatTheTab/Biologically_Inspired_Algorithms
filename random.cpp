#include "random.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>

using namespace std;

int* generateRandomPerturbation(int n, int* arr) {
    if (n <= 1) {
        cerr << "Error: n must be greater than 1 for generateRandomPerturbation.\n";
        return nullptr;
    }
    
    int swap_idx = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    for (int i=n; i>1; i--){
        swap_idx = rand() % i;
        swap(arr[swap_idx], arr[i-1]);
    }
    return arr;
}

int* perturbRandomly(int n, int* arr) {
    if (n <= 1) {
        cerr << "Error: n must be greater than 1 for perturbRandomly.\n";
        return nullptr;
    }
    
    int swap_idx = 0;

    for (int i=n; i>1; i--){
        swap_idx = rand() % i;
        swap(arr[swap_idx], arr[i-1]);
    }
    return arr;
}

pair<int, int> getRandomPair(int n) {
    if (n <= 2) {
        cerr << "Error: n must be greater than 2 for getRandomPair.\n";
        return {-1, -1};
    }
    int first = rand() % n;
    int second = rand() % (n-1);
    if (first == second){
        second = n-1;
    }
    return {first, second};
}