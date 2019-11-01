#include "client.h"

Client::Client()
{
    clientPort = 55000;
    serverPort = 54000;
    if(socket.bind(clientPort) != sf::Socket::Done)
    {
        // obsługa błędu
    }
}

Client::~Client()
{

}

void Client::run()
{
    window.create(sf::VideoMode(1920, 1080), "FarSpace client");
    while(window.isOpen())
    {
        input();
        update();
        draw();
    }
}

void Client::input()
{

}

void Client::update()
{

}

void Client::draw()
{

}