// Core.hpp
#pragma once

#include "IGraphicsLib.hpp"
#include "IGameLib.hpp"
#include "DLLoader.hpp"
#include <string>
#include <vector>
#include <map>

class Core {
private:
    DLLoader<IGraphicsLib> graphicsLoader;
    DLLoader<IGameLib> gameLoader;
    
    IGraphicsLib* currentGraphicsLib;
    IGameLib* currentGameLib;
    
    std::vector<std::string> graphicsLibPaths;
    std::vector<std::string> gameLibPaths;
    std::size_t currentGraphicsLibIndex;
    std::size_t currentGameLibIndex;
    
    std::string playerName;
    std::map<std::string, int> scores;
    
    enum class State {
        MENU,
        GAME,
        EXIT
    };
    State state;
    
    void loadLibrariesPaths();
    bool validateLibrary(const std::string& path, const std::string& expectedPrefix);
    void displayMenu();
    void displayGame();
    void handleInput();
    void loadScores();

public:
    Core(const std::string& initialGraphicsLibPath);
    ~Core();
    
    void run();
    
    bool loadGraphicsLib(const std::string& path);
    bool loadGameLib(const std::string& path);
    
    void switchToNextGraphicsLib();
    void switchToNextGameLib();
    void switchToPreviousGraphicsLib();
    void switchToPreviousGameLib();
    void restartGame();
    void returnToMenu();
};