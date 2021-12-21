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

    Vector add(int x, int y) {
        return Vector(this->x + x, this->y + y);
    }

    Vector add(Vector v) {
        return Vector(x + v.x, y + v.y);
    }

    Vector subtract(int x, int y) {
        return Vector(this->x - x, this->y - y);
    }

    bool equal_to(Vector v) {
        return v.x == this->x && v.y == this->y;
    }
};

#endif