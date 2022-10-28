#include <SFML/Graphics.hpp>
#include "world.hpp"

#ifndef GAME_HPP
#define GAME_HPP

enum class gamestate {
    place,
    play,
    victory,
    defeat,
    terminate
};

class game {
    private:
        sf::RenderWindow window;
        world *w;
        void place();
        void play(sf::TcpSocket& tcpSocket);
        void victory();
        void defeat();
    public:
        gamestate state = gamestate::play;
        game();
        ~game();
        void run(sf::TcpSocket &tcpSocket);
        bool update = true;
        
};
#endif
