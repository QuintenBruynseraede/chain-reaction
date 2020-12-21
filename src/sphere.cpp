#include "sphere.hpp"
#include "game_object.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>


Sphere::Sphere(float radius, float growth): GameObject()
{
    this->radius = radius;
    this->growth = growth;
}

Sphere::Sphere(float radius, float growth, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration) : GameObject(position,velocity,acceleration)
{
    this->radius = radius;
    this->growth = growth;
}


void Sphere::draw(sf::RenderWindow* window)
{    
    sf::CircleShape shape(this->radius);
    shape.setPosition(this->position);
    shape.setFillColor(sf::Color(255,255,255,this->alpha));
    window->draw(shape);
}

void Sphere::timestep ( float seconds )
{
    if (!this->exploding) {
        GameObject::timestep(seconds);
    }
    
    this->radius = this->radius + seconds * growth;    

    // Bounce against edges of window
    if (this->getX() < this->min_position.x)
        this->setVelocity(-this->getVelocity().x,this->getVelocity().y);
    
    if (this->getY() < this->min_position.y)
        this->setVelocity(this->getVelocity().x,-this->getVelocity().y);
    
    if (this->getY() > this->max_position.y-this->radius*2)
        this->setVelocity(this->getVelocity().x,-this->getVelocity().y);
    
    if (this->getX() > this->max_position.x-this->radius*2)
        this->setVelocity(-this->getVelocity().x,this->getVelocity().y);
    
    if (this->exploding) {
        this->alpha = this->alpha*(0.85);
        if (this->radius > Sphere::MAX_RADIUS || this->alpha <= 1) {
            this->remove();
        }
    }
    
    // Explode randomly
    if (rand() < 40000) {
        this->explode();
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

const float Sphere::MAX_RADIUS = 150;

void Sphere::explode()
{
    if (this->isExploding())
        return;
    std::cout << "Exploding!" << std::endl;
    this->exploding = true;
    this->growth = 200;
}

bool Sphere::isExploding()
{
    return this->exploding;
}





