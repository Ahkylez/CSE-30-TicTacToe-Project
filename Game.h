#ifndef GAME_H
#define GAME_H

#include <string>
#include <ostream>
#include <limits>

#include "GameState.h"
#include "Square.h"
#include "ArrayList.h"
#include "Box.h"
#include "Graph.h"
#include "LinkedList.h"
#include "AI.h"


// remove pointer.

class Game{
    // Main stuff
    bool GameOver=false;
    char winner='_';
    GameState State;

    // Settings
    int boardSize;
    bool vsAI;
    // easy being false, hard being true
    bool difficulty;
    bool pickX;
    
    // Visuals
    Square board = Square(-0.8, 0.8, 1, 1, 1, 1.6);
    ArrayList<ArrayList<Box*>> squares;

    AI computer;

    void createBoard() {
        float size = 0.534f * (3.0 / boardSize);
        float startX = -0.8f;
        float startY = 0.8f;
        int index = 0;
        float rColor = 1;
        float gColor = 0.945;
        float bColor =  0.357;

        for (int xi = 0; xi < boardSize; xi++) {
            ArrayList<Box*> xcolumn;
            for (int yi = 0; yi < boardSize; yi++) {
                float x = startX + xi * size;
                float y = startY - yi * size;
                rColor = (index % 2 == 0) ? 1.0f : 1.0f;
                gColor = (index % 2 == 0) ? 0.945 : 0.733;
                bColor = (index % 2 == 0) ? 0.357f : 0.0f;

                xcolumn.append(new Box(x, y, rColor, gColor, bColor, size, -1, boardSize));
                index++;
            }
            if (boardSize % 2 == 0) {
                index++;
            }
            squares.append(xcolumn);
        }
    }

    Vec maxRewardMove(GameState* game, int player);

    int maxReward(Vertex<GameState>* node, int player, int depth = 10);

    Vec AImove();

public:
    Game(){
        boardSize = 3;
        vsAI = false;
        difficulty = false;
        pickX = true;
        createBoard();
        State = GameState();
    }
    Game(int boardSize, bool vsAI, bool difficulty, bool pickX){
        this->boardSize = boardSize;
        this->vsAI = vsAI;
        this->difficulty = difficulty;
        State = GameState(boardSize);
        createBoard();
        this->pickX = pickX;

        if (vsAI && !pickX){
            Vec move = computer.AImove(State, difficulty);
            squares[move.x][move.y]->setValue(State.currentTurn);
            //std::cout<<(State.play(move.x,move.y) ? "Ai made valid move":"AI did not make valid move")<<std::endl;
            State.play(move.x,move.y);
        } 

        
    }

    void handleLeftMouseDown(float mx, float my){
        if (board.contains(mx, my)){
            if (!GameOver){
                for (int x = 0; x < boardSize; x++){
                    for (int y = 0; y < boardSize; y++){
                        if (squares[x][y]->getValue() == -1 && squares[x][y]->contains(mx, my)){
                            squares[x][y]->setValue(State.currentTurn);
                            State.play(x,y);
                            if (State.hasWon(0)){
                                GameOver=true;
                                winner='x';
                            }
                            else if (State.hasWon(1)){
                                GameOver=true;
                                winner='o';
                            }
                            else if (State.done){
                                GameOver=true;
                                winner='_';
                            }

                            if(!GameOver){
                                if (vsAI){
                                    Vec move = computer.AImove(State, difficulty);
                                    squares[move.x][move.y]->setValue(State.currentTurn);
                                    //std::cout<<(State.play(move.x,move.y) ? "Ai made valid move":"AI did not make valid move")<<std::endl;
                                    State.play(move.x,move.y);
                                }
                                if (State.hasWon(!pickX)){
                                    GameOver = true;
                                    winner = (pickX ? 'o' : 'x');
                                }
                            }

                            if (State.hasWon(0)){
                                GameOver=true;
                                winner='x';
                            }
                            else if (State.hasWon(1)){
                                GameOver=true;
                                winner='o';
                            }
                            else if (State.done){
                                GameOver=true;
                                winner='_';
                            }
                            
                            // std::cout<<"Turn: "<<(State.currentTurn ? "O":"X")<<" "<<"GameOver: "<<(GameOver ? "Yes":"No")<<std::endl<<std::endl;
                        }
                            
                    }
                }
                
            }
        }
    }

    void reset() {
    for (int x = 0; x < squares.size(); x++) {
        for (int y = 0; y < squares[x].size(); y++) {
            delete squares[x][y];
        }
    }

    State = GameState(boardSize);
    createBoard();

    if (vsAI) {
        Vec move = computer.AImove(State, difficulty);
        if (move.x >= 0 && move.y >= 0) {
            squares[move.x][move.y]->setValue(State.currentTurn);
            State.play(move.x, move.y);
        }
    }
}

    void draw(){
        board.draw();
        for (int x=0; x<boardSize;x++){
            for (int y=0; y<boardSize; y++){
                squares[x][y]->draw();
            }
        }
    }



    bool getGameOver(){
        return GameOver;
    }

    char getEndGame(){
        return winner;
    }
    
    ~Game(){

        for (int x = 0; x < squares.size(); x++) {
            for (int y = 0; y < squares[x].size(); y++) {
                delete squares[x][y];
            }
        }
    }
};

int minimax(GameState state, int depth, bool maximizingPlayer, int alpha, int beta, int player) {
    if (state.hasWon(player)) {
        return 100 - depth;
    } else if (state.hasWon(!player)) {
        return depth - 100;
    } else if (state.done || depth == 10) {
        return 0;
    }

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                if (state.grid[i][j] == -1) {
                    state.grid[i][j] = player;
                    int eval = minimax(state, depth + 1, false, alpha, beta, player);
                    state.grid[i][j] = -1;
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) {
                        return maxEval;
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < state.size; i++) {
            for (int j = 0; j < state.size; j++) {
                if (state.grid[i][j] == -1) {
                    state.grid[i][j] = !player;
                    int eval = minimax(state, depth + 1, true, alpha, beta, player);
                    state.grid[i][j] = -1;
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha) {
                        return minEval;
                    }
                }
            }
        }
        return minEval;
    }
}

Vec findBestMove(GameState state, int player) {
    Vec bestMove = {-1, -1};
    int bestValue = std::numeric_limits<int>::min();

    for (int i = 0; i < state.size; i++) {
        for (int j = 0; j < state.size; j++) {
            if (state.grid[i][j] == -1) {
                state.grid[i][j] = player;
                int moveValue = minimax(state, 0, false, 
                    std::numeric_limits<int>::min(), 
                    std::numeric_limits<int>::max(), player);
                state.grid[i][j] = -1;

                if (moveValue > bestValue) {
                    bestMove = {i, j};
                    bestValue = moveValue;
                }
            }
        }
    }

    return bestMove;
}

Vec Game::AImove() {
    if (difficulty) {
        return findBestMove(State, State.currentTurn);
    }

    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardSize; j++) {
            if (squares[i][j]->getValue() == -1) {
                return {i, j};
            }
        }
    }

    std::cerr << "AI failed to find a valid move." << std::endl;
    return {-1, -1};
}

#endif

