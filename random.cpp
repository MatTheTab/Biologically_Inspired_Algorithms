#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;

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



int main() {
    srand(time(0));
    int n = 10;
    int* arr = generateRandomPerturbation(n);
    cout << "Generated array: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    cout << "\n";
    delete[] arr;
    
    pair<int, int> randomValues = getRandomPair(n);
    int first = randomValues.first;
    int second = randomValues.second;
    cout << "Random values: " << first << " and " << second << "\n";

    cout << "Time Measuring \n";
    auto start = high_resolution_clock::now();
    auto end = start;
    int num_runs = 0;
    do{
    for (double i=0; i<10000000; i++){
        i++;
        i--;
    }
    end = high_resolution_clock::now();
    num_runs ++;
    }while(duration_cast<seconds>(end - start).count() < 100 && num_runs < 100);

    double algorithm_speed = duration_cast<nanoseconds>(end - start).count()/num_runs;
    cout<< "Algorithm Speed = "<<algorithm_speed<<" nanoseconds"<<"\n";
    return 0;
}