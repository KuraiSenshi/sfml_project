#ifndef client_h
#define client_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>

class Client
{
    public:
        Client();
        ~Client();
        void run();
    private:
        unsigned int screen_width;
        unsigned int screen_height;

        enum State { CONNECTING, MENU_1, MENU_2, NEW_ROOM_CONNECT, GAME };
                    // connecting = łączenie z serwerem ekran z miejscem na id hasło i ip serwera
                    // menu_1 = pierwsze menu startowe z opcjami połącz z serwerem wyjdź
                    // menu_2 = drugie menu już po połaczeniu z opcjami tworzenia pokoju dołączania do pokoju modyfikacji statku wyjścia
                    //
                    //
        State state;

        sf::Texture menu_background;
        sf::Texture gui_spritesheet;

        sf::Sprite button_1;
        sf::Sprite button_2;
        sf::Sprite button_3;
        sf::IntRect press_button;
        sf::IntRect button;
        sf::Font font;
        sf::Text text_1;
        sf::Text text_2;
        sf::Text text_3;
        std::string textInput = "Enter server IP:\n\n";

        void menu_1();
        void menu_2();
        void connecting();

        sf::RenderWindow window;
        sf::UdpSocket socket;
        unsigned short clientPort = 55000;
        unsigned short serverPort = 54000;
        sf::IpAddress serverAdress;
};

#endif