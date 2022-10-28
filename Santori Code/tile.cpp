#include "tile.hpp"

tile::tile():
    x(0),
    y(0),
    level(0)
{
}

void tile::draw(sf::RenderWindow &w)
{
    sf::RectangleShape rectangle;
    rectangle.setOutlineThickness(5);
    sf::Color cOutline;
    sf::Color cFill;
    cOutline = sf::Color(0xf2, 0xf0, 0xe6, 0xff);
    cFill = sf::Color(0xdf, 0xd8, 0xbf, 0xff);

    if (level == 0) {
        cFill = sf::Color(0x76, 0x9D, 0x66, 0xff);
        rectangle.setSize(sf::Vector2f(110, 110));
        rectangle.setPosition(x*120+5, y*120+5);
        rectangle.setFillColor(cFill);
        w.draw(rectangle);
    }
    else {
        int limit = (level<4)?level:3;
        for (int i = 0; i < limit; i++) {
            int s = 110 - (i * 20);
            rectangle.setSize(sf::Vector2f(s, s));
            rectangle.setPosition((x*120)+(i*10)+5, (y*120)+(i*10)+5);
            rectangle.setOutlineColor(cOutline);
            rectangle.setFillColor(cFill);
            w.draw(rectangle);
        }
    }
    if (level == 4) {
        sf::CircleShape circle(40);
        circle.setPosition(x*120+20, y*120+20);
        circle.setFillColor(sf::Color(0x00, 0x00, 0xaf, 0xff));
        w.draw(circle);
    }
}

bool tile::build()
{
    std::cout << "Build: " << x << " " << y << " " << level << std::endl;
    if (level < 4) {
        level++;
        return true;
    }
    return false;
}
