#include "NCursesLib.hpp"

NCursesLib::NCursesLib() : window(nullptr) {}

NCursesLib::~NCursesLib() {
    cleanup();
}

bool NCursesLib::initialize() {
    window = initscr();
    if (!window) {
        return false;
    }
    
    cbreak();
    noecho();
    keypad(stdscr, TRUE); 
    timeout(100);
    curs_set(0);
    
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLACK);
    }
    
    return true;
}

void NCursesLib::cleanup() {
    if (window) {
        endwin();
        window = nullptr;
    }
}

void NCursesLib::clear() {
    ::clear();
}

void NCursesLib::display() {
    refresh();
}

Input NCursesLib::getInput() {
    int ch = getch();
    
    switch (ch) {
        case KEY_UP:    return Input::UP;
        case KEY_DOWN:  return Input::DOWN;
        case KEY_LEFT:  return Input::LEFT;
        case KEY_RIGHT: return Input::RIGHT;
        case ' ':       return Input::ACTION;
        case 'p':       return Input::PAUSE;
        case 27:        return Input::EXIT;      // ESC
        case KEY_F(1):  return Input::NEXT_LIB;  // F1
        case KEY_F(2):  return Input::PREV_LIB;  // F2
        case KEY_F(3):  return Input::NEXT_GAME; // F3
        case KEY_F(4):  return Input::PREV_GAME; // F4
        case KEY_F(5):  return Input::MENU;      // F5
        default:        return Input::NONE;
    }
}

void NCursesLib::drawText(const std::string& text, int x, int y, Color color) {
    int colorPair = static_cast<int>(color) + 1;
    
    if (has_colors()) {
        attron(COLOR_PAIR(colorPair));
    }
    
    mvprintw(y, x, "%s", text.c_str());
    
    if (has_colors()) {
        attroff(COLOR_PAIR(colorPair));
    }
}

void NCursesLib::drawRect(int x, int y, int width, int height, Color color) {
    int colorPair = static_cast<int>(color) + 1;
    
    if (has_colors()) {
        attron(COLOR_PAIR(colorPair));
    }
    
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            mvprintw(y + j, x + i, " ");
        }
    }
    
    if (has_colors()) {
        attroff(COLOR_PAIR(colorPair));
    }
}

int NCursesLib::getWindowWidth() const {
    int x, y;
    getmaxyx(stdscr, y, x);
    return x;
}

int NCursesLib::getWindowHeight() const {
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

extern "C" {
    IGraphicsLib* createGraphicsLib() {
        return new NCursesLib();
    }
    
    void destroyGraphicsLib(IGraphicsLib* instance) {
        delete instance;
    }
}