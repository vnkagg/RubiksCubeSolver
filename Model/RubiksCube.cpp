//
// Created by Vinayak Aggarwal on 09/07/23.
//

#include <iostream>
#include "cstdlib"
#include "RubiksCube.h"
#include "ctime"

using namespace std;

char RubiksCube::getColorLetter(RubiksCube::COLOR color) {
    switch (color) {
        case COLOR::WHITE :
            return 'W';
        case COLOR::YELLOW :
            return 'Y';
        case(COLOR::BLUE) :
            return 'B';
        case COLOR::GREEN :
            return 'G';
        case COLOR::RED :
            return 'R';
        case COLOR::ORANGE :
            return 'O';
    }
}

string RubiksCube::getMove(MOVE move) {
    switch (move) {
        case MOVE::L:
            return "L";
        case MOVE::LPRIME:
            return "L'";
        case MOVE::L2:
            return "L2";
        case MOVE::R:
            return "R";
        case MOVE::RPRIME:
            return "R'";
        case MOVE::R2:
            return "R2";
        case MOVE::U:
            return "U";
        case MOVE::UPRIME:
            return "U'";
        case MOVE::U2:
            return "U2";
        case MOVE::D:
            return "D";
        case MOVE::DPRIME:
            return "D'";
        case MOVE::D2:
            return "D2";
        case MOVE::F:
            return "F";
        case MOVE::FPRIME:
            return "F'";
        case MOVE::F2:
            return "F2";
        case MOVE::B:
            return "B";
        case MOVE::BPRIME:
            return "B'";
        case MOVE::B2:
            return "B2";
    }
}

int RubiksCube::getMoveIndex(MOVE move){
    switch (move) {
        case MOVE::L:
            return 0;
        case MOVE::LPRIME:
            return 1;
        case MOVE::L2:
            return 2;
        case MOVE::R:
            return 3;
        case MOVE::RPRIME:
            return 4;
        case MOVE::R2:
            return 5;
        case MOVE::U:
            return 6;
        case MOVE::UPRIME:
            return 7;
        case MOVE::U2:
            return 8;
        case MOVE::D:
            return 9;
        case MOVE::DPRIME:
            return 10;
        case MOVE::D2:
            return 11;
        case MOVE::F:
            return 12;
        case MOVE::FPRIME:
            return 13;
        case MOVE::F2:
            return 14;
        case MOVE::B:
            return 15;
        case MOVE::BPRIME:
            return 16;
        case MOVE::B2:
            return 17;
    }
}

RubiksCube& RubiksCube::move(RubiksCube::MOVE move){
    switch (move) {
        case MOVE::L:
            return this->l();
        case MOVE::LPRIME:
            return this->lPrime();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->r();
        case MOVE::RPRIME:
            return this->rPrime();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->u();
        case MOVE::UPRIME:
            return this->uPrime();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->d();
        case MOVE::DPRIME:
            return this->dPrime();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->f();
        case MOVE::FPRIME:
            return this->fPrime();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->b();
        case MOVE::BPRIME :
            return this->bPrime();
        case MOVE::B2:
            return this->b2();
    }
}

RubiksCube& RubiksCube::invert(RubiksCube::MOVE move){
    switch (move) {
        case MOVE::L:
            return this->lPrime();
        case MOVE::LPRIME:
            return this->l();
        case MOVE::L2:
            return this->l2();
        case MOVE::R:
            return this->rPrime();
        case MOVE::RPRIME:
            return this->r();
        case MOVE::R2:
            return this->r2();
        case MOVE::U:
            return this->uPrime();
        case MOVE::UPRIME:
            return this->u();
        case MOVE::U2:
            return this->u2();
        case MOVE::D:
            return this->dPrime();
        case MOVE::DPRIME:
            return this->d();
        case MOVE::D2:
            return this->d2();
        case MOVE::F:
            return this->fPrime();
        case MOVE::FPRIME:
            return this->f();
        case MOVE::F2:
            return this->f2();
        case MOVE::B:
            return this->bPrime();
        case MOVE::BPRIME:
            return this->b();
        case MOVE::B2:
            return this->b2();
    }
}

