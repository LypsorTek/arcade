#pragma once
#include "IGraphicsLib.hpp"
#include <SFML/Graphics.hpp>
#include <string>

class SFMLLib : public IGraphicsLib {
private:
    sf::RenderWindow window;
    sf::Color getSFMLColor(Color color) const;

public:
    SFMLLib();
    ~SFMLLib() override;
    
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
