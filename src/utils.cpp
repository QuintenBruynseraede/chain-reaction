#include <cstdlib>
#include <cmath>

#include "utils.hpp"

float random_float() {
    return (float) rand()/RAND_MAX;
}

float dist ( sf::Vector2f pos1, sf::Vector2f pos2 )
{
    return sqrt((pos1.x-pos2.x)*(pos1.x-pos2.x)+(pos1.y-pos2.y)*(pos1.y-pos2.y));
}
