#include <iostream>

#include "./Model/RubiksCube.h"
#include "./Model/Model3D.cpp"
#include "./graphSolvers/DFS.h"
#include "./graphSolvers/BFS.h"
#include "./graphSolvers/IDA*.h"
#include "graphSolvers/IDDFS.h"
#include "./Model/bitBoard.cpp"
#include "./codeBaseDB/buildCornerDB.h"

int main()
{

    //    Model3D cube;
    bitBoard cube;

    int shuffleDepth = 10;
    vector<RubiksCube::MOVE> shuffled_moves = cube.shuffle(shuffleDepth);
    cube.print();
    cout << "\nShuffling order : ";
    for (auto move: shuffled_moves) {
        cout << RubiksCube::getMove(move) << " ";
    }

    int searchDepth = 10;

//    DFS<bitBoard> mySolver(cube, searchDepth);
//    BFS<bitBoard, HashbitCube> mySolver(cube);
//    IDDFS<bitBoard, HashbitCube> mySolver(cube, searchDepth);
    IDA<bitBoard, HashbitCube> mySolver(cube,"/Users/vinayak/Desktop/my-projects/RubiksCubeSolver/heuristicsDepth9.txt");

//    DFS<Model3D> mySolver(cube, searchDepth);
//    BFS<Model3D, Hash3d> mySolver(cube);
//    IDDFS<Model3D, Hash3d> mySolver(cube, searchDepth);
//    IDA<Model3D, Hash3d> mySolver(cube);

    vector<RubiksCube::MOVE> solveOrder = mySolver.solve();

//  PRINTING MOVES //
    cout << "\nMove order to solve the cube : ";
    for (auto move: solveOrder) {
        cout << RubiksCube::getMove(move) << " ";
    }

//    buildCornerDB attempt2("/Users/vinayak/Desktop/my-projects/RubiksCubeSolver/heuristicsDepth=12.txt");
//    attempt2.bfsAndStore();
    return 0;
}
