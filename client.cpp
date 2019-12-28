#include "client.h"
#include <iostream>
#include "player.h"

Client::Client()
    :communicationThread(&Client::communication, this)
{
    if(socket.bind(clientPort) != sf::Socket::Done)
    {
        // obsługa błędu
    }

    screen_height = 1080;
    screen_width = 1920;

    state = MENU_1;
    /*if (!menu_background.loadFromFile("menu_background.png"))
    {
        // obsługa błędu
    }*/
    if (!gui_spritesheet.loadFromFile("assets/blueSheet.png"))
    {
        // obsługa błędu
    }
    if (!font.loadFromFile("assets/kenvector_future.ttf"))
    {
        // obsługa błędu
    }
    
    window.setFramerateLimit(60);

    //gui_spritesheet.setSmooth(true);
    button = sf::IntRect(0, 94, 190, 49);
    press_button = sf::IntRect(190, 49, 190, 45);
    button_1.setTexture(gui_spritesheet);
    button_1.setTextureRect(button);
    button_2.setTexture(gui_spritesheet);
    button_2.setTextureRect(button);
    button_3.setTexture(gui_spritesheet);
    button_3.setTextureRect(button);
    button_1.setOrigin(button_1.getLocalBounds().width/2, button_1.getLocalBounds().height/2);
    button_2.setOrigin(button_2.getLocalBounds().width/2, button_2.getLocalBounds().height/2);
    button_3.setOrigin(button_3.getLocalBounds().width/2, button_3.getLocalBounds().height/2);

    text_1.setFont(font);
    text_2.setFont(font);
    text_3.setFont(font);
    text_1.setString("Connect");
    text_2.setString("Exit");
    text_1.setOrigin(text_1.getLocalBounds().width/2, text_1.getLocalBounds().height/2);
    text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);

    player1.setTexture("assets/player1.png");
    player2.setTexture("assets/player2.png");
}

Client::~Client()
{

}

