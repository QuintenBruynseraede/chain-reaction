#ifndef SPHERE_HPP_INCLUDED
#define SPHERE_HPP_INCLUDED

#include "game_object.hpp"

#include <SFML/Audio.hpp>

class Sphere : public GameObject {
public:
    Sphere(float radius, float growth,Game* game);
    Sphere(float radius, float growth, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration,Game* game);
    virtual ~Sphere() {};
    virtual void draw(sf::RenderWindow* window);
    virtual void timestep(float seconds);
    
    float getRadius() const;
    float getGrowth() const;
    
    
    void explode();
    bool isExploding();
    
    bool isSuperSphere();

private:
    float MAX_RADIUS;
    float radius;
    float growth;
    void printProperties() const;
    float alpha = 255;
    bool exploding = false;
    
    bool supersphere = false;
};

#endif // SPHERE_HPP_INCLUDED
