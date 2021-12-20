#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    int x = 0;
    int y = 0;

    Vector() {};
    Vector(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

#endif