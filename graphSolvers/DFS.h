//
// Created by Vinayak Aggarwal on 10/07/23.
//

#ifndef RUBIKSCUBESOLVER_DFS_H
#define RUBIKSCUBESOLVER_DFS_H

#include "../Model/RubiksCube.h"
#include "string"
#include <iostream>

template<typename T>
class DFS {
private:
    int maxDepth;
    vector<RubiksCube::MOVE> solutionMoves;
    int counter = 0;
    int nodes = 0;
    bool dfs(int depth, int lastMovePerformed, int secondLastMovePerformed){
        nodes++;
        if(cube.isSolved()){
            return true;
        }
        if(depth > maxDepth) {
            counter++;
            return false;
        }
        int a = (lastMovePerformed/3)*3; int b = a + 2;
        for(int i = 0; i < 18; i++){
            int newLastMove, newSecondLastMove;
            if(a <= i && i <= b){
                continue;
            }
            int x = (i/3)*3;
            if(x-a == 3 || a-x ==3){
                if((secondLastMovePerformed/3)*3 == x){
                    continue;
                }
                newLastMove = i;
                newSecondLastMove = lastMovePerformed;
            } else {
                newLastMove = i;
                newSecondLastMove = 18;
            }
            cube.move(RubiksCube::MOVE(i));
            solutionMoves.push_back(RubiksCube::MOVE(i));
            if(dfs(depth+1, newLastMove, newSecondLastMove)) {
                return true;
            }
            cube.invert(RubiksCube::MOVE(i));
            solutionMoves.pop_back();
        }
        return false;
    }
public :
    T cube;
    DFS(T _cube, int _maxDepth) {
        maxDepth = _maxDepth;
        cube = _cube;
    }

    vector<RubiksCube::MOVE> solve() {
        cout << "\n ------------Running DFS--------------";
        bool worked = dfs(1, 18, 18);
        if(!worked){
            cout << "\n DIDN'T FIND A SOLUTION WITH MAXDEPTH SET TO " << maxDepth;
        } else {
            cout << "\n FOUND A SOLUTION WITH MAXDEPTH SET TO " << maxDepth;
        }
        cout << "\n GONE THROUGH " << counter << " branches";
        cout << "\n GONE THROUGH " << nodes << " nodes";
        cout << "\n ------------Completed DFS--------------";
        return solutionMoves;
    }
};

#endif //RUBIKSCUBESOLVER_DFS_H
