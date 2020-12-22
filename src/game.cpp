#include "game.hpp"
#include "sphere.hpp"
#include "utils.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <cstdlib>

Game::Game ( sf::RenderWindow* win )
{
    this->window = win;
    this->fps = 60;
    this->restart();
}

void Game::add_object(GameObject* object)
{
    this->objects.push_back(object);
}

void Game::restart()
{
    // Set some initial values
    this->tries_left = 5;
    this->score = 0;
    this->score_multiplier = 1;
    this->game_over = false;
    
    // Clean up previous game if necessary
    if (this->objects.size() > 0) {
        for (auto i=this->objects.begin();i!=this->objects.end();i++) {
            delete *i;
        }
    }
    
    // Create new spheres
    this->objects = std::vector<GameObject*>();
    for (int i=0;i<250;i++) {
        Sphere* x = new Sphere(5,0,this);
        x->setMaxPosition(sf::Vector2f(this->window->getSize().x,this->window->getSize().y));
        x->setPosition(sf::Vector2f(30+random_float()*(x->getMaxPosition().x-30),30+random_float()*(x->getMaxPosition().y-30)));
        x->setVelocity(sf::Vector2f(-100+random_float()*200,-100+random_float()*200));

        this->add_object(x);
    }
}



void Game::loop()
{
    while (this->window->isOpen()) {
        
        // Handle events
        sf::Event event;
        while (this->window->pollEvent(event)) {
            this->handle_event(event);
        }
        
        // Update GameObjects
        for (auto i=this->objects.begin();i!=this->objects.end();i++) {
            (*i)->timestep(1.0/this->fps);
        }
        
        // Handle chain reactions
        std::vector<Sphere*> explodingSpheres;
        for (auto i=this->objects.begin();i!=this->objects.end();i++) {
            Sphere* x = dynamic_cast<Sphere*>(*i);
            if (x->isExploding())
                explodingSpheres.push_back(x);
        }
        
        for (auto i=this->objects.begin();i!=this->objects.end();i++) {
            Sphere* x = dynamic_cast<Sphere*>(*i);
            for (auto ex : explodingSpheres) {
                int minDist = ex->isSuperSphere()? 50 : 35;
                if (dist((*ex).getPosition(),x->getPosition()) < minDist) {
                    x->explode();
                }
            }
        }
        
        // Remove inactive GameObjects
        std::vector<GameObject*> new_objects;
        for (auto i=this->objects.begin();i!=this->objects.end();i++) {
            if (!(*i)->isRemoved()) {
                new_objects.push_back(*i);
            }
        }
        this->objects = new_objects;
        
        // Render everything
        this->render();
    }
}

void Game::handle_event ( sf::Event ev )
{
    switch (ev.type) {
        case sf::Event::Closed: 
            this->window->close();
        case sf::Event::MouseButtonReleased:
            if (ev.mouseButton.button == 0) {
                this->handleLeftClick(ev.mouseButton.x,ev.mouseButton.y);
            }
    }
    
    return;
}

void Game::render()
{
    this->window->clear(sf::Color::Black);
    
    for (auto i=this->objects.begin();i!=this->objects.end();i++) {
        (*i)->draw(this->window);
    }
    
    // Draw score and tries left 
    sf::Font font;
    font.loadFromFile("assets/fonts/FreeSansBold.ttf");
    
    sf::Text score, tries_left, mul;
    
    score.setFont(font);
    score.setString("Score: "+std::to_string(this->score));
    score.setCharacterSize(20); // in pixels, not points!
    score.setFillColor(sf::Color::White);
    score.setPosition(32,32);
    this->window->draw(score);

    
    tries_left.setFont(font);
    tries_left.setString("Tries left: "+std::to_string(this->tries_left));
    tries_left.setCharacterSize(20);
    if (this->tries_left == 1)
        tries_left.setFillColor(sf::Color::Red);
    tries_left.setFillColor(sf::Color::White);
    tries_left.setPosition(32,64);
    this->window->draw(tries_left);

    if (game_over) {
        sf::Text game_over_text;
        game_over_text.setFont(font);
        game_over_text.setString("Game over: click anywhere to restart");
        game_over_text.setCharacterSize(32); // in pixels, not points!
        game_over_text.setFillColor(sf::Color::White);
        
        sf::FloatRect textRect = game_over_text.getLocalBounds();
        game_over_text.setOrigin(textRect.left + textRect.width/2.0f,textRect.top+textRect.height/2.0f);
        game_over_text.setPosition(sf::Vector2f(this->window->getSize().x/2.0f,this->window->getSize().y/2.0f));
        this->window->draw(game_over_text);
    }
    
    this->window->display();
}

void Game::handleLeftClick ( int x, int y )
{
    if (game_over) {
        restart();
        return;
    }
    
    Sphere* explosion = new Sphere(1,1,this);
    explosion->explode();
    explosion->setPosition(x,y);
    this->add_object(explosion);
    this->score_multiplier = 1;
    this->tries_left -= 1;
    
    if (this->tries_left == 0)
        this->game_over = true;
}

void Game::add_score(int points)
{
    this->score += points*this->score_multiplier;
    this->score_multiplier *= 1.01;
}

Game::~Game()
{
    for (auto i=this->objects.begin();i!=this->objects.end();i++) {
        delete *i;
    }
}




