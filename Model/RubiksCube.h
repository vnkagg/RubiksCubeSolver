//
// Created by Vinayak Aggarwal on 09/07/23.
//

#ifndef RUBIKSCUBESOLVER_RUBIKSCUBE_H
#define RUBIKSCUBESOLVER_RUBIKSCUBE_H

#include "vector"
using namespace std;

class RubiksCube {
public:
    enum class FACE {
        UP, LEFT, FRONT, RIGHT, BACK, DOWN
    };
    enum class MOVE {
        L, LPRIME, L2,
        R, RPRIME, R2,
        U, UPRIME, U2,
        D, DPRIME, D2,
        F, FPRIME, F2,
        B, BPRIME, B2
    };
    enum class COLOR{
        WHITE, GREEN, RED, BLUE, ORANGE, YELLOW
    };

    static string getMove(MOVE ind);

    static int getMoveIndex(MOVE ind);

    virtual COLOR getColor(FACE face, unsigned row, unsigned col) const = 0;

    static char getColorLetter(COLOR color);

    virtual bool isSolved() const = 0;

    void print() const;

    vector<MOVE> shuffle(unsigned int times);

    RubiksCube& move(MOVE ind);

    RubiksCube& invert(MOVE ind);

    string getCornerColorString(uint8_t ind) const;

    uint8_t getCornerIndex(uint8_t ind) const;

    uint8_t getCornerOrientation(uint8_t ind) const;

    virtual RubiksCube &f() = 0;

    virtual RubiksCube &fPrime() = 0;

    virtual RubiksCube &f2() = 0;

    virtual RubiksCube &u() = 0;

    virtual RubiksCube &uPrime() = 0;

    virtual RubiksCube &u2() = 0;

    virtual RubiksCube &l() = 0;

    virtual RubiksCube &lPrime() = 0;

    virtual RubiksCube &l2() = 0;

    virtual RubiksCube &r() = 0;

    virtual RubiksCube &d() = 0;

    virtual RubiksCube &dPrime() = 0;

    virtual RubiksCube &d2() = 0;

    virtual RubiksCube &rPrime() = 0;

    virtual RubiksCube &r2() = 0;

    virtual RubiksCube &b() = 0;

    virtual RubiksCube &bPrime() = 0;

    virtual RubiksCube &b2() = 0;

};


#endif //RUBIKSCUBESOLVER_RUBIKSCUBE_H
