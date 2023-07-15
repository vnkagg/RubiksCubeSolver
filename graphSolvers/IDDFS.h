//
// Created by Vinayak Aggarwal on 10/07/23.
//

#ifndef RUBIKSCUBESOLVER_IDDFS_H
#define RUBIKSCUBESOLVER_IDDFS_H

#include "../Model/RubiksCube.h"
#include "./DFS.h"

template<typename T, typename H>
class IDDFS{
private:
    int maxDepth;
    vector<RubiksCube::MOVE> solution;

public:
    T cube;
    IDDFS(T _cube, int _maxDepth){
        cube = _cube;
        maxDepth = _maxDepth;
    }
    vector<RubiksCube::MOVE> solve(){
        cout << "\n------------------------------------Running IDDFS----------------------------------";
        for(int i = 1; i <= maxDepth; i++){
            DFS<T> dfs(cube, i);
            auto moves = dfs.solve();
            if(dfs.cube.isSolved()){
        cout << "\n------------------------------------Completed IDDFS----------------------------------";
                return moves;
            }
        }
        return solution;
    }
};

#endif //RUBIKSCUBESOLVER_IDDFS_H
