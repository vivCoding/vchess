#ifndef VECTOR_H
#define VECTOR_H

#include <string>
using std::string;
using std::to_string;

/*
 * Helper class to represent chess positions and movements
*/
class Vector {
public:
    int x = 0;
    int y = 0;

    Vector() : x(0), y(0) {};
    Vector(int x, int y) {
        this->x = x;
        this->y = y;
    }

    // Set the x and y of the Vector
    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    void set(Vector v) {
        this->x = v.x;
        this->y = v.y;
    }

    /*
     * Adds this vector to the given vector. Does not change any values
     * Returns the resultant vector
    */
    Vector add(Vector v) {
        return Vector(x + v.x, y + v.y);
    }

    /*
     * Subtracts the given vector from this vector. Does not change any values
     * Returns the resultant vector
    */
    Vector subtract(Vector v) {
        return Vector(x - v.x, y - v.y);
    }

    /*
     * Multiplies x and y of this vector by given scalar. Does not change any values
     * Returns the resultant vector
    */
    Vector scale(int scalar) {
        return Vector(x * scalar, y * scalar);
    }

    /*
     * Compares this vector with given vector
    */
    bool equal_to(Vector v) {
        return x == v.x && y == v.y;
    }

    /*
     * Returns the Vector in a printable string
    */
    string as_string() {
        return "(" + to_string(x) + ", " + to_string(y) + ")";
    }
};

#endif
