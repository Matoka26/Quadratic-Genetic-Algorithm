//
// Created by Mihai on 4/3/2024.
//

#ifndef ALGORITMI_GENETICI_NULLSTREAM_H
#define ALGORITMI_GENETICI_NULLSTREAM_H

#endif //ALGORITMI_GENETICI_NULLSTREAM_H
#include <iostream>
#include <fstream>

class NullBuffer: public std::streambuf{
public:
    int overflow(int c) {return c;}
};