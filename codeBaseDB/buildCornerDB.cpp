//
// Created by Vinayak Aggarwal on 12/07/23.
//

#include "buildCornerDB.h"
#include "./../Model/bitBoard.cpp"
#include "queue"

using namespace std;

buildCornerDB::buildCornerDB(std::string _fileName) {
    fileName = _fileName;
}

buildCornerDB::buildCornerDB(string _fileName, uint8_t init_val) {
    fileName = _fileName;
    cornerDB = cornerPatternDB(init_val);
}

bool buildCornerDB::bfsAndStore() {
    bitBoard cube;
    queue<bitBoard> q;
    q.push(cube);
    cornerDB.setNumMoves(cube, 0);
    int curr_depth = 0;
    while (!q.empty()) {
        int n = q.size();
        curr_depth++;
        if (curr_depth == 9) break;
        for (int counter = 0; counter < n; counter++) {
            bitBoard node = q.front();
            q.pop();
            for (int i = 0; i < 18; i++) {
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                if ((int) cornerDB.getNumMoves(node) > curr_depth) {
                    cornerDB.setNumMoves(node, curr_depth);
                    q.push(node);
                }
                node.invert(curr_move);
            }
        }
    }

    cornerDB.toFile(fileName);
    return true;
}