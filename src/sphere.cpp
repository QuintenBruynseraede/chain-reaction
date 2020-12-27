#include "sphere.hpp"
#include "game_object.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <cstdlib>
#include "game.hpp"


Sphere::Sphere(float radius, float growth,Game* game): 
    GameObject(game)
{
    this->radius = radius;
    this->growth = growth;
    this->MAX_RADIUS = 150;
}

Sphere::Sphere ( float radius, float growth, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration,Game* game): 
    GameObject(position,velocity,acceleration,game)
{
    this->radius = radius;
    this->growth = growth;
    this->MAX_RADIUS = 150;
}


void Sphere::draw(sf::RenderWindow* window)
{    
    sf::CircleShape shape(this->radius);
    shape.setPosition(sf::Vector2f(this->position.x-this->radius,this->position.y-this->radius));
    if (this->supersphere)
        shape.setFillColor(sf::Color(0,0,255,this->alpha));
    else
        shape.setFillColor(sf::Color(this->color_r,this->color_g,this->color_b,this->alpha));
    
    window->draw(shape);
}

void Sphere::timestep ( float seconds )
{
    if (rand() < 10000) {
        this->supersphere = true;
        this->MAX_RADIUS = 150;
    }
    
    if (!this->exploding) {
        GameObject::timestep(seconds);
    }
    
    this->radius = this->radius + seconds * growth;    

    // Bounce against edges of window
    if (this->getX() < this->min_position.x + this->radius)
        this->setVelocity(-this->getVelocity().x,this->getVelocity().y);
    
    if (this->getY() < this->min_position.y + this->radius)
        this->setVelocity(this->getVelocity().x,-this->getVelocity().y);
    
    if (this->getY() > this->max_position.y-this->radius)
        this->setVelocity(this->getVelocity().x,-this->getVelocity().y);
    
    if (this->getX() > this->max_position.x-this->radius)
        this->setVelocity(-this->getVelocity().x,this->getVelocity().y);
    
    if (this->exploding) {
        
        if (supersphere)
            this->alpha = this->alpha*(0.98);
        else
            this->alpha = this->alpha*(0.85);
        
        
        if (this->radius > Sphere::MAX_RADIUS || this->alpha <= 1) {
            this->remove();
        }
    }
}

float Sphere::getGrowth() const
{
    return this->growth;
}

float Sphere::getRadius() const 
{
    return this->radius;
}

void Sphere::printProperties() const
{
    std::cout << "Pos (" << this->getX() << "," << this->getY() << "), Velocity (" \
        << this->getVelocity().x << "," << this->getVelocity().y << "), Growth: " << this->getGrowth() << ", Radius: " << this->getRadius() << std::endl;
}


void Sphere::explode()
{
    if (this->isExploding())
        return;
    this->exploding = true;
    this->growth = supersphere? 50 : 200;
    this->game->add_score(10);
}

bool Sphere::isExploding()
{
    return this->exploding;
}

bool Sphere::isSuperSphere()
{
    return this->supersphere;
}

void Sphere::setColor(int red, int green, int blue)
{
    if (red >= 0 && red <= 255 && green >= 0 && green <= 255 && blue >= 0 && blue <= 255) {
        this->color_b = blue;
        this->color_g = green;
        this->color_r = red;
    }
}




