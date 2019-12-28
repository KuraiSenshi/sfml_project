#include "server_game.h"
#include <iostream>

ServerGame::ServerGame(unsigned short port1)
    : gameThread(&ServerGame::game, this), communicationThread(&ServerGame::communication, this)
{
    std::cout << "konstruktor nowego pokoju" << std::endl;
    port = port1;
    if(socket.bind(port) != sf::Socket::Done)
    {
         // obsługa błędu połączenia
    }
    selector.add(socket);

    communicationThread.launch();

}

ServerGame::~ServerGame()
{

}

unsigned short ServerGame::getPort()
{
    return port;
}

void ServerGame::game()
{
    //TODO: aktualizacja obiektów
    //TODO: kolizje obiektów
    if (!gameThreadActive)
    {
        std::cout << "Player1:: " << "x:" << player1Pos.x << " y:" << player1Pos.y << std::endl;
        std::cout << "Player2:: " << "x:" << player2Pos.x << " y:" << player2Pos.y << std::endl;
    }
    
}

void ServerGame::gameUpdate()
{
    gameThread.launch();
}

void ServerGame::communication()
{   
    sf::Packet packet;
    //potwierdzenie komunikacji z pierwszym graczem
    socket.receive(packet, player1Address, player1Port);
    int wiadomosc;
    packet >> wiadomosc;
    std::cout << "odebrano: " << wiadomosc << " od " << player1Port << " " << player1Address << std::endl;
    playersNumber = 1;

    //potwierdzenie komunikacji z drugim graczem 
    socket.receive(packet, player2Address, player2Port);
    packet >> wiadomosc;
    std::cout << "odebrano: " << wiadomosc << " od " << player2Port << " " << player2Address << std::endl;
    playersNumber = 2;

    //odesłanie info do do pierwszeo gracza że można zacząć  
    wiadomosc = 321;
    packet.clear();
    packet << wiadomosc;
    socket.send(packet, player1Address, player1Port);
    //socket.send(packet, player2Address, player2Port);
    

    while (true)
    {
        if (selector.wait(sf::seconds(5.f)))
        {
            //TODO: po otrzymaniu danych od clienta odsyła zestaw aktualnych danych z serwera
            if ( socket.receive(packet, playerAddress, playerPort) == sf::Socket::Done)
            {
                if (playerAddress == player1Address && playerPort == player1Port)
                {   // otrzymano dane od gracza nr1 
                    float p1x;
                    float p1y;
                    packet >> p1x >> p1y;
                    player1Pos.x = p1x;
                    player1Pos.y = p1y;
                }
                else if (playerAddress == player2Address && playerPort == player2Port)
                {   // otrzymano dane od gracza nr2
                    float p2x;
                    float p2y;
                    packet >> p2x >> p2y;
                    player2Pos.x = p2x;
                    player2Pos.y = p2y;
                }
            }
        }
        else
        {
            break;
        }
        
    }
}

int ServerGame::getPlayersNumber()
{
    return playersNumber;
}