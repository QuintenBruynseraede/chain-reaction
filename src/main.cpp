#include <stdio.h>
#include <stdlib.h>
#include "SFML/Window.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.hpp"

int main(int argc, char *argv[])
{
    sf::RenderWindow win(sf::VideoMode(800,800), "Chain reaction");
    win.setVerticalSyncEnabled(true);
    win.setFramerateLimit(60);
    
    Game game(&win);
    game.loop();
    
}
