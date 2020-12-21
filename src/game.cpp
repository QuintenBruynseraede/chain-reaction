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
    this->objects = std::vector<GameObject*>();
    this->fps = 60;
    
    for (int i=0;i<250;i++) {
        Sphere* x = new Sphere(5,0);
        x->setMaxPosition(sf::Vector2f(this->window->getSize().x,this->window->getSize().y));
        x->setPosition(sf::Vector2f(30+random_float()*(x->getMaxPosition().x-30),30+random_float()*(x->getMaxPosition().y-30)));
        x->setVelocity(sf::Vector2f(-100+random_float()*200,-100+random_float()*200));

        this->add_object(x);
    }
}

void Game::add_object(GameObject* object)
{
    if (std::count(this->objects.begin(),this->objects.end(),object)) {
        // GameObject already exists
        return;
    }
    this->objects.push_back(object);
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
                if (dist((*ex).getPosition(),x->getPosition()) < 50) {
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
    
    this->window->display();
}

void Game::handleLeftClick ( int x, int y )
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile("assets/sounds/tick.wav");
    
    Sphere* explosion = new Sphere(1,1);
    explosion->explode();
    explosion->setPosition(x,y);
    this->add_object(explosion);
}




