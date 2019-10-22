#include "server_game.h"

serverGame::serverGame(unsigned short port)
{
    if(socket.bind(port) != sf::Socket::Done)
    {
        // obsługa błędu połączenia
    }
}

serverGame::~serverGame()
{}