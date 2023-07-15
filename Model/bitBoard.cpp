//
// Created by Vinayak Aggarwal on 12/07/23.
//


#include "RubiksCube.h"
#include "cstdint"
#include "array"
#include "vector"
#include "string"

class bitBoard : public RubiksCube {
private:
    uint64_t aSolvedCube[6] {};
    uint64_t eightOnes = (1 << 8) - 1; // To Represent any Cubie on a Face/ Side
    uint64_t twentyfourOnes = (1 << 24) - 1; // To Represent one side (U)
    int indexNomenclature[3][3] = {{0, 1, 2},
                                   {7, 8, 3},
                                   {6, 5, 4}};
    void rotateFace(int ind){
        uint64_t side = bitCube[ind];
        uint64_t rightHalf = side >> (64 - 8*2);
        uint64_t leftHalf = side << (8 * 2);
        side = leftHalf | rightHalf;
        bitCube[ind] = side;
    }
    void rotateSide(int s1, int s1_1, int s1_2, int s1_3, int s2, int s2_1, int s2_2, int s2_3) {
        uint64_t clr1 = (bitCube[s2] & (eightOnes << (8 * s2_1))) >> (8 * s2_1);
        uint64_t clr2 = (bitCube[s2] & (eightOnes << (8 * s2_2))) >> (8 * s2_2);
        uint64_t clr3 = (bitCube[s2] & (eightOnes << (8 * s2_3))) >> (8 * s2_3);

        bitCube[s1] = (bitCube[s1] & ~(eightOnes << (8 * s1_1))) | (clr1 << (8 * s1_1));
        bitCube[s1] = (bitCube[s1] & ~(eightOnes << (8 * s1_2))) | (clr2 << (8 * s1_2));
        bitCube[s1] = (bitCube[s1] & ~(eightOnes << (8 * s1_3))) | (clr3 << (8 * s1_3));
    }

    int getCornerDetails(string corner){
        int ret = 0;
        for(auto c : corner){
            if(c == 'Y'){
                ret |= 1 << 2;
            }
            if(c == 'O'){
                ret |= 1 << 1;
            }
            if(c == 'G'){
                ret |= 1 << 0;
            }
        }
        if(corner[1] == 'Y' || corner[1] == 'W'){
            ret |= 1 << 3;
        } else if (corner[2] == 'Y' || corner[2] == 'W'){
            ret |= 1 << 4;
        }
        return ret;
    }
public:
    uint64_t bitCube[6] {};

