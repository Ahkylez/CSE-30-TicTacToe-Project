#ifndef CIRCLE_H
#define CIRCLE_H

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>

class Circle {
private:
    float x;
    float y;
    float r;
    float b;
    float g;
    float radius;

public:
    Circle() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0;
        g = 0.0f;
        b = 0.0f;
        radius = 0.1f;
    }

    Circle(float x, float y, float r, float g, float b, float radius) {
        this->x = x;
        this->y = y; 
        this->r = r;
        this->g = g;
        this->b = b;
        this->radius = radius;
    }

    void draw() {
        glColor3f(r, g, b);
        glLineWidth(3.0f);
        glBegin(GL_LINE_LOOP);
            for (int i = 0; i <= 100; i++){
                float angle = 2.0f * M_PI * i/100;
                float dx = radius *cos(angle);
                float dy = radius * sin(angle);
                glVertex2f(x + dx, y + dy);
            }
        glEnd();
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + radius*2 && my <= y && my >= y - radius*2) {
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
        return radius;
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }

    void setSize(float size) {
        this->radius = size;
    }

    ~Circle() {
        //
    }
};

#endif