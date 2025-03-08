#include "random.h"
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

int* generateRandomPerturbation(int n) {
    int* arr = new int[n];
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

std::pair<int, int> getRandomPair(int n) {
    int first = rand() % (n + 1);
    int second = rand() % n;
    if (first == second){
        second = n;
    }
    return {first, second};
}