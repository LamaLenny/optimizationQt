#ifndef ARGS_H
#define ARGS_H
#include "FUN_vec.h"
#include <string>
#include <vector>

class Args {
public:
    int count;
    int N_max;
    int N_good_max;
    int count_good; //Argument for random search. It is a number of "good" comparisons in a row (with decreasing objective function)
    vec x_cur;
    vec x_prev;
    double eps;
    fun f;
    vec left;
    vec right;
    double p;
    vec x0;

    Args(int N = 1000) : f(nullptr), count(0), count_good(0), N_max(N) {};
};

#endif // ARGS_H
