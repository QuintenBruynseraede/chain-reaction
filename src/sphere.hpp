#ifndef SPHERE_HPP_INCLUDED
#define SPHERE_HPP_INCLUDED

#include "game_object.hpp"

class Sphere : public GameObject {
public:
    Sphere(float radius, float growth);
    Sphere(float radius, float growth, sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f acceleration);
    virtual ~Sphere() {};
    virtual void draw(sf::RenderWindow* window);
    virtual void timestep(float seconds);
    
    float getRadius() const;
    float getGrowth() const;
    
    static const float MAX_RADIUS;
    
    void explode();
    bool isExploding();

private:
    float radius;
    float growth;
    void printProperties() const;
    float alpha = 255;
    bool exploding = false;
};

#endif // SPHERE_HPP_INCLUDED
