#include "server_game.h"

ServerGame::ServerGame(unsigned short port1)
    //: roomThread(&ServerGame::game, this)
{
    port = port1;
    //if(socket.bind(port1) != sf::Socket::Done)
    //{
        // obsługa błędu połączenia
    //}

    // this->roomThread.launch();
}

ServerGame::~ServerGame()
{}

unsigned short ServerGame::getPort()
{
    return port;
}

void ServerGame::game()
{

}