#include <SFML/Graphics.hpp>
#include "game_object.hpp"

#include <iostream>

GameObject::GameObject()
{
    this->setAcceleration(sf::Vector2f(0,0));
    this->setPosition(sf::Vector2f(0,0));
    this->setVelocity(sf::Vector2f(0,0));
}

GameObject::GameObject(float x_position, float y_position, float x_velocity, float y_velocity, float x_acceleration, float y_acceleration)
{
    this->setAcceleration(sf::Vector2f(x_acceleration,y_acceleration));
    this->setPosition(sf::Vector2f(x_position,y_position));
    this->setVelocity(sf::Vector2f(x_velocity,y_velocity));
}

GameObject::GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration)
{
    this->setAcceleration(sf::Vector2f(acceleration));
    this->setPosition(sf::Vector2f(position));
    this->setVelocity(sf::Vector2f(velocity));
}

sf::Vector2f GameObject::getAcceleration() const
{
    return sf::Vector2f(this->acceleration);
}

sf::Vector2f GameObject::getPosition() const
{
    return sf::Vector2f(this->position);
}

sf::Vector2f GameObject::getVelocity() const
{
    return sf::Vector2f(this->velocity);
}

void GameObject::setAcceleration ( sf::Vector2f acceleration )
{
    this->acceleration = sf::Vector2f(acceleration);
}

void GameObject::setVelocity ( sf::Vector2f velocity )
{
    this->velocity = sf::Vector2f(velocity);
}

void GameObject::setPosition ( sf::Vector2f position )
{
    this->position = sf::Vector2f(position);
}

void GameObject::setAcceleration ( float acceleration_x, float acceleration_y )
{
    this->setAcceleration(sf::Vector2f(acceleration_x,acceleration_y));
}

void GameObject::setPosition ( float pos_x, float pos_y )
{
    this->setPosition(sf::Vector2f(pos_x,pos_y));
}

void GameObject::setVelocity ( float velocity_x, float velocity_y )
{
    this->setVelocity(sf::Vector2f(velocity_x,velocity_y));
}

void GameObject::timestep ( float seconds )
{
    this->setVelocity(this->getVelocity()+this->getAcceleration()*seconds);
    this->setPosition(this->getPosition()+this->getVelocity()*seconds);
}

GameObject::~GameObject() {}

float GameObject::getX() const
{
    return this->getPosition().x;
}

float GameObject::getY() const
{
    return this->getPosition().y;
}

sf::Vector2f GameObject::getMaxPosition() const
{
    return sf::Vector2f(this->max_position);
}

sf::Vector2f GameObject::getMinPosition() const
{
    return sf::Vector2f(this->min_position);
}

bool GameObject::isRemoved()
{
    return !this->isActive;
}

void GameObject::remove()
{
    this->isActive = false;
}












