#include <SFML/Graphics.hpp>
#include "entity.hpp"

#ifndef BUILDER_HPP
#define BUILDER_HPP

class builder : public entity {
public:
    builder(unsigned short x, unsigned short y, unsigned short player);
    ~builder();
    unsigned short player;
    void draw(sf::RenderWindow &window);
    void move(unsigned short i, unsigned short j);
    void TileChecker(int mX);
    unsigned short x;
    unsigned short y;
    unsigned short z = 0;
    bool canmove = true;
    bool canbuild = false;
private:
};

#endif
