#ifndef GAME_HPP_IMPORTED
#define GAME_HPP_IMPORTED

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "game_object.hpp"

#include <vector>

class Game {
public:
    Game(sf::RenderWindow* win);
    ~Game(){};
    
    // Main loop
    void loop();
    void handle_event(sf::Event ev);
    void render();
    
    // GameObject management
    void add_object(GameObject* object);
    
    // Events
    void handleLeftClick(int x, int y);
    
private:
    sf::RenderWindow* window;
    std::vector<GameObject*> objects;
    int fps;
};

#endif
