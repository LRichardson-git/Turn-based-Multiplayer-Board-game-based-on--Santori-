#include "messenger.h"

void messenger::receive_data(sf::TcpSocket& tcpSocket)
{
	Recieved.clear();
	while (true) {

		msg = RecieveData(tcpSocket);
		//if recived data determine what type of data it is
		display = msg;
		if (display > 0) {
			//std::cout << "received msg type:" << display << std::endl;

			switch (display) {
				Recieved.clear();
			case 1:
				//make it next turn
				
				mturn++;
				
				if (mturn > 1 && player4 == false)
					mturn = 0;

				else if (mturn > 3 && player4 == true)
					mturn = 0;

				std::cout << "turn:" << mturn << std::endl;
				if (mturn == mPlayerID)
					std::cout << "it is your turn" << std::endl;
				break;

				//case 2 is if position data is sent
			case 2:

				std::cout << "Recieving position data" << std::endl;
				//recieveing pos data
				for (int i = 0; i < 3; i++) {
					Recieved.clear();

					msg = RecieveData(tcpSocket);
					Rec = msg;

					if (i == 0)
						mbuilderID = Rec;

					if (i == 1)
						mPosX = Rec;

					if (i == 2)
						mPosY = Rec;

					
					

					std::cout << "pos Data recived" << std::endl;

				}
				builders[mbuilderID].x = mPosX;
				builders[mbuilderID].y = mPosY;

				std::cout << "server built at x:" << mPosX << std::endl;
				std::cout << "server built at y:" << mPosY << std::endl;
				
				std::cout << "position data received";
				break;
			case 3:
				// gives out playerID
				msg = RecieveData(tcpSocket);
				Rec = msg;
				mPlayerID = Rec;
				std::cout << std::endl;
				std::cout << "player ID:" << mPlayerID << std::endl;
				std::cout << "player ID Determines the turn order"  << std::endl;

				if (mPlayerID == 1 || mPlayerID == 3) {
					mteam = 1;
					std::cout << "your team 1 which is the blue team" << std::endl;
				}
				else
					std::cout << "your team 0 which is the Red team" << std::endl;
				break;

			case 4:
				std::cout << "You have lost" << std::endl;
				system("pause");
				system("exit");
				break;
			case 5:
				Recieved.clear();

				for (int i = 0; i < 2; i++) {
					Recieved.clear();
					msg = RecieveData(tcpSocket);
					Rec = msg;

					if (i == 0) {
						mPosX = Rec;
						std::cout << "updated build x" << std::endl;
					}
					if (i == 1) {
						mPosY = Rec;
						std::cout << "updated build y" << std::endl;
					}

				}

				mbuild = true;

				break;
			case 6:
				StartGame = true;
				std::cout << "starting the game" << std::endl;
				break;
			case 7:
				player4 = true;
				break;
			
				
				

			}
		}
	}
	}


void messenger::place() {

    builders.push_back(builder(1, 1, 0));
    builders.push_back(builder(3, 3, 0));
    builders.push_back(builder(3, 1, 1));
    builders.push_back(builder(1, 3, 1));
}

messenger::messenger()
{
}

messenger::~messenger()
{
}
