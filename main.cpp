//
// Created by Mihai on 3/31/2024.
//

// #include "main.h"
#include <cstdlib>
#include <iostream>

#include "Headers/Generation.h"

using std::cout;

int main(){
    srand(static_cast<unsigned>(time(nullptr)));

    Interval inter = {-5,5};
    Equation eq = {-2,3,10};
    int dimPop = 1000;
    int precision = 4;
    double crossProb = 0.5;
    double mutProb = 0.05;
    int generations = 10;

    Generation a(dimPop,inter,eq,precision,crossProb,mutProb, generations);
    a.start();


}

