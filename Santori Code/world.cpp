#include "world.hpp"
#include "game.hpp"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include "SFML/Network.hpp"
#include <thread>


world::world(sf::RenderWindow& w, game *g_):
    window(w)
{
    srand(time(0));
    window.setFramerateLimit(60);
    setup();
    

    
}

void world::setup()
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tiles[i][j].x = i;
            tiles[i][j].y = j;
            tiles[i][j].level = 0;
        }
    }
    place();
    turn = 0;
}

world::~world()
{
    delete tcSocket;
    delete g;
    
}

// Place the builders at the beginning of the game
void world::place()
{
    builders.push_back(builder(1, 1, 0));
    builders.push_back(builder(3, 3, 0));
    builders.push_back(builder(3, 1, 1));
    builders.push_back(builder(1, 3, 1));
}

void world::selectBuilder()
{
        //loops through builders to see if selected
    for (int i = 0; i < 4; i++) {
        if (builders[i].x == tilePos(mX) && builders[i].y == tilePos(mY) && builders[i].player == team) {
            builderID = i;
            std::cout << "builder :" << i << "selected" << std::endl;
            canmove = true;
        }
    
    }
}

bool world::tileOccupied() {
    //loop through and check tiles
    for (int i = 0; i < 4; i++) {
        if (builders[i].x == tilePos(mX) && builders[i].y == tilePos(mY)) {
            std::cout << "way is blocked" << std::endl;
            return true;
        }
    }

    //had to add this for some reason the second tile in the vector dosent seem to register in the loop
    if (builders[1].x == tilePos(mX) && builders[1].y == tilePos(mY)) {
        std::cout << "way is blocked" << std::endl;
        return true;
    }

    //check to see if can move to the tile depending on its build level
    if (SelBuilder == true and tiles[tilePos(mX)][tilePos(mY)].level != 4)  
        return false;
  
        
    //check if the tiles are too high for the player to go onto
    else {
        if (tiles[tilePos(mX)][tilePos(mY)].level == builders[builderID].z || tiles[tilePos(mX)][tilePos(mY)].level < builders[builderID].z)
            return false;

        else if (tiles[tilePos(mX)][tilePos(mY)].level == builders[builderID].z + 1 && tiles[tilePos(mX)][tilePos(mY)].level  != 4) {
            return false;
        }
        else {
            std::cout << "cant move there" << std::endl;
            return true;
            
        }
           
    }


}
void world::updaterecieve() {

     msger.place();
     
        while (true) {
            msger.receive_data(*tcSocket);
        }
        
}


void world::UpdatemouseLocation() {
    
        //update the mouse location based on its currecnt position relative to the window
    position = sf::Mouse::getPosition(window);
    mX = position.x;
    mY = position.y;
    //std::cout << "x :" << tilePos(mX) << std::endl;
    //std::cout << "y :" << tilePos(mY) << std::endl;
  
}


