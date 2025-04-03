#pragma once
#include "IGraphicsLib.hpp"
#include <SDL2/SDL.h>
#include <string>

class SDL2Lib : public IGraphicsLib {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    SDL_Color getSDLColor(Color color) const;

public:
    SDL2Lib();
    ~SDL2Lib() override;
    
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
