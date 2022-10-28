#pragma once

#include "messenger.h"
#include "builder.hpp"
#include <vector>
#include <iostream>
#include <string>
#include "NetworkManager.h"

class messenger : public NetworkManager
{


public:
	void receive_data(sf::TcpSocket& tcpSocket);

    void place();

    messenger();
    ~messenger();

	//duplicate data recieved from server
    std::vector<builder> builders;
    unsigned short mturn = 0;
    unsigned short mPlayerID = 0;
    unsigned short mbuilderID = 0;
    unsigned short mPosX = 0;
    unsigned short mPosY = 0;
    unsigned short mteam = 0;

    bool mbuild = false;
    bool player4 = false;
    bool lost = false;
    bool won = true;
  

 

	//when someone builds sentthat here two
};