void world::update(sf::TcpSocket& tcpSocket)
{
    //Setup 
    if (k == 0) {
        tcSocket = &tcpSocket;

        std::thread d(&world::updaterecieve, this);
        d.detach();

        //Send data to get PlayerID from server
        
        msger.SendDataType(tcpSocket, msger.playerID);
        k++;
    }

    
        //Constantly check to see if anything has been sent from the Server
    if (PlayerID != msger.mPlayerID) {
        PlayerID = msger.mPlayerID;
        std::cout << "changed id to: "<< PlayerID << std::endl;
    }
       
    for (int i = 0; i < 4; i++) {
        builders[i].x = msger.builders[i].x;
        builders[i].y = msger.builders[i].y;
    }

    if (msger.mbuild == true) {
        tiles[msger.mPosX][msger.mPosY].build();
        msger.mbuild = false;
    }

    //std::cout << "turn:" << turn << std::endl;
    if (msger.mbuild == true) {
        tiles[msger.mPosX][msger.mPosY].build();
        msger.mbuild = false;
    }
 
    if (msger.mturn != turn)
        turn = msger.mturn;
   
    if (team != msger.mteam)
        team = msger.mteam;



    //check if anyone has won or lost
    for (int i = 0; i < 4; i++) {
        if (builders[i].z == 3) {
            std::cout << "Team :" << builders[i].player << "has won " << std::endl;
            
            if (builders[i].player == team) {
                std::cout << "you have won" << std::endl;
                msger.SendDataType(tcpSocket, msger.vic);
                system("pause");
                g->state = gamestate::terminate;
            }
                
            
        }
    }
    

        //check if mouse button pressed
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && turn == PlayerID) {
            //update the mouse location
        UpdatemouseLocation();
       
            //select a builder
        if (SelBuilder == false)
            selectBuilder();

            //check if builder is selected
        if (canmove == true) {
            
                //check if tile is occupied by a builder
            if (tilePos(mX) > builders[builderID].x + 1 || tilePos(mX) < builders[builderID].x - 1 || tilePos(mY) > builders[builderID].y + 1 || tilePos(mY) < builders[builderID].y - 1) {
                std::cout << "sorry you cant move there" << std::endl;
            }

                //move builder
            else if (tileOccupied() == false && SelBuilder == false){
                    //move builder
                builders[builderID].x = tilePos(mX);
                builders[builderID].y = tilePos(mY);
                std::cout << "moved x:" << tilePos(mX) << std::endl;
                std::cout << "moved y:" << tilePos(mY) << std::endl;
                builders[builderID].z = tiles[tilePos(mX)][tilePos(mY)].level;

                    //make it so cant move but can build
                builders[builderID].canbuild = true;
                builders[builderID].canmove = false;
                SelBuilder = true;
                
                    //send updated position to server
                updatePos(tcpSocket);

                    //this makes it so the player is locked onto this builder after moving it
                SelBuilder = true;
            }

            else if (builders[builderID].canbuild == true) {

                    //check if someone is there
                bool canbuild = true;
                for (int i = 0; i < 4; i++) {
                    if (builders[i].x == tilePos(mX) && builders[i].y == tilePos(mY) && tiles[tilePos(mX)][tilePos(mY)].level != 4)
                        canbuild = false;
                    }


                   //Build a tile 
                if (canbuild == true) {
                    tiles[tilePos(mX)][tilePos(mY)].build();
                    builders[builderID].canbuild = false;
                    builders[builderID].canmove = true;
                    SelBuilder = false;
                    canmove = false;
                    //send data to server
                    updateBuild(tcpSocket);
                }
                else
                    std::cout << "sorry cant build there" << std::endl;

            }
        }

    }


}

void world::draw()
{
    window.clear();
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tiles[i][j].draw(window);
        }
    }
    for (int i = 0; i < 4; i++) {
        builders[i].draw(window);
    }
}


int world::tilePos(unsigned short XY) {

    if(XY < 120)
        return 0;

    if(XY < 240)
        return 1;

    if(XY < 360)
        return 2;

    if(XY < 480)
        return 3;

    if (XY < 600)
        return 4;

    else
        return 5;
}




void world::updatePos(sf::TcpSocket& Socket) {
    //update builders on messenger side so it dosent undo itself
    msger.builders[builderID].x = tilePos(mX);
    msger.builders[builderID].y = tilePos(mY);

        //send data type about position
    msger.SendDataType(Socket, msger.pos);

        //send which builder has moved
    msger.sending = builderID;
    msger.SendData(Socket, msger.sending);
    
        //send builders x and y
    msger.sending = tilePos(mX);
    msger.SendData(Socket, msger.sending);

    msger.sending = tilePos(mY);
    msger.SendData(Socket, msger.sending);


}

void world::updateBuild(sf::TcpSocket& Socket) {
   
    msger.SendDataType(Socket, msger.build);
        //send X data
    msger.sending = tilePos(mX);
    msger.SendData(Socket, msger.sending);
        //send Y data
    msger.sending = tilePos(mY);
    msger.SendData(Socket, msger.sending);
        //next turn
    msger.SendDataType(Socket, msger.turn);


}