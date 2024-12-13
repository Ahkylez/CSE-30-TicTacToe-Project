#ifndef MENU_H
#define MENU_H

#include "Texture.h"
#include <string>
#include "Rectangle.h"
#include "Square.h"

struct Menu{
    bool mainMenu = true;
    bool mainLevel = false;
    bool options = false;
    bool difficulty = false;
    bool gameOver = false;

    void closeMenus(){
        mainMenu = false;
        mainLevel = false;
        options = false;
        difficulty = false;
        gameOver = false;
    }
};

struct MainMenuObjects{
    Texture* mainBackground;
    Texture* logo;
    Texture* buttonVsAI;
    Texture* buttonVsPlayer;
};

struct OptionObjects{
    Texture* options;
    Texture* pick;
    Texture* optionX;
    Texture* optionO;
    Texture* arrow;

    Texture* sizeButtons[3];

    Square temporaryButton;

    Square optionsBack;
    Rectangle optionsTop;
    Rectangle optionsBottom;
};

struct DifficultyObjects{
    Square difficultyBackground;
    Rectangle difficultyTop;
    Rectangle difficultyBottom;
    Texture* easyWordButton;
    Texture* hardWordButton;
    Texture* difficultyLogo;
    Texture* arrowTemp;
};

struct GameOverObjects{
    Square gameOverBackground;
    Rectangle gameOverTop;
    Rectangle gameOverBottom;
    Texture* retryButton;
    Texture* quitButton;
    Texture* gameOverLogo; 
    Texture* winsTexture;
    Texture* tieTexture;
    Texture* xTexture;
    Texture* oTexture;
    bool retry;
};

class MenuInitializer {
public:
    static void initializeMainMenu(MainMenuObjects& mainMenu) {
        mainMenu.mainBackground = new Texture(-1.0f, 1.0f, 2.0f, 2.0f, "./assets/checkerboard.png", 0.02, 0.02);
        mainMenu.logo = new Texture(-0.4f, 1.0f, 0.8f, 0.8f, "./assets/tictactoe.png", 0, 0);
        mainMenu.buttonVsAI = new Texture(-0.4f, 0.05f, 0.837f, 0.3f, "./assets/buttonplayervsai.png", 0, 0);
        mainMenu.buttonVsPlayer = new Texture(-0.4f, -0.35f, 0.837f, 0.3f, "./assets/buttonplayervsplayer.png", 0, 0);
    }

    static void initializeOptions(OptionObjects& optionsMenu) {
        optionsMenu.options = new Texture(-0.4, 0.95, 0.8, 0.4, "./assets/Options.png", 0, 0);
        optionsMenu.pick = new Texture(-0.95, -0.57, 0.7, 0.35, "./assets/Pick.png", 0, 0);
        optionsMenu.arrow = new Texture(0.6, -0.58, 0.34, 0.34, "./assets/Arrow.png", 0, 0);
        optionsMenu.optionX = new Texture(-0.35, -0.58, 0.34, 0.34, "./assets/XButton.png", 0, 0);
        optionsMenu.optionO = new Texture(0.05, -0.58, 0.34, 0.34, "./assets/OButton.png", 0, 0);
        optionsMenu.optionsBack = Square(-1.0, 1.0, 1, 0.945, 0.357, 2.0);
        optionsMenu.optionsTop = Rectangle(-1.0, 1.0, 1, 0.733, 0, 2, 0.5);
        optionsMenu.optionsBottom = Rectangle(-1.0, -0.5, 1, 0.733, 0, 2, 0.5);

        for (int i = 0; i < 3; i++) {
            if (i < 4) {
                optionsMenu.sizeButtons[i] = new Texture(-0.875 + 0.47 * i, 0.375, 0.34, 0.34, "./assets/SizeButtons/SizeButton" + std::to_string(i) + ".png", 0, 0);
            } 
            else {
                optionsMenu.sizeButtons[i] = new Texture(-0.875 + 0.47 * (i - 4), -0.065, 0.34, 0.34, "./assets/SizeButtons/SizeButton" + std::to_string(i) + ".png", 0, 0);
            }
        }

        // Make 3x3 the default
        optionsMenu.sizeButtons[0]->select();
        // Make X the default
        optionsMenu.optionX->select();
    }

