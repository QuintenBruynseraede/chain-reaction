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
    
    void setColor(int red,int green, int blue);

private:
    float MAX_RADIUS;
    float radius;
    float growth;
    void printProperties() const;
    float alpha = 255;
    bool exploding = false;
    
    bool supersphere = false;
    
    int color_r = 255;
    int color_g = 255;
    int color_b = 255;
};

#endif // SPHERE_HPP_INCLUDED
