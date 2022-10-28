#include <SFML/Graphics.hpp>
#include <array>
#include "tile.hpp"
#include "builder.hpp"
#include <Windows.h>
#include "messenger.h"

#ifndef WORLD_HPP
#define WORLD_HPP

class game;

class world {
    public:
        world(sf::RenderWindow& w, game *g);
        ~world();
        void update(sf::TcpSocket& tcpSocket);
        void draw();
        int tilePos(unsigned short XY);
        void updatePos(sf::TcpSocket& Socket);
        void updateBuild(sf::TcpSocket& Socket);
        void setup();
        void updaterecieve();
    private:
        messenger msger;
        game *g;
        sf::RenderWindow& window;
        std::array<std::array<tile, 5>, 5> tiles{{{{tile(), tile(), tile()}}, {{tile(), tile(), tile()}}, {{tile(), tile(), tile()}}}} ;
        std::vector<builder> builders;
        sf::Vector2i position;
        sf::TcpSocket* tcSocket;


        //game data
        unsigned short mX, mY;
        unsigned short turn = 0;
        unsigned short PlayerID = 1;
        unsigned short builderID = 0;
        unsigned short k = 0;
        unsigned short team = 0;
        bool canmove = false;
        bool SelBuilder = false;
        
       
        
        void place();
        void selectBuilder();
        bool tileOccupied();
        void UpdatemouseLocation();
       
};
#endif
