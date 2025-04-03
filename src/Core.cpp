#include "Core.hpp"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

Core::Core(const std::string& initialGraphicsLibPath)
    : currentGraphicsLib(nullptr), 
      currentGameLib(nullptr),
      currentGraphicsLibIndex(0),
      currentGameLibIndex(0),
      playerName("Player"),
      state(State::MENU)
{
    // Charger les chemins des bibliothèques
    loadLibrariesPaths();
    
    // Valider et charger la bibliothèque graphique initiale
    if (!loadGraphicsLib(initialGraphicsLibPath)) {
        std::cerr << "Error: '" << initialGraphicsLibPath << "' not a graphical library" << std::endl;
        exit(84);
    }
    
    // Charger les scores
    loadScores();
}

Core::~Core()
{
    // Nettoyer les ressources
}

void Core::run()
{
    // Boucle principale
    while (state != State::EXIT) {
        if (state == State::MENU) {
            displayMenu();
        } else if (state == State::GAME) {
            displayGame();
        }
        
        handleInput();
    }
}

void Core::loadLibrariesPaths()
{
    // Implémentez cette méthode pour lister les bibliothèques disponibles
}

bool Core::loadGraphicsLib(const std::string& path)
{
    // Implémentez cette méthode pour charger une bibliothèque graphique
    return true; // temporairement pour éviter l'erreur
}

bool Core::loadGameLib(const std::string& path)
{
    // Implémentez cette méthode pour charger un jeu
    return true; // temporairement pour éviter l'erreur
}

void Core::displayMenu()
{
    // Implémentez cette méthode pour afficher le menu
}

void Core::displayGame()
{
    // Implémentez cette méthode pour afficher et exécuter le jeu
}

void Core::handleInput()
{
    // Implémentez cette méthode pour gérer les entrées utilisateur
}

void Core::loadScores()
{
    // Implémentez cette méthode pour charger les scores
}