#include "server_game.h"

ServerGame::ServerGame(unsigned short port1)
    : gameThread(&ServerGame::game, this), communicationThread(&ServerGame::communication, this)
{
    port = port1;
    if(socket.bind(port) != sf::Socket::Done)
    {
         // obsługa błędu połączenia
    }

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

}

void ServerGame::communication()
{

}

int ServerGame::getPlayersNumber()
{
    return playersNumber;
}