void RubiksCube::print() const {
    cout << "RUBIKS CUBE " << (this->isSolved() ? "(is solved) :" : "(is not solved ) : ") << "\n\n";

//  PRINTING THE UP FACE
    for(int row = 0; row <= 2; row++){
        for(int i = 0; i < 8; i++){
            cout << " ";
        }
        for(int col = 0; col <= 2; col++){
            cout << getColorLetter(getColor(FACE::UP, row, col)) << " ";
        }
        cout << endl;
    }
    cout << endl;

//  PRINTING THE LEFT, FRONT, RIGHT, BACK FACES
    for(int row = 0; row <= 2; row++){
        // LEFT FACE
        for(int col = 0; col <= 2; col++){
           cout << getColorLetter(getColor(FACE::LEFT, row, col)) << " ";
        }
        cout << "  ";
        // FRONT FACE
        for(int col = 0; col <= 2; col++){
            cout << getColorLetter(getColor(FACE::FRONT, row, col)) << " ";
        }
        cout << "  ";
        // RIGHT FACE
        for(int col = 0; col <= 2; col++){
            cout << getColorLetter(getColor(FACE::RIGHT, row, col)) << " ";
        }
        cout << "  ";
        // BACK FACE
        for(int col = 0; col <= 2; col++){
            cout << getColorLetter(getColor(FACE::BACK, row, col)) << " ";
        }
        cout << endl;
    }
    cout << endl;
//  PRINTING THE BOTTOM FACE
    for(int row = 0; row <= 2; row++){
        for(int i = 0; i < 8; i++){
            cout << " ";
        }
        for(int col = 0; col <= 2; col++){
            cout << getColorLetter(getColor(FACE::DOWN, row, col)) << " ";
        }
        cout << endl;
    }
}

vector<RubiksCube::MOVE> RubiksCube::shuffle(unsigned int times) {
    vector<MOVE> moves_performed;
    std::srand(std::time(nullptr));
    for(int i = 0; i < times; i++){
        int selectMove = std::rand() %18;
        int last = moves_performed.size() ? getMoveIndex(moves_performed[moves_performed.size()-1]) : 18;
        int a = (last/3)*3;
        int b= a + 2;
        while(a <= selectMove && selectMove <= b){
            selectMove = std::rand() % 18;
        }
        moves_performed.push_back(static_cast<RubiksCube::MOVE>(selectMove));
        this->move(static_cast<RubiksCube::MOVE>(selectMove));
    }
    return moves_performed;
}

string RubiksCube::getCornerColorString(uint8_t ind) const {
    string str = "";

    switch (ind) {
//        UFR
        case 0:
            str += getColorLetter(getColor(FACE::UP, 2, 2));
            str += getColorLetter(getColor(FACE::FRONT, 0, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 0));
            break;

//            UFL
        case 1:
            str += getColorLetter(getColor(FACE::UP, 2, 0));
            str += getColorLetter(getColor(FACE::FRONT, 0, 0));
            str += getColorLetter(getColor(FACE::LEFT, 0, 2));
            break;

//            UBL
        case 2:
            str += getColorLetter(getColor(FACE::UP, 0, 0));
            str += getColorLetter(getColor(FACE::BACK, 0, 2));
            str += getColorLetter(getColor(FACE::LEFT, 0, 0));
            break;

//            UBR
        case 3:
            str += getColorLetter(getColor(FACE::UP, 0, 2));
            str += getColorLetter(getColor(FACE::BACK, 0, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 0, 2));
            break;

//            DFR
        case 4:
            str += getColorLetter(getColor(FACE::DOWN, 0, 2));
            str += getColorLetter(getColor(FACE::FRONT, 2, 2));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 0));
            break;

//            DFL
        case 5:
            str += getColorLetter(getColor(FACE::DOWN, 0, 0));
            str += getColorLetter(getColor(FACE::FRONT, 2, 0));
            str += getColorLetter(getColor(FACE::LEFT, 2, 2));
            break;

//            DBR
        case 6:
            str += getColorLetter(getColor(FACE::DOWN, 2, 2));
            str += getColorLetter(getColor(FACE::BACK, 2, 0));
            str += getColorLetter(getColor(FACE::RIGHT, 2, 2));
            break;

//            DBL
        case 7:
            str += getColorLetter(getColor(FACE::DOWN, 2, 0));
            str += getColorLetter(getColor(FACE::BACK, 2, 2));
            str += getColorLetter(getColor(FACE::LEFT, 2, 0));
            break;
    }
    return str;
}

uint8_t RubiksCube::getCornerIndex(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    uint8_t ret = 0;
    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        if (c == 'Y') {
            ret |= (1 << 2);
        }
    }

    for (auto c: corner) {
        if (c != 'R' && c != 'O') continue;
        if (c == 'O') {
            ret |= (1 << 1);
        }
    }

    for (auto c: corner) {
        if (c != 'B' && c != 'G') continue;
        if (c == 'G') {
            ret |= (1 << 0);
        }
    }
    return ret;
}

uint8_t RubiksCube::getCornerOrientation(uint8_t ind) const {
    string corner = getCornerColorString(ind);

    string actual_str = "";

    for (auto c: corner) {
        if (c != 'W' && c != 'Y') continue;
        actual_str.push_back(c);
    }

    if (corner[1] == actual_str[0]) {
        return 1;
    } else if (corner[2] == actual_str[0]) {
        return 2;
    } else return 0;
}