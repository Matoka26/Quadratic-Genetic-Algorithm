//
// Created by Mihai on 4/3/2024.
//

#ifndef ALGORITMI_GENETICI_NULLSTREAM_H
#define ALGORITMI_GENETICI_NULLSTREAM_H

#endif //ALGORITMI_GENETICI_NULLSTREAM_H
#include <iostream>
#include <fstream>

// Define a NullBuffer class to redirect output to nothing
class NullBuffer : public std::streambuf {
public:
    int overflow(int c) { return c; } // Ignore any input
};

// Define a NullStream class to redirect output to nothing
class NullStream : public std::ostream {
public:
    NullStream() : std::ostream(&nullBuffer) {}
private:
    NullBuffer nullBuffer;
};