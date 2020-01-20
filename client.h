#ifndef client_h
#define client_h

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>
#include <string>
#include "player.h"
#include <vector>
#include "laser.h"
#include "meteor.h"

class Client
{
    public:
        Client();
        ~Client();
        void run();
    private:
        unsigned int screen_width;
        unsigned int screen_height;

        enum State { CONNECTING, MENU_1, MENU_2, NEW_ROOM_CONNECT, GAME, ROOM_LIST };
                    // connecting = łączenie z serwerem ekran z miejscem na id hasło i ip serwera
                    // menu_1 = pierwsze menu startowe z opcjami połącz z serwerem wyjdź
                    // menu_2 = drugie menu już po połaczeniu z opcjami tworzenia pokoju dołączania do pokoju modyfikacji statku wyjścia
                    //
                    //
        State state;

        sf::Sprite menu_bckground_sprite;
        sf::Texture menu_backgroundTex;
        sf::Sprite menu_bckground_sprite2;
        sf::Texture menu_backgroundTex2;
        sf::Sprite backgroundSprite;
        sf::Texture backgroundTex;
        float backgroundPos = 0;
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
        sf::Text text_4;
        std::string textInput = "Enter server IP:\n";
        std::string nameInput = "Enter your name:\n";
        int inputFocus = 1;
        sf::Text title;

        void menu_1();
        void menu_2();
        void connecting();
        void game();
        void room_list();

        void communication();
        sf::Thread communicationThread;
        bool communicationThreadActive = false;

        sf::RenderWindow window;
        sf::UdpSocket socket;
        sf::SocketSelector selector;
        unsigned short clientPort = 55000;
        unsigned short serverPort = 54000;
        sf::IpAddress serverAdress;
        bool first_player;  // jeżeli client działa jako gracz pierwszy =true
                            // jeżeli działą jako drugi =false

        Player player1;
        Player player2;
        float speed = 12;

        sf::Texture blueBulletTex;
        sf::Texture greenBulletTex;
        std::vector<Laser> bullets;
        sf::Clock shootingClock;
        bool shootedInActualLoop = false;

        bool testRun = false;
        sf::Clock framerateClock;
        sf::Time framerateTime;

        sf::Clock clock;
        std::vector<int> freeRoom;
        std::vector<sf::Text> freeRoomList;

        std::string name;

        std::vector <Meteor> meteors;
        sf::Texture meteorTex1;
};

#endif