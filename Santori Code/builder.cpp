#include "builder.hpp"
#include <iostream>

builder::builder(unsigned short x_, unsigned short y_, unsigned short p_):
    x(x_),
    y(y_),
    player(p_)
{
}

builder::~builder()
{
   
}

void builder::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(40, 40);
    sf::Color fColor = sf::Color(0xd0, 0x70, 0x70, 0xff);
    if (player == 1) {
        fColor = sf::Color(0x70, 0x70, 0xd0, 0xff);
    }
    circle.setFillColor(fColor);
    circle.setPosition(x * 120 + 20, y * 120 + 20);
    window.draw(circle);
}

void builder::move(unsigned short i, unsigned short j)
{
    x += i;
    y += j;
}

void builder::TileChecker(int mX) {
     

}