    bitBoard(){
        for(int faceSide = 0 ; faceSide < 6; faceSide++){
            bitCube[faceSide] = 0;
            uint64_t clr = 1 << faceSide;
            for(int faceIndex = 0; faceIndex < 8; faceIndex++){
                bitCube[faceSide] |= (clr << (8 * faceIndex));
            }
            aSolvedCube[faceSide] = bitCube[faceSide];
        }
    }
    COLOR getColor(FACE face, unsigned int row, unsigned int col) const override{
        int ind = indexNomenclature[row][col];
        if(ind == 8){
            return (COLOR) face;
        }
        uint64_t side = bitCube[(int) face];
        uint8_t colour = side >> 8 * ind;
        int onePosition = 0;
        while (colour != 0){
            onePosition++;
            colour = colour >> 1;
        }
        return (COLOR) (onePosition - 1);
    }
    bool isSolved() const override{
        for(int i = 0; i < 6; i++){
            if(bitCube[i] != aSolvedCube[i]){
                return false;
            }
        }
        return true;
    }
    RubiksCube& u() override{
        this->rotateFace(0);
        uint64_t bitMask = (1 << 24) - 1;
        uint64_t temp = bitCube[2] & eightOnes;
        bitCube[2] = (bitCube[2] & ~eightOnes) | (bitCube[3] & eightOnes);
        bitCube[3] = (bitCube[3] & ~eightOnes) | (bitCube[4] & eightOnes);
        bitCube[4] = (bitCube[4] & ~eightOnes) | (bitCube[1] & eightOnes);
        bitCube[1] = (bitCube[1] & ~eightOnes) | temp;
        return *this;
    }
    RubiksCube& uPrime() override{
        this->u();
        this->u();
        return *this;
    }
    RubiksCube& u2() override{
        this->u();
        this->u();
        this->u();
        return *this;
    }
    RubiksCube &l() override {
        this->rotateFace(1);
        uint64_t clr1 = (bitCube[2] & (eightOnes << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitCube[2] & (eightOnes << (8 * 6))) >> (8 * 6);
        uint64_t clr3 = (bitCube[2] & (eightOnes << (8 * 7))) >> (8 * 7);

        this->rotateSide(2, 0, 7, 6, 0, 0, 7, 6);
        this->rotateSide(0, 0, 7, 6, 4, 4, 3, 2);
        this->rotateSide(4, 4, 3, 2, 5, 0, 7, 6);

        bitCube[5] = (bitCube[5] & ~(eightOnes << (8 * 0))) | (clr1 << (8 * 0));
        bitCube[5] = (bitCube[5] & ~(eightOnes << (8 * 6))) | (clr2 << (8 * 6));
        bitCube[5] = (bitCube[5] & ~(eightOnes << (8 * 7))) | (clr3 << (8 * 7));

        return *this;

    };
    RubiksCube& lPrime() override{
        this->l();
        this->l();
        this->l();
        return *this;
    }
    RubiksCube& l2() override{
        this->l();
        this->l();
        return *this;
    }
    RubiksCube &f() override {
        this->rotateFace(2);

        uint64_t clr1 = (bitCube[0] & (eightOnes << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitCube[0] & (eightOnes << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitCube[0] & (eightOnes << (8 * 6))) >> (8 * 6);

        this->rotateSide(0, 4, 5, 6, 1, 2, 3, 4);
        this->rotateSide(1, 2, 3, 4, 5, 0, 1, 2);
        this->rotateSide(5, 0, 1, 2, 3, 6, 7, 0);

        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 6))) | (clr1 << (8 * 6));
        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 7))) | (clr2 << (8 * 7));
        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &fPrime() override {
        this->f();
        this->f();
        this->f();
        return *this;
    };

    RubiksCube &f2() override {
        this->f();
        this->f();

        return *this;
    };

    RubiksCube &r() override {
        this->rotateFace(3);
        uint64_t clr1 = (bitCube[0] & (eightOnes << (8 * 2))) >> (8 * 2);
        uint64_t clr2 = (bitCube[0] & (eightOnes << (8 * 3))) >> (8 * 3);
        uint64_t clr3 = (bitCube[0] & (eightOnes << (8 * 4))) >> (8 * 4);

        this->rotateSide(0, 2, 3, 4, 2, 2, 3, 4);
        this->rotateSide(2, 2, 3, 4, 5, 2, 3, 4);
        this->rotateSide(5, 2, 3, 4, 4, 7, 6, 0);

        bitCube[4] = (bitCube[4] & ~(eightOnes << (8 * 7))) | (clr1 << (8 * 7));
        bitCube[4] = (bitCube[4] & ~(eightOnes << (8 * 6))) | (clr2 << (8 * 6));
        bitCube[4] = (bitCube[4] & ~(eightOnes << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &rPrime() override {
        this->r();
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &r2() override {
        this->r();
        this->r();

        return *this;
    };

    RubiksCube &b() override {
        this->rotateFace(4);

        uint64_t clr1 = (bitCube[0] & (eightOnes << (8 * 0))) >> (8 * 0);
        uint64_t clr2 = (bitCube[0] & (eightOnes << (8 * 1))) >> (8 * 1);
        uint64_t clr3 = (bitCube[0] & (eightOnes << (8 * 2))) >> (8 * 2);

        this->rotateSide(0, 0, 1, 2, 3, 2, 3, 4);
        this->rotateSide(3, 2, 3, 4, 5, 4, 5, 6);
        this->rotateSide(5, 4, 5, 6, 1, 6, 7, 0);

        bitCube[1] = (bitCube[1] & ~(eightOnes << (8 * 6))) | (clr1 << (8 * 6));
        bitCube[1] = (bitCube[1] & ~(eightOnes << (8 * 7))) | (clr2 << (8 * 7));
        bitCube[1] = (bitCube[1] & ~(eightOnes << (8 * 0))) | (clr3 << (8 * 0));

        return *this;
    };

    RubiksCube &bPrime() override {
        this->b();
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &b2() override {
        this->b();
        this->b();

        return *this;
    };

    RubiksCube &d() override {
        this->rotateFace(5);

        uint64_t clr1 = (bitCube[2] & (eightOnes << (8 * 4))) >> (8 * 4);
        uint64_t clr2 = (bitCube[2] & (eightOnes << (8 * 5))) >> (8 * 5);
        uint64_t clr3 = (bitCube[2] & (eightOnes << (8 * 6))) >> (8 * 6);

        this->rotateSide(2, 4, 5, 6, 1, 4, 5, 6);
        this->rotateSide(1, 4, 5, 6, 4, 4, 5, 6);
        this->rotateSide(4, 4, 5, 6, 3, 4, 5, 6);

        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 4))) | (clr1 << (8 * 4));
        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 5))) | (clr2 << (8 * 5));
        bitCube[3] = (bitCube[3] & ~(eightOnes << (8 * 6))) | (clr3 << (8 * 6));

        return *this;
    };

    RubiksCube &dPrime() override {
        this->d();
        this->d();
        this->d();

        return *this;
    };

    RubiksCube &d2() override {
        this->d();
        this->d();

        return *this;
    }
    bool operator==(const bitBoard &r1) const {
        for (int i = 0; i < 6; i++) {
            if (bitCube[i] != r1.bitCube[i]) return false;
        }
        return true;
    }

    bitBoard& operator=(const bitBoard &r1) {
        for (int i = 0; i < 6; i++) {
            bitCube[i] = r1.bitCube[i];
        }
        return *this;
    }


    uint64_t getCorners() {
        uint64_t ret = 0;
        string top_front_right = "";
        top_front_right += getColorLetter(getColor(FACE::UP, 2, 2));
        top_front_right += getColorLetter(getColor(FACE::FRONT, 0, 2));
        top_front_right += getColorLetter(getColor(FACE::RIGHT, 0, 0));

        string top_front_left = "";
        top_front_left += getColorLetter(getColor(FACE::UP, 2, 0));
        top_front_left += getColorLetter(getColor(FACE::FRONT, 0, 0));
        top_front_left += getColorLetter(getColor(FACE::LEFT, 0, 2));

        string top_back_left = "";
        top_back_left += getColorLetter(getColor(FACE::UP, 0, 0));
        top_back_left += getColorLetter(getColor(FACE::BACK, 0, 2));
        top_back_left += getColorLetter(getColor(FACE::LEFT, 0, 0));

        string top_back_right = "";
        top_back_right += getColorLetter(getColor(FACE::UP, 0, 2));
        top_back_right += getColorLetter(getColor(FACE::BACK, 0, 0));
        top_back_right += getColorLetter(getColor(FACE::RIGHT, 0, 2));

        string bottom_front_right = "";
        bottom_front_right += getColorLetter(getColor(FACE::DOWN, 0, 2));
        bottom_front_right += getColorLetter(getColor(FACE::FRONT, 2, 2));
        bottom_front_right += getColorLetter(getColor(FACE::RIGHT, 2, 0));

        string bottom_front_left = "";
        bottom_front_left += getColorLetter(getColor(FACE::DOWN, 0, 0));
        bottom_front_left += getColorLetter(getColor(FACE::FRONT, 2, 0));
        bottom_front_left += getColorLetter(getColor(FACE::LEFT, 2, 2));

        string bottom_back_right = "";
        bottom_back_right += getColorLetter(getColor(FACE::DOWN, 2, 2));
        bottom_back_right += getColorLetter(getColor(FACE::BACK, 2, 0));
        bottom_back_right += getColorLetter(getColor(FACE::RIGHT, 2, 2));

        string bottom_back_left = "";
        bottom_back_left += getColorLetter(getColor(FACE::DOWN, 2, 0));
        bottom_back_left += getColorLetter(getColor(FACE::BACK, 2, 2));
        bottom_back_left += getColorLetter(getColor(FACE::LEFT, 2, 0));

        ret |= getCornerDetails(top_front_right);
        ret = ret << 5;

        ret |= getCornerDetails(top_front_left);
        ret = ret << 5;

        ret |= getCornerDetails(top_back_right);
        ret = ret << 5;

        ret |= getCornerDetails(top_back_left);
        ret = ret << 5;

        ret |= getCornerDetails(bottom_front_right);
        ret = ret << 5;

        ret |= getCornerDetails(bottom_front_left);
        ret = ret << 5;

        ret |= getCornerDetails(bottom_back_right);
        ret = ret << 5;

        ret |= getCornerDetails(bottom_back_left);
        ret = ret << 5;

        return ret;
    }

};

struct HashbitCube {
    size_t operator()(const bitBoard& r1) const {
        std::hash<uint64_t> hasher;
        size_t hash = 0;
        for (int i = 0; i < 6; i++) {
            hash ^= hasher(r1.bitCube[i]);
        }
        return hash;
    }
};