    static void initializeDifficultyMenu(DifficultyObjects& difficultyMenu) {
        difficultyMenu.difficultyBackground = Square(-1.0f, 1.0f, 1, 0.945, 0.357, 2.0);
        difficultyMenu.difficultyTop = Rectangle(-1.0, 1.0, 1, 0.733, 0, 2, 0.5);
        difficultyMenu.difficultyBottom = Rectangle(-1.0, -0.5, 1, 0.733, 0, 2, 0.5);
        difficultyMenu.easyWordButton = new Texture(-0.65f, 0.415f, 0.55, 0.837, "./assets/EasyButton.png", 0, 0);
        difficultyMenu.hardWordButton = new Texture(0.12f, 0.415f, 0.55, 0.837, "./assets/HardButton.png", 0, 0);
        difficultyMenu.difficultyLogo = new Texture(-0.5f, 0.95f, 1.0f, 0.4f, "./assets/Difficulty.png", 0, 0);
        difficultyMenu.arrowTemp = new Texture(-0.15, -0.58, 0.34, 0.34, "./assets/Arrow.png", 0, 0);
        
        difficultyMenu.hardWordButton->select();
    }

    static void initializeGameOverMenu(GameOverObjects& gameOverMenu){
        gameOverMenu.gameOverBackground = Square(-1.0f, 1.0f, 1, 0.945, 0.357, 2.0);
        gameOverMenu.gameOverTop = Rectangle(-1.0, 1.0, 1, 0.733, 0, 2, 0.5);
        gameOverMenu.gameOverBottom = Rectangle(-1.0, -0.5, 1, 0.733, 0, 2, 0.5);
        gameOverMenu.gameOverLogo = new Texture(-0.5, 0.95f, 1.0f, 0.49f, "./assets/GameOver.png", 0, 0);
        gameOverMenu.retryButton = new Texture(-0.43, 0.35f, 0.837, 0.3f, "./assets/ButtonRetry.png", 0, 0);
        gameOverMenu.quitButton = new Texture(-0.43f, -0.05f, 0.837f, 0.3f, "./assets/ButtonQuit.png", 0, 0);
        gameOverMenu.winsTexture = new Texture(-0.50f, -0.58, 0.6f, 0.31f, "./assets/Wins.png", 0, 0);
        gameOverMenu.xTexture = new Texture(0.0f, -0.59, 0.5f, 0.30f, "./assets/X.png", 0, 0);
        gameOverMenu.oTexture = new Texture(0.0f, -0.59, 0.5f, 0.30f, "./assets/O.png", 0, 0);
        gameOverMenu.tieTexture = new Texture(-0.35f, -0.43, 0.73f, 0.56f, "./assets/Tie.png", 0, 0);
        gameOverMenu.retry = false;
    }

};

class MenuRenderer {
public: 
    static void renderMainMenu(MainMenuObjects& mainMenu) {
        mainMenu.mainBackground->draw();
        mainMenu.logo->draw();
        mainMenu.buttonVsAI->draw();
        mainMenu.buttonVsPlayer->draw();
        glutPostRedisplay();
    }

    static void renderOptionsMenu(OptionObjects& optionsMenu, bool vsAI) {
        optionsMenu.temporaryButton.draw();
        optionsMenu.optionsBack.draw();
        optionsMenu.optionsTop.draw();
        optionsMenu.optionsBottom.draw();
        optionsMenu.options->draw();
        optionsMenu.arrow->draw();

        // Player Vs player who goes first shouldn't matter.
        if (vsAI){
            optionsMenu.pick->draw();
            optionsMenu.optionX->draw();
            optionsMenu.optionO->draw();
        }

        for (int i = 0; i < 3; i++) {
            optionsMenu.sizeButtons[i]->draw();
        }
    }

    static void renderDifficultyMenu(DifficultyObjects& difficultyMenu) {
        difficultyMenu.difficultyBackground.draw();
        difficultyMenu.difficultyTop.draw();
        difficultyMenu.difficultyBottom.draw();
        difficultyMenu.easyWordButton->draw();
        difficultyMenu.hardWordButton->draw();
        difficultyMenu.difficultyLogo->draw();
        difficultyMenu.arrowTemp->draw();
    }

    static void renderGameOverMenu(GameOverObjects& gameOverMenu, char winner){
        gameOverMenu.gameOverBackground.draw();
        gameOverMenu.gameOverTop.draw();
        gameOverMenu.gameOverBottom.draw();
        gameOverMenu.gameOverLogo->draw();
        gameOverMenu.quitButton->draw();
        gameOverMenu.retryButton->draw();

        if (winner == 'o'){
            gameOverMenu.winsTexture->draw();
            gameOverMenu.oTexture->draw();
            
        }
        else if (winner == 'x'){
            gameOverMenu.winsTexture->draw();
            gameOverMenu.xTexture->draw();
        }
        else {
            gameOverMenu.tieTexture->draw();
        }
    }
};

