#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <cstddef>
#include <iostream>
#include <GL/freeglut.h>
#include <linux/limits.h>
#include <string>
#include "AppController.h"
#include "ArrayList.h"
#include "GameState.h"
#include "Graph.h"
#include "LinkedList.h"
#include "X.h"
#include "Menu.h"

#include "Box.h"
#include "Circle.h"
#include "Game.h"



class Controller : public AppController {
    // Menus
    Menu menuState;
    MainMenuObjects mainMenu;
    OptionObjects optionsMenu;
    DifficultyObjects difficultyMenu;
    GameOverObjects gameOverMenu;
    
    // Game
    Game* currentGame = nullptr;
    bool vsAI=false;
    bool pickX = true;
    bool difficulty = true;
    int boardSize=3;
    bool gameInitialized = false;
    char winner = '_';

public:
    Controller(){
        MenuInitializer::initializeMainMenu(mainMenu);
        MenuInitializer::initializeOptions(optionsMenu);
        MenuInitializer::initializeDifficultyMenu(difficultyMenu);
        MenuInitializer::initializeGameOverMenu(gameOverMenu);
    }

    void render() {

        if (menuState.mainMenu) MenuRenderer::renderMainMenu(mainMenu);
        
        if (menuState.options)  MenuRenderer::renderOptionsMenu(optionsMenu, vsAI);
        
        if (menuState.difficulty)  MenuRenderer::renderDifficultyMenu(difficultyMenu);

        if (menuState.mainLevel && gameInitialized) currentGame->draw();

        if (menuState.gameOver) MenuRenderer::renderGameOverMenu(gameOverMenu, winner);
    }

    void leftMouseDown(float mx, float my) {

         if (menuState.gameOver){
            MenuMouseHandler::handleGameOverMenuClick(mx, my, menuState, gameOverMenu);
            if (gameOverMenu.retry == true){
                resetGame();
            }
        }

        if (menuState.mainLevel && gameInitialized){
            currentGame->handleLeftMouseDown(mx,my);
            if (currentGame->getGameOver()){
                winner = currentGame->getEndGame();
                menuState.gameOver = true;
            }
        }

        if (menuState.mainMenu){
            MenuMouseHandler::handleMainMenuClick(mx, my, menuState, mainMenu, vsAI);
        }

        if (menuState.options){
            MenuMouseHandler::handleOptionsMenuClick(mx, my, menuState, optionsMenu, boardSize, pickX, vsAI);
            if (menuState.mainLevel){
                initializeGame();
            }
        }
       
        if (menuState.difficulty){
            MenuMouseHandler::handleDifficultyMenuClick(mx, my, menuState, difficultyMenu, difficulty);

            if (menuState.mainLevel && !gameInitialized){
                initializeGame();
            }
        }
        

    }


    void initializeGame() {
        if (currentGame) {
            delete currentGame;
        }
        currentGame = new Game(boardSize, vsAI, difficulty, pickX);
        gameInitialized = true;
    }

    void resetGame(){
        menuState.closeMenus();
        menuState.mainMenu = true;

        Game* currentGame = nullptr;
        vsAI=false;
        pickX = true;
        difficulty = true;
        boardSize=3;
        gameInitialized = false;
        winner = '_';

        // Options Menu
        optionsMenu.arrow->deselect();
        optionsMenu.optionX->select();
        optionsMenu.optionO->deselect();

        for (int i = 0; i < 3; i++){
            optionsMenu.sizeButtons[i]->deselect();
        }
        optionsMenu.sizeButtons[0]->select();

        // Difficulty Menu
        difficultyMenu.easyWordButton->deselect();
        difficultyMenu.hardWordButton->select();
        difficultyMenu.arrowTemp->deselect();

        // Game over menu
        gameOverMenu.retry = false;
    }





    ~Controller(){
        // Release memory
        MenuDeleter::deleteMainMenu(mainMenu);
        MenuDeleter::deleteOptionsMenu(optionsMenu);
        MenuDeleter::deleteDifficultyMenu(difficultyMenu);
    }
};

#endif