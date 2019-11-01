#ifndef client_h
#define client_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class Client
{
    public:
        Client();
        ~Client();
        void run();
    private:
        enum state { CONNECTING, MENU_1, MENU_2, NEW_ROOM_CONNECT, GAME };
                    // connecting = łączenie z serwerem ekran z miejscem na id hasło i ip serwera
                    // menu_1 = pierwsze menu startowe z opcjami połącz z serwerem wyjdź twórcy
                    // menu_2 = drugie menu już po połaczeniu z opcjami tworzenia pokoju dołączania do pokoju modyfikacji statku
                    //
                    //
        void update();
        void draw();

        sf::RenderWindow window;
        sf::UdpSocket socket;
        unsigned short clientPort;
        unsigned short serverPort;
};

#endif