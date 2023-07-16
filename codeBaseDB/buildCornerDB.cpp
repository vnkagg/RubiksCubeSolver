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
    queue<pair<bitBoard, int>> q;
    q.push(make_pair(cube, 18));
    cornerDB.setNumMoves(cube, 0);
    int curr_depth = 0;
    while (!q.empty()) {
        int n = q.size();
        curr_depth++;
        if (curr_depth == 12) break;
        for (int counter = 0; counter < n; counter++) {
            bitBoard node = q.front().first;
            int lastMovePerformed = q.front().second;
            q.pop();
            int a = (lastMovePerformed/ 3) * 3; int b = a + 2;
            for (int i = 0; i < 18; i++) {
                if(a <= i && i <= b) {
                    continue;
                }
                if((int) cornerDB.getNumMoves(node) <= curr_depth){
                    continue;
                }
                auto curr_move = RubiksCube::MOVE(i);
                node.move(curr_move);
                cornerDB.setNumMoves(node, curr_depth);
                q.push(make_pair(node, i));
                node.invert(curr_move);
            }
        }
    }

    cornerDB.toFile(fileName);
    return true;
}