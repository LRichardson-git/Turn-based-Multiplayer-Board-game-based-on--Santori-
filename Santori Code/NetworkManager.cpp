#include "NetworkManager.h"

NetworkManager::NetworkManager()
{

}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::SendDataType(sf::TcpSocket& Socket, sf::Uint8 type) {

	//std::cout << "sending dataType" << std::endl;
	Send.clear();

	if (Send << type)
		if (Socket.send(Send) != sf::Socket::Done)
			std::cout << "not able to send data" << std::endl;
		else
			std::cout << "dataType sent" << std::endl;
}

void NetworkManager::SendData(sf::TcpSocket& Socket, sf::Uint8 data) {

	//std::cout << "sending data" << std::endl;
	Send.clear();
	if (Send << data)
		std::cout << "data packed";

	if (Socket.send(Send) != sf::Socket::Done)
		std::cout << "not able to send data" << std::endl;
	else
		std::cout << "data sent" << std::endl;

}

sf::Uint8 NetworkManager::RecieveData(sf::TcpSocket& Socket) {
	
	bool NoData = true;
	//int lol;

	
	Recieved.clear();
	if (Socket.receive(Recieved) != sf::Socket::Done) {
		std::cout << "player Discconected or error recieving data" << std::endl;
		system("pause");
		return nothing;
	}

	else {
		std::cout << "data recieved" << std::endl;
		
		if (Recieved >> sendback ) {
			//lol = sendback;
			//std::cout << "got" << lol << std::endl;
			NoData = false;
			return sendback;
		}
		else
			std::cout << "could not pack data recieved" << std::endl;
	}
	

}