class MenuMouseHandler {
public:
    static void handleMainMenuClick(float mx, float my, Menu& menuState, MainMenuObjects& mainMenu, bool& vsAI) {
        if (!menuState.mainMenu) return; // Ignore clicks if not in main menu
        if (mainMenu.buttonVsAI->contains(mx, my)) {
            menuState.closeMenus();
            menuState.options = true;
            vsAI = true;
        }
        if (mainMenu.buttonVsPlayer->contains(mx, my)) {
            menuState.closeMenus();
            menuState.options = true;
            vsAI = false;
        }
    }

    static void handleOptionsMenuClick(float mx, float my, Menu& menuState, OptionObjects& optionsMenu, int& boardSize, bool& Xstarts, bool& vsAI) {
        if (!menuState.options) return;
        if (optionsMenu.arrow->contains(mx, my)){
            if (vsAI){
                optionsMenu.arrow->select();
                menuState.closeMenus();
                menuState.difficulty = true;
            }
            else{
                optionsMenu.arrow->select();
                menuState.closeMenus();
                menuState.mainLevel = true;
            }
        }

        for (int i = 0; i < 3; i++) {
            if (optionsMenu.sizeButtons[i]->contains(mx, my)) {
                for (int j = 0; j < 3; j++) {
                    optionsMenu.sizeButtons[j]->deselect();
                }
                optionsMenu.sizeButtons[i]->select();
                boardSize = i + 3;
            }
        }

        if (optionsMenu.optionX->contains(mx, my)) {
            optionsMenu.optionX->select();
            optionsMenu.optionO->deselect();
            Xstarts = true;
        }
        if (optionsMenu.optionO->contains(mx, my)) {
            optionsMenu.optionO->select();
            optionsMenu.optionX->deselect();
            Xstarts = false;
        }
    }

    static void handleDifficultyMenuClick(float mx, float my, Menu& menuState, DifficultyObjects& difficultyMenu, bool& difficulty) {
        if (!menuState.difficulty) return;
        if (difficultyMenu.arrowTemp->contains(mx, my)) {
            menuState.closeMenus();
            menuState.mainLevel = true;
        }

        if (difficultyMenu.easyWordButton->contains(mx, my)) {
            difficultyMenu.easyWordButton->select();
            difficultyMenu.hardWordButton->deselect();
            difficulty = false; // Easy
        }

        if (difficultyMenu.hardWordButton->contains(mx, my)) {
            difficultyMenu.easyWordButton->deselect();
            difficultyMenu.hardWordButton->select();
            difficulty = true; // Hard
        }
    }

    static void handleGameOverMenuClick(float mx, float my, Menu& menuState, GameOverObjects& gameOverMenu){
        if (!menuState.gameOver) return;

        if (gameOverMenu.retryButton->contains(mx, my)){
            gameOverMenu.retry = true;
        }

        if (gameOverMenu.quitButton->contains(mx, my)){
            exit(0);
        }
    }
};

class MenuDeleter {
public:
    static void deleteMainMenu(MainMenuObjects& mainMenu){
        delete mainMenu.mainBackground;
        delete mainMenu.logo;
        delete mainMenu.buttonVsAI;
        delete mainMenu.buttonVsPlayer;

        mainMenu.mainBackground = nullptr;
        mainMenu.logo = nullptr;
        mainMenu.buttonVsAI = nullptr;
        mainMenu.buttonVsPlayer = nullptr;
    }

    static void deleteOptionsMenu(OptionObjects& optionsMenu) {
        delete optionsMenu.options;
        delete optionsMenu.pick;
        delete optionsMenu.optionX;
        delete optionsMenu.optionO;
        delete optionsMenu.arrow;

        optionsMenu.options = nullptr;
        optionsMenu.pick = nullptr;
        optionsMenu.optionX = nullptr;
        optionsMenu.optionO = nullptr;
        optionsMenu.arrow = nullptr;

        for (int i = 0; i < 8; i++) {
            delete optionsMenu.sizeButtons[i];
            optionsMenu.sizeButtons[i] = nullptr;
        }
    }

    static void deleteDifficultyMenu(DifficultyObjects& difficultyMenu) {
        delete difficultyMenu.easyWordButton;
        delete difficultyMenu.hardWordButton;
        delete difficultyMenu.difficultyLogo;
        delete difficultyMenu.arrowTemp;

        difficultyMenu.easyWordButton = nullptr;
        difficultyMenu.hardWordButton = nullptr;
        difficultyMenu.difficultyLogo = nullptr;
        difficultyMenu.arrowTemp = nullptr;
    }

    static void deleteGameOverMenu(GameOverObjects& gameOverMenu){
        delete gameOverMenu.gameOverLogo;
        delete gameOverMenu.quitButton;
        delete gameOverMenu.retryButton;
    }
};

#endif