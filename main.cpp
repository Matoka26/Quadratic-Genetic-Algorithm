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

    Interval inter = {-1,1};
    Equation eq = {-1,1,2};
    int dimPop = 10;
    int precision = 6;
    double crossProb = 0.25;
    double mutProb = 0.05;
    int generations = 2;

    Generation a(dimPop,inter,eq,precision,crossProb,mutProb, generations);
    a.start();


}

