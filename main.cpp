//
// Created by Mihai on 3/31/2024.
//

// #include "main.h"
#include <cstdlib>
#include <iostream>
#include "Generation.h"

using std::cout;

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    Interval inter = {-5,5};
    Equation eq = {-7,3,-2};
    int dimPop = 100;
    int precision = 3;
    double crossProb = 0.5;
    double mutProb = 0.05;
    int generations = 3;

    Generation a(dimPop,inter,eq,precision,crossProb,mutProb, generations);
    a.start();
}

