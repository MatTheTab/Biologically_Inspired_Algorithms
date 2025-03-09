#ifndef TIME_MEASURE_H
#define TIME_MEASURE_H

#include <utility>
#include "time_measure.h"
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

/**
 * @brief Measures the execution time of a function passed as a function pointer or lambda expression.
 * 
 * @tparam Func Function type, like a pointer of a lambda expression.
 * @tparam Args Function argument types.
 * @param func The function whose runtime is going to be measured.
 * @param args Arguments to pass to the function.
 * @return The average execution time per call in nanoseconds as a 'double' datatype.
 */
template<typename Func, typename... Args>
double measureFunctionRuntime(Func func, Args... args) {
    auto start = high_resolution_clock::now();
    auto end = start;
    int num_runs = 0;
        do{
            func(args...);
            end = high_resolution_clock::now();
            num_runs ++;
        }while(duration_cast<seconds>(end - start).count() < 100 && num_runs < 100);
    double algorithm_speed = duration_cast<nanoseconds>(end - start).count()/num_runs;
    return algorithm_speed;
}

#endif