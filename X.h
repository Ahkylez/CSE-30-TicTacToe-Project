#ifndef X_Shape_H
#define X_Shape_H

#include <GL/freeglut.h>
#include <GL/gl.h>

class Xshape {
private:
    float x;
    float y;
    float r;
    float b;
    float g;
    float size;

public:
    Xshape() {
        x = 0.0f;
        y = 0.0f;
        r = 0.0;
        g = 0.0f;
        b = 0.0f;
        size = 0.2f;
    }

    Xshape(float x, float y, float r, float g, float b, float size) {
        this->x = x;
        this->y = y;
        this->r = r;
        this->g = g;
        this->b = b;
        this->size = size;
    }

    void draw() {
        glColor3f(r, g, b);
        glLineWidth(5.0f);
        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + size, y - size);
            glVertex2f(x + size, y);
            glVertex2f(x, y - size);
        glEnd();
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

    ~Xshape() {
        //
    }
};

#endif