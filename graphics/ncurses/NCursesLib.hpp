#pragma once
#include "IGraphicsLib.hpp"
#include <ncurses.h>

class NCursesLib : public IGraphicsLib {
private:
    WINDOW* window;

public:
    NCursesLib();
    ~NCursesLib() override;
    
    bool initialize() override;
    void cleanup() override;
    void clear() override;
    void display() override;
    Input getInput() override;
    void drawText(const std::string& text, int x, int y, Color color) override;
    void drawRect(int x, int y, int width, int height, Color color) override;
    int getWindowWidth() const override;
    int getWindowHeight() const override;
};

extern "C" {
    IGraphicsLib* createGraphicsLib();
    void destroyGraphicsLib(IGraphicsLib* instance);
}