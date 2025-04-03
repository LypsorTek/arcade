#pragma once

#include "IGraphicsLib.hpp"

class IGameLib {
public:
    virtual ~IGameLib() = default;
    
    virtual bool initialize() = 0;
    virtual void cleanup() = 0;
    
    virtual void update(float deltaTime) = 0;
    virtual void render(IGraphicsLib* graphicsLib) = 0;
    
    virtual void handleInput(Input input) = 0;
    
    virtual int getScore() const = 0;
    virtual bool isGameOver() const = 0;
    virtual void reset() = 0;
};

extern "C" {
    IGameLib* createGameLib();
    void destroyGameLib(IGameLib* instance);
}