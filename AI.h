#ifndef AI_H
#define AI_H

#include <cstddef>
#include <string>
#include <ostream>

#include "GameState.h"
#include "ArrayList.h"
#include "Graph.h"
#include "LinkedList.h"
#include "HashTable.h"

int gameStateHash(Vertex<GameState>* state) {
    unsigned int hashValue = 0;
    
    for (int i = 0; i < state->data.size; i++) {
        for (int j = 0; j < state->data.size; j++) {
            hashValue += hashValue * 3 + (state->data.grid[i][j]+1);
        }
    }
    return (hashValue + state->data.currentTurn) % 10007;
}


class AI{


Vertex<GameState>* isSeenInTable(HashTable<Vertex<GameState>*>& Table, GameState state){
    Vertex<GameState>* vertex= new Vertex<GameState>(state);
    int tempHash=gameStateHash(vertex);
    delete vertex;
    for (int i=0; i<Table.storage[tempHash].size(); i++){
        if (Table.storage[tempHash][i]->data==state){
            return Table.storage[tempHash][i];
        }
    }
    return nullptr;
}

int MinMax(Vertex<GameState>* node, int player, int depth){
        if (node->edgeList.size() == 0){
            if (node->data.hasWon(player)){
                return 100-depth;
            }
            else if (node->data.hasWon(!player)){
                return depth-100;
            }
            else{
                return 0;
            }
        }
        else{
            int reward = MinMax(node->edgeList[0]->to, player, depth+1);
            for (int i = 1; i < node->edgeList.size(); i++){
                int curr = MinMax(node->edgeList[i]->to, player, depth+1);
                if (node->data.currentTurn == player){
                    if (curr > reward){
                        reward = curr;
                    }
                }
                else {
                    if (curr < reward){
                        reward = curr;
                    }
                }
            }
            return reward;
        }
    }




ArrayList<Vertex<GameState>*> determineStateMoves(GameState State, bool player, int depth){
    Graph<GameState> possibleGameStates;
    ArrayList<Vertex<GameState>*> moves;
    GameState tempGame= State;
    HashTable<Vertex<GameState>*> SeenStates(10007, gameStateHash);
    possibleGameStates.addVertex(new Vertex<GameState>(tempGame));
    Waypoint<GameState>* start =new  Waypoint<GameState>(possibleGameStates.vertices[0]);
    LinkedList<Waypoint<GameState>*> toExpand;
    int WaypointIndex=0;
    toExpand.append(start);
    while (!toExpand.isEmpty()){
        Waypoint<GameState>* v = toExpand.removeFirst();

        if (!v->vertex->data.done){

            for (int i = 0; i < State.size; i++){
                for (int j = 0; j < State.size; j++){
                    GameState temp = v->vertex->data;
                    bool valid = temp.play(i, j);
                    if (valid){
                        Vertex<GameState>* hasSeen= isSeenInTable(SeenStates, temp);
                        if (!hasSeen){
                            Vertex<GameState>* u = new Vertex<GameState>(temp);
                            SeenStates.add(u);
                            possibleGameStates.addVertex(u);
                            possibleGameStates.addDirectedEdge(v->vertex, u, 1);
                            
                        }else{
                            possibleGameStates.addDirectedEdge(v->vertex, hasSeen, 1);
                        }
                    }
                }
            }
            v->expand();
            for (int i=0; i<v->children.size();i++){
                if (v->children[i]->partialCost < depth){
                    toExpand.append(v->children[i]);
                }
            }
        }
    }
    for (int i=0; i<possibleGameStates.vertices[0]->edgeList.size();i++){
        moves.append(possibleGameStates.vertices[0]->edgeList[i]->to);
    }
    return moves;
}

Vec findBestPossibleMove(GameState state, bool player) {
    ArrayList<Vertex<GameState>*> possibleMoves;
    if ((state.size*state.size)-state.turnCount>9){
        possibleMoves=determineStateMoves(state, player, 2);
    }
    else{
        possibleMoves=determineStateMoves(state, player, 6);
    }
    
    Vec move= possibleMoves[0]->data.lastMove;
    int maxValue=MinMax(possibleMoves[0], player, 0);
    for (int possibleMove=1; possibleMove<possibleMoves.size(); possibleMove++){
        int currentReward=MinMax(possibleMoves[possibleMove], player, 0);
        if (currentReward>maxValue){
            maxValue=currentReward;
            move=possibleMoves[possibleMove]->data.lastMove;
        }
    }
    
    return move;
}

public:
Vec AImove(GameState State, bool difficulty) {
    if (difficulty) {
        if (State.turnCount==0) return Vec(0,0);
        return findBestPossibleMove(State, State.currentTurn);
    }

    for (int i = 0; i < State.size; i++) {
        for (int j = 0; j < State.size; j++) {
            if (State.grid[i][j] == -1) {
                return {i, j};
            }
        }
    }

    std::cerr << "AI failed to find a valid move." << std::endl;
    return {-1, -1};
}



public:
AI(){
}

};






#endif