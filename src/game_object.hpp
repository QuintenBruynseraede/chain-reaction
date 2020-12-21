#ifndef GAME_OBJECT_HPP_INCLUDED
#define GAME_OBJECT_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class GameObject {
public:
    GameObject(float x, float y): position(sf::Vector2f(x,y)),velocity(sf::Vector2f(0,0)),acceleration(sf::Vector2f(0,0)) {};
    GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration);
    GameObject(float x_position, float y_position, float x_velocity, float y_velocity, float x_acceleration, float y_acceleration);
    GameObject();
    
    virtual ~GameObject();
    
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    
    float getX() const;
    float getY() const;
    
    void setPosition(sf::Vector2f pos);
    void setVelocity(sf::Vector2f velocity);
    void setAcceleration(sf::Vector2f acceleration);
    
    void setPosition(float pos_x, float pos_y);
    void setVelocity(float velocity_x, float velocity_y);
    void setAcceleration(float acceleration_x, float acceleration_y);
   
    void setMaxPosition(sf::Vector2f max){ this->max_position = sf::Vector2f(max); }
    void setMinPosition(sf::Vector2f min){ this->min_position = sf::Vector2f(min); }
    
    sf::Vector2f getMaxPosition() const;
    sf::Vector2f getMinPosition() const;
    
    virtual void timestep(float seconds);
    
    virtual void draw(sf::RenderWindow* window)=0;
    
    void remove();
    bool isRemoved();

    
protected:
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    
    sf::Vector2f max_position;
    sf::Vector2f min_position;
private:
    bool isActive=true;
};

#endif // GAME_OBJECT_HPP_INCLUDED