void Client::run()
{
    window.create(sf::VideoMode(screen_width, screen_height), "FarSpace client");
    while(window.isOpen())
    {
        switch (state)
        {
        case MENU_1:
            menu_1();
            break;
        
        case CONNECTING:
            connecting();
            break;

        case MENU_2:
            menu_2();
            break;

        case GAME:
            game();
            break;

        case ROOM_LIST:
            room_list();
            break;

        default:
            break;
        }
    }
}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Client::menu_1()
{
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));

    button_1.setTextureRect(button);
    button_2.setTextureRect(button);
    button_1.setPosition(window.getSize().x/2, window.getSize().y*0.50);
    button_2.setPosition(window.getSize().x/2, window.getSize().y*0.70);
    button_1.setScale(1.5, 1.5);
    text_1.setPosition(window.getSize().x/2, window.getSize().y*0.49);
    text_2.setPosition(window.getSize().x/2, window.getSize().y*0.69);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);

    if (button_1.getGlobalBounds().contains(mouse))
    {
        text_1.setFillColor(sf::Color::White);
    }
    if (button_2.getGlobalBounds().contains(mouse))
    {
        text_2.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_1.getGlobalBounds().contains(mouse))
    {
        button_1.setTextureRect(press_button);
        float button_move = button_1.getLocalBounds().height * 0.20;
        button_1.setPosition(button_1.getPosition().x, button_1.getPosition().y + button_move );
        text_1.setPosition(text_1.getPosition().x, text_1.getPosition().y + button_move);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_2.getGlobalBounds().contains(mouse))
    {
        button_2.setTextureRect(press_button);
        float button_move = button_2.getLocalBounds().height * 0.20;
        button_2.setPosition(button_2.getPosition().x, button_2.getPosition().y + button_move );
        text_2.setPosition(text_2.getPosition().x, text_2.getPosition().y + button_move);
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (button_1.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku connecting
                state = CONNECTING;
                text_2.setString("Back");
                text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
                text_3.setString(textInput);
                text_3.setOrigin(text_3.getLocalBounds().width/2, text_3.getLocalBounds().height/2);
            }
            
            else if (button_2.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku exit
                window.close();
            }
        }
    }
    

    window.clear();
    window.draw(button_1);
    window.draw(text_1);
    window.draw(button_2);
    window.draw(text_2);
    window.display();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Client::connecting()
{

    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));

    button_1.setTextureRect(button);
    button_2.setTextureRect(button);
    button_1.setPosition(window.getSize().x/2, window.getSize().y*0.60);
    button_2.setPosition(window.getSize().x/2, window.getSize().y*0.70);
    button_1.setScale(1.5, 1.5);
    text_1.setPosition(window.getSize().x/2, window.getSize().y*0.59);
    text_2.setPosition(window.getSize().x/2, window.getSize().y*0.69);
    text_3.setPosition(window.getSize().x/2, window.getSize().y*0.30);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);

    if (button_1.getGlobalBounds().contains(mouse))
    {
        text_1.setFillColor(sf::Color::White);
    }
    if (button_2.getGlobalBounds().contains(mouse))
    {
        text_2.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_1.getGlobalBounds().contains(mouse))
    {
        button_1.setTextureRect(press_button);
        float button_move = button_1.getLocalBounds().height * 0.20;
        button_1.setPosition(button_1.getPosition().x, button_1.getPosition().y + button_move );
        text_1.setPosition(text_1.getPosition().x, text_1.getPosition().y + button_move);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_2.getGlobalBounds().contains(mouse))
    {
        button_2.setTextureRect(press_button);
        float button_move = button_2.getLocalBounds().height * 0.20;
        button_2.setPosition(button_2.getPosition().x, button_2.getPosition().y + button_move );
        text_2.setPosition(text_2.getPosition().x, text_2.getPosition().y + button_move);
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        
        case sf::Event::MouseButtonReleased:
            if (button_1.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku connect
                serverAdress = sf::IpAddress(textInput);
                sf::Packet packet;
                int order = 5; // prośba o nowy numer portu clienta
                packet << order;
                if(socket.send(packet, serverAdress, serverPort) != sf::Socket::Done)
                {
                    std::cout << "Error nie wyslano order = 5" << std::endl;
                }
                packet.clear();
                if(socket.receive(packet, serverAdress, serverPort) != sf::Socket::Done)
                {
                    std::cout << "Error nie odebrano nowego numeru portu clienta" << std::endl;
                }
                packet >> clientPort;
                packet.clear();
                socket.unbind();
                if(socket.bind(clientPort) != sf::Socket::Done)
                {
                    std::cout << "Error blad bindowania nowego socketu" << std::endl;
                }
                else
                {
                    std::cout << "connecting succesfull new port = " << clientPort << std::endl;
                    state = MENU_2;
                    text_1.setString("Create new game");
                    text_1.setOrigin(text_1.getLocalBounds().width/2, text_1.getLocalBounds().height/2);
                    text_2.setString("Join the game");
                    text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
                    text_3.setString("Exit");
                    text_3.setOrigin(text_3.getLocalBounds().width/2, text_3.getLocalBounds().height/2);
                }
            }
            
            else if (button_2.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku back
                state = MENU_1;
                text_2.setString("Exit");
                text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
            }
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::BackSpace && textInput.size() > 18)
            {
                textInput.pop_back();
                text_3.setString(textInput);
            }  
            break;

        case sf::Event::TextEntered:
            if (event.text.unicode > 31 && event.text.unicode < 128 && textInput.size() < 33)
            {
                textInput += event.text.unicode;
                text_3.setString(textInput);
            }
            break;

        default:
            break;
        }
       
    }

    window.clear();
    window.draw(button_1);
    window.draw(text_1);
    window.draw(button_2);
    window.draw(text_2);
    window.draw(text_3);
    window.display();
}
///////////////////////////////////////////////////////////////////////////////////////////////
void Client::menu_2()
{
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));

    button_1.setTextureRect(button);
    button_2.setTextureRect(button);
    button_3.setTextureRect(button);
    button_1.setPosition(window.getSize().x/2, window.getSize().y*0.49);
    button_2.setPosition(window.getSize().x/2, window.getSize().y*0.60);
    button_3.setPosition(window.getSize().x/2, window.getSize().y*0.70);
    button_1.setScale(2.1, 1.5);
    button_2.setScale(1.5, 1.5);
    text_1.setPosition(window.getSize().x/2, window.getSize().y*0.48);
    text_2.setPosition(window.getSize().x/2, window.getSize().y*0.59);
    text_3.setPosition(window.getSize().x/2, window.getSize().y*0.69);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);
    text_3.setFillColor(sf::Color::Black);

    if (button_1.getGlobalBounds().contains(mouse))
    {
        text_1.setFillColor(sf::Color::White);
    }
    if (button_2.getGlobalBounds().contains(mouse))
    {
        text_2.setFillColor(sf::Color::White);
    }
    if (button_3.getGlobalBounds().contains(mouse))
    {
        text_3.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_1.getGlobalBounds().contains(mouse))
    {
        button_1.setTextureRect(press_button);
        float button_move = button_1.getLocalBounds().height * 0.20;
        button_1.setPosition(button_1.getPosition().x, button_1.getPosition().y + button_move );
        text_1.setPosition(text_1.getPosition().x, text_1.getPosition().y + button_move);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_2.getGlobalBounds().contains(mouse))
    {
        button_2.setTextureRect(press_button);
        float button_move = button_2.getLocalBounds().height * 0.20;
        button_2.setPosition(button_2.getPosition().x, button_2.getPosition().y + button_move );
        text_2.setPosition(text_2.getPosition().x, text_2.getPosition().y + button_move);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_3.getGlobalBounds().contains(mouse))
    {
        button_3.setTextureRect(press_button);
        float button_move = button_3.getLocalBounds().height * 0.20;
        button_3.setPosition(button_3.getPosition().x, button_3.getPosition().y + button_move );
        text_3.setPosition(text_3.getPosition().x, text_3.getPosition().y + button_move);
    }

    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonReleased)
        {
            if (button_1.getGlobalBounds().contains(mouse))
            {   // wciśnięcie przycisku create new game
                
                first_player = true;

                sf::Packet packet;
                int order = 1;
                packet << order;
                if ( socket.send(packet, serverAdress, serverPort) != sf::Socket::Done )
                {   // wysłanie prośby o nowy pokój
                    std::cout << "Wysłanie zapytania nie powiodlo sie" << std::endl;
                }   
                packet.clear();
                if ( socket.receive(packet, serverAdress, serverPort) != sf::Socket::Done )
                {   // odebranie numeru portu nowego pokoju
                    std::cout << "odebranie numeru portu pokoju nie powiodlo sie" << std::endl;
                }   
                packet >> serverPort;   // nowy port pokoju gry
                std::cout << "Port nowego pokoju: " << serverPort << std::endl;

                // test połączenia z pokojem gry
                int wiadomosc = 123;
                packet.clear();
                packet << wiadomosc;
                if (socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
                {
                    std::cout << "wysłano: " << wiadomosc << std::endl;
                }
                packet.clear();
                //TODO: czekanie na drugiego gracza
                if (socket.receive(packet, serverAdress, serverPort) == sf::Socket::Done)
                {
                    packet >> wiadomosc;
                    std::cout << "odebrano: " << wiadomosc << std::endl;
                }
                if (wiadomosc == 321)
                {
                    state = GAME;
                }
                

            }
            
            else if (button_2.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku join the game
                first_player = false;
                //TODO:
                //sf::Packet packet;
                //int order = 4;
                //packet << order;
                //if (socket.send(packet, serverAdress, serverPort) != sf::Socket::Done)
                //{
                //    std::cout << "Error nie wyslano order=4" << std::endl;
                //}
                //else
                //{
                    state = ROOM_LIST;
                //}
                
            }

            else if (button_3.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku exit
                window.close();
            }
            
        }
    }
    

    window.clear();
    window.draw(button_1);
    window.draw(text_1);
    window.draw(button_2);
    window.draw(text_2);
    window.draw(button_3);
    window.draw(text_3);
    window.display();
}

