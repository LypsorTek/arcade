#pragma once

#include <string>

enum class Input {
    UP, DOWN, LEFT, RIGHT, ACTION, PAUSE, EXIT,
    NEXT_GAME, PREV_GAME, NEXT_LIB, PREV_LIB, MENU, NONE
};

enum class Color {
    BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE
};

class IGraphicsLib {
public:
    virtual ~IGraphicsLib() = default;
    
    virtual bool initialize() = 0;
    virtual void cleanup() = 0;
    
    virtual void clear() = 0;
    virtual void display() = 0;
    
    virtual Input getInput() = 0;
    
    virtual void drawText(const std::string& text, int x, int y, Color color) = 0;
    virtual void drawRect(int x, int y, int width, int height, Color color) = 0;
    
    virtual int getWindowWidth() const = 0;
    virtual int getWindowHeight() const = 0;
};

extern "C" {
    IGraphicsLib* createGraphicsLib();
    void destroyGraphicsLib(IGraphicsLib* instance);
}