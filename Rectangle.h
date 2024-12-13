#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <GL/freeglut.h>

class Rectangle {
private:
    float x;
    float y;
    float r;
    float b;
    float g;
    float w;
    float h;

public:
    Rectangle() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0;
        g = 0.0f;
        b = 0.0f;
        w = 0.2f;
        h = 0.2f;
    }

    Rectangle(float x, float y, float r, float g, float b, float w, float h) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
        this->w = w;
        this->h = h;
    }

    void draw() {
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);
            glVertex2f(x, y);
            glVertex2f(x + w, y);
            glVertex2f(x + w, y - h);
            glVertex2f(x, y - h);
        glEnd();
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + w && my <= y && my >= y - h) {
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
    
    float getW() {
        return w;
    }

    float getH(){
        return h;
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }

    void setW(float w) {
        this->w = w;
    }

    void setH(float h){
        this->h = h;
    }

    ~Rectangle() {
        //
    }
};

#endif