///////////////////////////////////////////////////////////////////////////////////

void Client::game()
{
    if (first_player)    // client pierwszego gracza
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && window.hasFocus())
        {
            player1.moveUp(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus())
        {
            player1.moveDown(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && window.hasFocus())
        {
            player1.moveLeft(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
        {
            player1.moveRight(0.5);
        }
        
    }
    else    //client drugiego gracza
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && window.hasFocus())
        {
            player2.moveUp(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus())
        {
            player2.moveDown(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && window.hasFocus())
        {
            player2.moveLeft(0.5);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
        {
            player2.moveRight(0.5);
        }
    }

    if (!communicationThreadActive)
    {
        communicationThread.launch();
    }
    
    //std::cout << "x:" << player1.getPosition().x << " y:" << player1.getPosition().y << std::endl;

    window.clear();
    window.draw(player1);
    window.draw(player2);
    window.display();
}

void Client::room_list()
{
    //TODO: gui wyboru pokoju
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;

        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
            {
                sf::Packet packet;
                int pokoj = 0;
                int order = 2;
                packet << order << pokoj;
                if (socket.send(packet, serverAdress, serverPort) != sf::Socket::Done)
                {
                    std::cout << "Error nie wyslano order=2" << std::endl;
                }
                packet.clear();
                if (socket.receive(packet, serverAdress, serverPort) != sf::Socket::Done)
                {
                    std::cout << "Error nie odebrano nr pokoju" << std::endl;
                }
                packet >> serverPort;
                std::cout << "otrzymano: " << std::endl;

                // test połączenia z pokojem gry
                int wiadomosc = 123;
                packet.clear();
                packet << wiadomosc;
                if (socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
                {
                    std::cout << "wysłano: " << wiadomosc << std::endl;
                }

                state = GAME;
            }
            
            break;

        default:
            break;
        }
    }

    

    window.clear();
    
    window.display();
}

void Client::communication()
{
    communicationThreadActive = true;
    if (first_player)
    {
        sf::Packet packet;
        float p1x = player1.getPosition().x;
        float p1y = player1.getPosition().y;
        packet << p1x << p1y;
        if(socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
        {
            std::cout << "wyslano x:" << player1.getPosition().x << " y:" << player1.getPosition().y << std::endl;
        }
    }
    else
    {
        sf::Packet packet;
        float p2x = player2.getPosition().x;
        float p2y = player2.getPosition().y;
        packet << p2x << p2y;
        if(socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
        {
            std::cout << "wyslano x:" << player2.getPosition().x << " y:" << player2.getPosition().y << std::endl;
        }
        else
        {
            std::cout << "error wyslanie wspolrzednych gracza2 nie powiodlo sie" << std::endl;
        }
        
    }
    
    communicationThreadActive = false;
}