#ifndef BOX_H
#define BOX_H

#include <GL/freeglut.h>
#include "X.h"
#include "Circle.h"
#include "Texture.h"

// This is square but has a value, -1 = empty, 0 = X, 1 = O



class Box {
private:
    float x;
    float y;
    float r;
    float b;
    float g;
    float size;
    int value;
    int boardSize;

public:
    Box() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0;
        g = 0.0f;
        b = 0.0f;
        size = 0.2f;
        value = -1;
        boardSize = 3;
    }

    Box(float x, float y, float r, float g, float b, float size, int value, int boardSize) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
        this->size = size;
        this->value = value;
        this->boardSize = boardSize;
    }

    void draw() {
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + size, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x, y - size);
        glEnd();


        if (value == 0){
            // Xshape xValue = Xshape(x, y, 0, 0, 0, size); 
            // xValue.draw();
            Texture xValue = Texture(x, y, .5* (3.0 / boardSize), .5* (3.0 / boardSize), "./assets/X.png", 0, 0);
            xValue.draw();

        }
        if (value == 1){
            // Circle cValue = Circle(x + size/2, y - size/2, 0, 0, 0, size/2); 
            // cValue.draw();
            Texture oValue = Texture(x, y, .5 * (3.0 / boardSize), .5 * (3.0 / boardSize), "./assets/O.png", 0, 0);
            oValue.draw();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + size && my <= y && my >= y - size) {
            return true;
        }
        return false;
    }

    float getX() {
        return x;
    }

    float getY() {
        return y;
    }
    
    float getSize() {
        return size;
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }

    void setSize(float size) {
        this->size = size;
    }

    int getValue(){
        return value;
    }

    void setValue(int value){
        this->value = value;
    }

    ~Box() {
        //
    }
};

#endif