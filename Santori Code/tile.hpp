#include <iostream>
#include <SFML/Graphics.hpp>
#include "entity.hpp"

#ifndef TILE_HPP
#define TILE_HPP

class tile : public entity {
public:
    tile();
    void draw(sf::RenderWindow &w);
    bool build();
    unsigned short x;
    unsigned short y;
    unsigned short level = 0;
private:
};

#endif
