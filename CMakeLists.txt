cmake_minimum_required(VERSION 3.25)
project(RubiksCubeSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(RubiksCubeSolver main.cpp Model/RubiksCube.cpp Model/RubiksCube.h Model/Model3D.cpp graphSolvers/DFS.h graphSolvers/BFS.h graphSolvers/IDDFS.h graphSolvers/IDA*.h Model/bitBoard.cpp codeBaseDB/nibbleArray.cpp codeBaseDB/nibbleArray.h codeBaseDB/PatternDatabase.cpp codeBaseDB/PatternDatabase.h codeBaseDB/math.cpp codeBaseDB/permutationIndexer_BlackBox.h codeBaseDB/buildCornerDB.cpp codeBaseDB/buildCornerDB.h codeBaseDB/cornerPatternDB.cpp codeBaseDB/cornerPatternDB.h)
