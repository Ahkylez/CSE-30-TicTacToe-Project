#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

struct AppController {
    // Children must define functions listed below
    virtual void render() = 0;

    // Children can optionally define functions listed below
    virtual void leftMouseDown(float x, float y) {};
    virtual void leftMouseUp(float x, float y) {};

    virtual void rightMouseDown(float x, float y) {};
    virtual void rightMouseUp(float x, float y) {};

    virtual void mouseMotion(float x, float y) {};
    
    virtual void keyboardDown(unsigned char key, float x, float y) {};

    virtual ~AppController() {};
};

#endif