//
// Created by Vinayak Aggarwal on 12/07/23.
//

#ifndef RUBIKSCUBESOLVER_IDA_H
#define RUBIKSCUBESOLVER_IDA_H

#include "../Model/RubiksCube.h"
#include "unordered_map"
#include "queue"

template<typename T, typename H>
class IDA{
private:
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
        bool operator()(Node &n1, Node &n2){
            return
                n1.depth + n1.heuristic == n2.depth + n2.heuristic ?
                    n2.heuristic > n2.heuristic                                :
                n2.depth + n2.heuristic >  n2.depth + n2.heuristic ;
        }
    };
    pair<T, int> ida(int bound){
        priority_queue<Node, vector<Node>, compareCubeForPQ> pq;
        Node inputCube = Node(cube, 0, 0);
        pq.push(inputCube);
        int next_bound = INT_MAX;
        while(!pq.empty()){
            Node node = pq.top();
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
            for(int i = 0; i < 18; i++){
                auto currentMove = RubiksCube::MOVE(i);
                node.cube.move(currentMove);
                if(!visited[node.cube]){
                    node.heuristic = 0;
                    if(node.heuristic + node.depth > bound){
                        next_bound = min(next_bound, node.heuristic + node.depth);
                    } else {
                        howHere[node.cube] = currentMove;
                        pq.push(node);
                    }
                }
                node.cube.invert(currentMove);
            }
        }
        return make_pair(inputCube.cube, next_bound);

    }
public:
    T cube;
    IDA(T _cube){
        cube = _cube;
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
