#include "SDL2Lib.hpp"

SDL2Lib::SDL2Lib() : window(nullptr), renderer(nullptr) {}

SDL2Lib::~SDL2Lib() {
    cleanup();
}

bool SDL2Lib::initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        return false;
    }
    
    window = SDL_CreateWindow("Arcade - SDL2", 
                            SDL_WINDOWPOS_CENTERED, 
                            SDL_WINDOWPOS_CENTERED,
                            800, 600, 0);
    if (!window) {
        cleanup();
        return false;
    }
    
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cleanup();
        return false;
    }
    
    return true;
}

void SDL2Lib::cleanup() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window) {
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void SDL2Lib::clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void SDL2Lib::display() {
    SDL_RenderPresent(renderer);
}

Input SDL2Lib::getInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return Input::EXIT;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP: return Input::UP;
                case SDLK_DOWN: return Input::DOWN;
                case SDLK_LEFT: return Input::LEFT;
                case SDLK_RIGHT: return Input::RIGHT;
                case SDLK_SPACE: return Input::ACTION;
                case SDLK_p: return Input::PAUSE;
                case SDLK_ESCAPE: return Input::EXIT;
                case SDLK_F1: return Input::NEXT_LIB;
                case SDLK_F2: return Input::PREV_LIB;
                case SDLK_F3: return Input::NEXT_GAME;
                case SDLK_F4: return Input::PREV_GAME;
                case SDLK_F5: return Input::MENU;
                default: break;
            }
        }
    }
    return Input::NONE;
}

void SDL2Lib::drawText(const std::string& text, int x, int y, Color color) {
    SDL_Color sdlColor = getSDLColor(color);
    SDL_Rect rect = {x, y, static_cast<int>(text.length() * 8), 16};
    SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

void SDL2Lib::drawRect(int x, int y, int width, int height, Color color) {
    SDL_Rect rect = {x, y, width, height};
    SDL_Color sdlColor = getSDLColor(color);
    
    SDL_SetRenderDrawColor(renderer, sdlColor.r, sdlColor.g, sdlColor.b, sdlColor.a);
    SDL_RenderFillRect(renderer, &rect);
}

int SDL2Lib::getWindowWidth() const {
    int w;
    SDL_GetWindowSize(window, &w, nullptr);
    return w;
}

int SDL2Lib::getWindowHeight() const {
    int h;
    SDL_GetWindowSize(window, nullptr, &h);
    return h;
}

SDL_Color SDL2Lib::getSDLColor(Color color) const {
    switch (color) {
        case Color::BLACK:
            return {0, 0, 0, 255};
        case Color::RED:
            return {255, 0, 0, 255};
        case Color::GREEN:
            return {0, 255, 0, 255};
        case Color::YELLOW:
            return {255, 255, 0, 255};
        case Color::BLUE:
            return {0, 0, 255, 255};
        case Color::MAGENTA:
            return {255, 0, 255, 255};
        case Color::CYAN:
            return {0, 255, 255, 255};
        case Color::WHITE:
            return {255, 255, 255, 255};
        default:
            return {128, 128, 128, 255};
    }
}

extern "C" {
    IGraphicsLib* createGraphicsLib() {
        return new SDL2Lib();
    }
    
    void destroyGraphicsLib(IGraphicsLib* instance) {
        delete instance;
    }
}