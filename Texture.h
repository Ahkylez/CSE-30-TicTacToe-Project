#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#define STB_IMAGE_IMPLEMENTATION
#include <GL/freeglut.h>
#include "stb_image.h"
#include <iostream>

struct Scrolling {
    float OffsetX = 0.0f;
    float OffsetY = 0.0f;
    float SpeedX = 0.0f;
    float SpeedY = 0.0f;
    float lastTime = 0.0f;
    float deltaTime = 0.0f;
};

class Texture{
private:
    // Properties
    float x;
    float y;
    float w;
    float h;
    bool doEffect;
    bool selected;
    Scrolling scroll;

    std::string imagePath;
    GLuint texture; // GLuint is a cross platform integer.

    void loadTexture() {
        unsigned char* imageData;
        int imageWidth;
        int imageHeight;
        int bitdepth;

        imageData = stbi_load(imagePath.c_str(), &imageWidth, &imageHeight, &bitdepth, STBI_rgb_alpha);
        if (imageData == NULL) {
            std::cerr << "Failed to load texture file" << std::endl;
        } else {
            std::cout << "Texture file loaded successfully" << std::endl;
        }

        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }

    void drawPolygon(float uMin, float vMin, float uMax, float vMax) {
        glBegin(GL_POLYGON);
        glTexCoord2f(uMin, vMin); glVertex2f(x, y);
        glTexCoord2f(uMax, vMin); glVertex2f(x + w, y);
        glTexCoord2f(uMax, vMax); glVertex2f(x + w, y - h);
        glTexCoord2f(uMin, vMax); glVertex2f(x, y - h);
        glEnd();
    }

public: 
    Texture(float x, float y, float w, float h, std::string imagePath, float scrollSpeedX, float scrollSpeedY) {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->selected = false;
        this->imagePath = imagePath;
        this->scroll.OffsetX = 0.0f; // Start with no horizontal scroll
        this->scroll.OffsetY = 0.0f; // Start with no vertical scroll
        this->scroll.SpeedX = scrollSpeedX; // Set horizontal scroll speed
        this->scroll.SpeedY = scrollSpeedY; // Set vertical scroll speed

        if (scrollSpeedX == 0.0f && scrollSpeedY == 0.0f){
            doEffect = false;
        } else{
            doEffect = true;
        }

        loadTexture();
    }

    void draw() {
        if (doEffect) {
            doScroll();
        }

        glColor3f(1.0f, 1.0f, 1.0f);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        if (selected){
            glColor3f(0.8f, 0.8f, 0.8f);
        } else{
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        if (doEffect) {
            drawPolygon(scroll.OffsetX, scroll.OffsetY, scroll.OffsetX + 1.0f, scroll.OffsetY + 1.0f);
        } else {
            drawPolygon(0.0f, 0.0f, 1.0f, 1.0f);
        }

        

        glDisable(GL_TEXTURE_2D);
    }

    void doScroll() {
        float currentTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
        scroll.deltaTime = currentTime - scroll.lastTime;
        scroll.lastTime = currentTime;

        scroll.OffsetX = std::fmod(scroll.OffsetX + scroll.SpeedX * scroll.deltaTime, 1.0f);
        scroll.OffsetY = std::fmod(scroll.OffsetY + scroll.SpeedY * scroll.deltaTime, 1.0f);
    }


    // Check if the mouse is within the bounds of the texture
    bool contains(float mx, float my) {
        return mx >= x && mx <= x + w && my <= y && my >= y - h;
    }

    // Setters
    void select() {
        selected = true;
    }

    void deselect() {
        selected = false;
    }

    // Getters
};



#endif