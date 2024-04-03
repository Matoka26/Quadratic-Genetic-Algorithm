//
// Created by Mihai on 3/31/2024.
//

#ifndef ALGORITMI_GENETICI_INTERVAL_H
#define ALGORITMI_GENETICI_INTERVAL_H

#endif //ALGORITMI_GENETICI_INTERVAL_H

struct Interval{
    int a,b;
    Interval();
    Interval(int a, int b);
};

Interval::Interval() {
    this->a = 0;
    this->b = 0;
}

Interval::Interval(int a, int b) {
    this->a = a;
    this->b = b;
}