//
// Created by Mihai on 3/31/2024.
//

#ifndef ALGORITMI_GENETICI_EQUATION_H
#define ALGORITMI_GENETICI_EQUATION_H

#endif //ALGORITMI_GENETICI_EQUATION_H

struct Equation{
    int a,b,c;
    Equation();
    Equation(int a,int b,int c);
    double f(double x);
};

Equation::Equation() {
    this->a = 0;
    this->b = 0;
    this->c = 0;
}

Equation::Equation(int a,int b,int c){
    this->a=a;
    this->b=b;
    this->c=c;
}

double Equation::f(double x) {
    return double(this->a * x*x + this->b * x + this->c);
}