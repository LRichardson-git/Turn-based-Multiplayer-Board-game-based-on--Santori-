#include "Reciever.h"
#include <thread>
#include <iostream>


void Reciever::receive(sf::TcpSocket& CSocket, sf::TcpSocket& RSocket, sf::TcpSocket& BSocket, sf::TcpSocket& DSocket, unsigned short sPlayers ,unsigned short nPlayer)
{
	

	Recieved.clear();
	while (true) {

		//look if recieved data
		msg = RecieveData(CSocket);
		display = msg;
		if (display > 0) {
			std::cout << "received msg type:" << display << std::endl;

			switch (display) {
				//Data on which turn it is
				Recieved.clear();

				//case 1 is if the data is for a turn update
			case 1:
					// send to both clients that a turn has passed
				std::cout << "sending turn data" << std::endl;
				SendDataType(RSocket, turn);
				SendDataType(CSocket, turn);
					//if 4 players send them data as well
				if (sPlayers > 2) {
					SendDataType(BSocket,turn);
					SendDataType(DSocket,turn);
				}
				break;

				//case 2 is if position data is sent
			case 2:
				
				std::cout << "Recieved Pos data" << std::endl;
				Send.clear();
				//telling the client it is pos data
				SendDataType(RSocket, pos);
				if (sPlayers > 2) {
					SendDataType(DSocket, pos);
					SendDataType(BSocket, pos);
				}

				for (int i = 0; i < 3; i++) {
					int test = 200;
					//std::cout << "sending pos data" << std::endl;
					Recieved.clear();
					sf::Uint8 reck;
					reck = RecieveData(CSocket);
					test = reck;
					
					std::cout << "recieced pos data :" << test << std::endl;
					SendData(RSocket, reck);
					if (sPlayers > 2) {
						SendData(DSocket, reck);
						SendData(BSocket, reck);
					}

				}
				
				
				break;

			case 3:
				std::cout << "sending player ID" << std::endl;
				SendDataType(CSocket, playerID);

				//Clear packets
				SendData(CSocket, nPlayer);

				if (sPlayers > 2) {
					SendDataType(CSocket, fourPlayer);
					SendDataType(BSocket, fourPlayer);
					SendDataType(DSocket, fourPlayer);
					SendDataType(RSocket, fourPlayer);
				}

				//next player that connectes is one player higher
			
				std::cout << "Player:" <<nPlayer << "connected" <<std::endl;

				break;

			case 4:
				// recive that it is victory data
				std::cout << "A team has won the game is over";
				//tell other team they have lost
				SendDataType(RSocket, vic);
				if (sPlayers > 2)
					SendDataType(DSocket, vic);

				system("pause");
				//send to the other player that the first player has won
				break;

			case 5:
				std::cout << "received tile build data" << std::endl;
				SendDataType(RSocket, build);
				if (sPlayers > 2) {
					SendDataType(DSocket, build);
					SendDataType(BSocket, build);
				}

				for (int i = 0; i < 2; i++) {
					Recieved.clear();
					sending = RecieveData(CSocket);
					SendData(RSocket, sending);
					if (sPlayers > 2) {
						SendData(DSocket, sending);
						SendData(BSocket, sending);
					}

				}
		}
		

		}
	}
}




	

//}
