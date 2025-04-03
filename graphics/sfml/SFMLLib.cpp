#include "SFMLLib.hpp"

SFMLLib::SFMLLib() {}

SFMLLib::~SFMLLib() {
    cleanup();
}

bool SFMLLib::initialize() {
    window.create(sf::VideoMode(800, 600), "Arcade - SFML");
    if (!window.isOpen()) {
        return false;
    }
    
    window.setFramerateLimit(60);
    return true;
}

void SFMLLib::cleanup() {
    if (window.isOpen()) {
        window.close();
    }
}

void SFMLLib::clear() {
    window.clear(sf::Color::Black);
}

void SFMLLib::display() {
    window.display();
}

Input SFMLLib::getInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            return Input::EXIT;
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Up: return Input::UP;
                case sf::Keyboard::Down: return Input::DOWN;
                case sf::Keyboard::Left: return Input::LEFT;
                case sf::Keyboard::Right: return Input::RIGHT;
                case sf::Keyboard::Space: return Input::ACTION;
                case sf::Keyboard::P: return Input::PAUSE;
                case sf::Keyboard::Escape: return Input::EXIT;
                case sf::Keyboard::F1: return Input::NEXT_LIB;
                case sf::Keyboard::F2: return Input::PREV_LIB;
                case sf::Keyboard::F3: return Input::NEXT_GAME;
                case sf::Keyboard::F4: return Input::PREV_GAME;
                case sf::Keyboard::F5: return Input::MENU;
                default: break;
            }
        }
    }
    return Input::NONE;
}

void SFMLLib::drawText(const std::string& text, int x, int y, Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(text.length() * 8, 16));
    rectangle.setFillColor(getSFMLColor(color));
    rectangle.setPosition(x, y);
    window.draw(rectangle);
}

void SFMLLib::drawRect(int x, int y, int width, int height, Color color) {
    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setFillColor(getSFMLColor(color));
    rectangle.setPosition(x, y);
    window.draw(rectangle);
}

int SFMLLib::getWindowWidth() const {
    return window.getSize().x;
}

int SFMLLib::getWindowHeight() const {
    return window.getSize().y;
}

sf::Color SFMLLib::getSFMLColor(Color color) const {
    switch (color) {
        case Color::BLACK:
            return sf::Color::Black;
        case Color::RED:
            return sf::Color::Red;
        case Color::GREEN:
            return sf::Color::Green;
        case Color::YELLOW:
            return sf::Color::Yellow;
        case Color::BLUE:
            return sf::Color::Blue;
        case Color::MAGENTA:
            return sf::Color::Magenta;
        case Color::CYAN:
            return sf::Color::Cyan;
        case Color::WHITE:
            return sf::Color::White;
        default:
            return sf::Color(128, 128, 128);
    }
}

extern "C" {
    IGraphicsLib* createGraphicsLib() {
        return new SFMLLib();
    }
    
    void destroyGraphicsLib(IGraphicsLib* instance) {
        delete instance;
    }
}