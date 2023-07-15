//
// Created by Vinayak Aggarwal on 10/07/23.
//

#ifndef RUBIKSCUBESOLVER_BFS_H
#define RUBIKSCUBESOLVER_BFS_H

#include "../Model/RubiksCube.h"
#include "queue"
#include "unordered_map"
#include "cmath"

template<typename T, typename H>
class BFS{
private:
    vector<RubiksCube::MOVE> solutionMoves;
    unordered_map<T, int, H> howHere;
    unordered_map<T, bool, H> visited;
    T bfs(){
        queue<T> q;
        q.push(cube);
        visited[cube] = true;
        int counter = 0;
        int layer = 1;
        int n = 1;
        while(!q.empty()){
            counter++;
            if(counter == n){
                cout << "\nCompleted BFS upto Layer : " << layer << ", number of nodes covered in this layer : " << n;
                n = pow(18, layer);
                layer++;
            }
            T currentCube = q.front();
            q.pop();
            if(currentCube.isSolved()){
                cout << "\nFound the solution at layer : " << layer;
                return currentCube;
            }
            visited[currentCube] = true;
            int byWhichMove = howHere[currentCube];
            int a = (byWhichMove/3)*3; int b = a + 2;
            for(int i = 0; i < 18; i++){
                if(a <= i && i <= b){
                    continue;
                }
                RubiksCube::MOVE thisMove = RubiksCube::MOVE(i);
                currentCube.move(thisMove);
                if(!visited[currentCube]){
                    q.push(currentCube);
                    howHere[currentCube] = i;
                }
                currentCube.invert(thisMove);
            }
        }
        return cube;
    }
public:
    T cube;
    BFS(T _cube){
      cube = _cube;
    }
    vector<RubiksCube::MOVE> solve(){
        cout << "\n------------Starting BFS--------------";
        T solvedCube = bfs();
        T iterateCubes = solvedCube;
        while(!(iterateCubes == cube)){
            RubiksCube::MOVE theMove = RubiksCube::MOVE(howHere[iterateCubes]);
            solutionMoves.push_back(theMove);
            iterateCubes.invert(theMove);
        }
        reverse(solutionMoves.begin(), solutionMoves.end());
        cout << "\n------------BFS Completed--------------";
        return solutionMoves;
    }
};

#endif //RUBIKSCUBESOLVER_BFS_H
