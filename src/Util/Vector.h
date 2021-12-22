#ifndef VECTOR_H
#define VECTOR_H

class Vector {
public:
    int x = 0;
    int y = 0;

    Vector() : x(0), y(0) {};
    Vector(int x, int y) {
        this->x = x;
        this->y = y;
    }

    Vector add(Vector v) {
        return Vector(x + v.x, y + v.y);
    }

    Vector subtract(Vector v) {
        return Vector(x - v.x, y - v.y);
    }

    Vector scale(int scalar) {
        return Vector(x * scalar, y * scalar);
    }

    bool equal_to(Vector v) {
        return x == v.x && y == v.y;
    }
};

#endif