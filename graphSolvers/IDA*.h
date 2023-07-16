//
// Created by Vinayak Aggarwal on 12/07/23.
//

#ifndef RUBIKSCUBESOLVER_IDA_H
#define RUBIKSCUBESOLVER_IDA_H

#include "../Model/RubiksCube.h"
#include "unordered_map"
#include "queue"
#include "../codeBaseDB/cornerPatternDB.h"

template<typename T, typename H>
class IDA{
private:
    cornerPatternDB cornerDB;
    unordered_map<T, RubiksCube::MOVE, H> howHere;
    unordered_map<T, bool, H> visited;
    void reset(){
        howHere.clear();
        visited.clear();
    }
    struct Node{
        T cube;
        int depth;
        int heuristic;
        Node(T _cube, int _depth, int _heuristic) : cube(_cube), depth(_depth), heuristic(_heuristic) {};
    };
    struct compareCubeForPQ{
        bool operator()(pair<Node, int> &p1, pair<Node, int> &p2){
            auto n1 = p1.first;
            auto n2 = p2.first;
            return
                n1.depth + n1.heuristic == n2.depth + n2.heuristic ?
                    n2.heuristic > n2.heuristic                                :
                n2.depth + n2.heuristic >  n2.depth + n2.heuristic ;
        }
    };
    pair<T, int> ida(int bound){
        priority_queue<pair<Node, int> , vector<pair<Node, int>>, compareCubeForPQ> pq;
        Node inputCube = Node(cube, 0, cornerDB.getNumMoves(cube));
        pq.push(make_pair(inputCube, 18));
        int next_bound = INT_MAX;
        while(!pq.empty()){
            Node node = pq.top().first;
            int lastMovePerformed = pq.top().second;
            pq.pop();
            if(visited[node.cube]){
                // implement logic for shorter path update here
                continue;
            }
            visited[node.cube] = true;
            if(node.cube.isSolved()){
                return make_pair(node.cube, bound);
            }
            node.depth++;
            int a = (lastMovePerformed/3)*3; int b = a + 2;
            for(int i = 0; i < 18; i++){
                if(a <= i && i <= b){
                    continue;
                }
                auto currentMove = RubiksCube::MOVE(i);
                node.cube.move(currentMove);
                if(!visited[node.cube]){
                    node.heuristic = cornerDB.getNumMoves(node.cube);
                    if(node.heuristic + node.depth > bound){
                        next_bound = min(next_bound, node.heuristic + node.depth);
                    } else {
                        howHere[node.cube] = currentMove;
                        pq.push(make_pair(node, i));
                    }
                }
                node.cube.invert(currentMove);
            }
        }
        return make_pair(inputCube.cube, next_bound);

    }
public:
    T cube;
    IDA(T _cube, string _fileName){
        cube = _cube;
        cornerDB.fromFile(_fileName);
    }
    vector<RubiksCube::MOVE> solution;
    vector<RubiksCube::MOVE> solve(){
        int bound = 1;
        auto p = ida(bound);
        while(p.second != bound){
            reset();
            cout << endl << bound << ", " << p.second;
            bound = p.second;
            p = ida(bound);
        }
        cout << endl << bound << ", " << p.second << endl;
        T iterateCubes = p.first;
        while(!(iterateCubes==cube)){
            auto moveDone = howHere[iterateCubes];
            solution.push_back(moveDone);
            iterateCubes.invert(moveDone);
        }
        std::reverse(solution.begin(), solution.end());
        return solution;
    }
};

#endif //RUBIKSCUBESOLVER_IDA_H
