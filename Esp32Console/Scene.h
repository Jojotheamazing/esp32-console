#pragma once
#include "ButtonManager.h"

class Scene {
public:
    virtual void onEnter() {}
    virtual void onExit()  {}
    virtual void draw()    {}
    virtual void onInput(ButtonID btn, InputEvent evt) {}
    virtual void enter()   { _inside = true;  }
    virtual void exit()    { _inside = false; }
    virtual void update()  {}

    bool isInside() const { return _inside; }

protected:
    bool _inside = false;
};