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

    //selector.add(socket);

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
    text_4.setFont(font);
    text_1.setString("Connect");
    text_2.setString("Exit");
    text_1.setOrigin(text_1.getLocalBounds().width/2, text_1.getLocalBounds().height/2);
    text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);

    title.setFont(font);
    title.setString("Far Space");
    title.setCharacterSize(100);
    title.setOrigin(title.getLocalBounds().width/2, title.getLocalBounds().height/2);
    title.setFillColor(sf::Color::White);
    title.setOutlineThickness(5);

    player1.setTexture("assets/player1.png", "assets/jet.png");
    player2.setTexture("assets/player2.png", "assets/jet.png");

    if (!blueBulletTex.loadFromFile("assets/blueLaser.png"))
    {
        std::cout << "Error - wczytanie grafiki niebieskiego lasera nie powiodlo sie" << std::endl;
    }

    if (!greenBulletTex.loadFromFile("assets/greenLaser.png"))
    {
        std::cout << "Error - wczytanie grafiki zielonego lasera nie powiodlo sie" << std::endl;
    }

    if (!backgroundTex.loadFromFile("assets/darkPurple.png"))
    {
        std::cout << "Error - wczytanie grafiki tla gry nie powiodlo sie" << std::endl;
    }
    backgroundTex.setRepeated(true);
    backgroundSprite.setTexture(backgroundTex);
    backgroundSprite.setTextureRect(sf::IntRect(0,0,4096,2160));

    if (!menu_backgroundTex.loadFromFile("assets/menu_background.png"))
    {
        std::cout << "Error - wczytanie grafiki tla menu nie powiodlo sie" << std::endl;
    }
    menu_bckground_sprite.setTexture(menu_backgroundTex);

    if (!menu_backgroundTex2.loadFromFile("assets/menu_background2.png"))
    {
        std::cout << "Error - wczytanie grafiki tla menu nie powiodlo sie" << std::endl;
    }
    menu_bckground_sprite2.setTexture(menu_backgroundTex2);

    if (!meteorTex1.loadFromFile("assets/Meteor1.png"))
    {
        std::cout << "Error - wczytanie grafiki meteor1 nie powiodlo sie" << std::endl;
    }
}

Client::~Client()
{

}

void Client::run()
{
    window.create(sf::VideoMode(screen_width, screen_height), "FarSpace client");
    window.setFramerateLimit(60);
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
    title.setPosition(window.getSize().x/2, window.getSize().y*0.20);

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
                // wciśnięcie przycisku connect
                state = CONNECTING;
                text_2.setString("Back");
                text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
                text_3.setString(textInput);
                text_3.setCharacterSize(50);
                text_3.setOrigin(text_3.getLocalBounds().width/2, text_3.getLocalBounds().height/2);
                text_4.setString(nameInput);
                text_4.setCharacterSize(50);
                text_4.setOrigin(text_4.getGlobalBounds().width/2, text_4.getGlobalBounds().height/2);
            }
            
            else if (button_2.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku exit
                window.close();
            }
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::T && event.key.shift)
            {
                std::cout << "T was pressed" << std::endl;
                std::cout << "shift:" << event.key.shift << std::endl;
                state = GAME;
                testRun = true;
            }
            
        }
        
    }
    
    backgroundSprite.setPosition((-mouse.x+window.getSize().x/2)/5 - 1000,(-mouse.y+window.getSize().y/2)/5 - 1000);
    menu_bckground_sprite.setPosition((-mouse.x+window.getSize().x/2)/15,(-mouse.y+window.getSize().y/2)/15);
    menu_bckground_sprite2.setPosition((-mouse.x+window.getSize().x/2)/10,(-mouse.y+window.getSize().y/2)/10);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(menu_bckground_sprite2);
    window.draw(menu_bckground_sprite);
    window.draw(title);
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
    text_3.setPosition(window.getSize().x/2, window.getSize().y*0.15);
    text_4.setPosition(window.getSize().x/2, window.getSize().y*0.35);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);
    text_3.setFillColor(sf::Color::White);
    text_4.setFillColor(sf::Color::White);
    text_3.setOutlineThickness(2);
    text_4.setOutlineThickness(2);

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
                serverAdress = sf::IpAddress(textInput.substr(17));
                if (nameInput.size() > 18)
                {
                    name = nameInput.substr(17);
                }
                else
                {
                    name = "noname";
                }
                
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
                    text_3.setCharacterSize(30);
                    text_3.setOrigin(text_3.getLocalBounds().width/2, text_3.getLocalBounds().height/2);
                    text_3.setOutlineThickness(0);
                    selector.add(socket);
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
            if (event.key.code == sf::Keyboard::Up)
            {
                if (inputFocus == 2)
                {
                    inputFocus = 1;
                }
                
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                if (inputFocus == 1)
                {
                    inputFocus = 2;
                }
                
            }
            
            if (event.key.code == sf::Keyboard::BackSpace)
            {
                if (inputFocus == 1 && textInput.size() > 17 )
                {
                    textInput.pop_back();
                    text_3.setString(textInput);
                }
                else if (inputFocus == 2 && nameInput.size() > 17)
                {
                    nameInput.pop_back();
                    text_4.setString(nameInput);
                }
                
            }  
            break;

        case sf::Event::TextEntered:
            if (event.text.unicode > 31 && event.text.unicode < 128)
            {
                if (inputFocus == 1 && textInput.size() < 32)
                {
                    textInput += event.text.unicode;
                    text_3.setString(textInput);
                }
                else if (inputFocus == 2 && nameInput.size() < 32)
                {
                    nameInput += event.text.unicode;
                    text_4.setString(nameInput);
                }
                
            }
            break;

        default:
            break;
        }
       
    }

    if (inputFocus == 1 && state == CONNECTING)
    {
        if (clock.getElapsedTime().asMilliseconds() < 500)
        {
            text_3.setString(textInput + "|");
        }
        else if (clock.getElapsedTime().asMilliseconds() < 1000)
        {
            text_3.setString(textInput);
        }
        else
        {
            clock.restart();
        }
        text_4.setString(nameInput);
    }
    else if (state == CONNECTING)
    {
        if (clock.getElapsedTime().asMilliseconds() < 500)
        {
            text_4.setString(nameInput + "|");
        }
        else if (clock.getElapsedTime().asMilliseconds() < 1000)
        {
            text_4.setString(nameInput);
        }
        else
        {
            clock.restart();
        }
        text_3.setString(textInput);
    }
    
    

    backgroundSprite.setPosition((-mouse.x+window.getSize().x/2)/5 - 1000,(-mouse.y+window.getSize().y/2)/5 - 1000);
    menu_bckground_sprite.setPosition((-mouse.x+window.getSize().x/2)/15,(-mouse.y+window.getSize().y/2)/15);
    menu_bckground_sprite2.setPosition((-mouse.x+window.getSize().x/2)/10,(-mouse.y+window.getSize().y/2)/10);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(menu_bckground_sprite2);
    window.draw(menu_bckground_sprite);
    window.draw(button_1);
    window.draw(text_1);
    window.draw(button_2);
    window.draw(text_2);
    window.draw(text_3);
    window.draw(text_4);
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

                // wysłanie do serwera nazwy pierwszego gracza
                std::string wiadomosc = name;
                packet.clear();
                packet << wiadomosc;
                if (socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
                {
                    std::cout << "wysłano: " << wiadomosc << std::endl;
                }
                packet.clear();
                //TODO: czekanie na drugiego gracza                                         //
                int wiadomosc2;                                                             //
                if (socket.receive(packet, serverAdress, serverPort) == sf::Socket::Done)   //
                {                                                                           //
                    packet >> wiadomosc2;                                                   //
                    std::cout << "odebrano: " << wiadomosc2 << std::endl;                   //
                }                                                                           //  przenieść do osobnej metody
                if (wiadomosc2 == 321)                                                      //
                {                                                                           //
                    state = GAME;                                                           //
                }                                                                           //
                

            }
            
            else if (button_2.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku join the game
                first_player = false;
                text_2.setString("Back");
                text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
                state = ROOM_LIST;
            }

            else if (button_3.getGlobalBounds().contains(mouse))
            {
                // wciśnięcie przycisku exit
                window.close();
            }
            
        }
    }
    
    backgroundSprite.setPosition((-mouse.x+window.getSize().x/2)/5 - 1000,(-mouse.y+window.getSize().y/2)/5 - 1000);
    menu_bckground_sprite.setPosition((-mouse.x+window.getSize().x/2)/15,(-mouse.y+window.getSize().y/2)/15);
    menu_bckground_sprite2.setPosition((-mouse.x+window.getSize().x/2)/10,(-mouse.y+window.getSize().y/2)/10);

    window.clear();
    window.draw(backgroundSprite);
    window.draw(menu_bckground_sprite2);
    window.draw(menu_bckground_sprite);
    window.draw(title);
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
            player1.moveUp(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus())
        {
            player1.moveDown(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && window.hasFocus())
        {
            player1.moveLeft(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
        {
            player1.moveRight(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window.hasFocus())
        {
            if (shootingClock.getElapsedTime().asMilliseconds() > player1.getShootDelay())
            {
                bullets.push_back(Laser(player1.getPosition(), 0, blueBulletTex));
                shootingClock.restart();
                shootedInActualLoop = true;
            }
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
            player2.moveUp(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && window.hasFocus())
        {
            player2.moveDown(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && window.hasFocus())
        {
            player2.moveLeft(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && window.hasFocus())
        {
            player2.moveRight(speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window.hasFocus())
        {
            if (shootingClock.getElapsedTime().asMilliseconds() > player2.getShootDelay())
            {
                bullets.push_back(Laser(player2.getPosition(), 0, greenBulletTex));
                shootingClock.restart();
                shootedInActualLoop = true;
            }
        }
    }

    if (!communicationThreadActive && testRun == false)
    {
        communicationThread.launch();
    }
    
    //std::cout << "x:" << player1.getPosition().x << " y:" << player1.getPosition().y << std::endl;

    if (!bullets.empty())   // updatowanie laserow i usuwanie gdy poza ekranem
    {
        for (size_t i = 0; i < bullets.size(); i++)
        {
            if(!bullets[i].update())    // jeżeli pocisk jest poza ekranem updete zwraca false
            {
                bullets.erase(bullets.begin()+i);
            }
        }
        
    }

    if (!meteors.empty()) // updatowanie meteorow i usuwanie gdy poza ekranem
    {
        for (size_t i = 0; i < meteors.size(); i++)
        {
            if (!meteors[i].update()) // jeżeli meteor jest daleko poza ekranem update zwraca false
            {
                meteors.erase(meteors.begin()+i);
            }
        }
    }

    // kolizje===================================================
    for (size_t i = 0; i < meteors.size(); i++)
    {
        sf::Vector2f meteorPos = meteors[i].getPosition();
        for (size_t j = 0; j < bullets.size(); j++)
        {
            sf::Vector2f bulletPos = bullets[j].getPosition();
            if (!meteors[i].isDestroyed() && !bullets[j].isDestroyed() && pow(bulletPos.x - meteorPos.x, 2) + pow(bulletPos.y - meteorPos.y, 2) <= 1600)
            {
                bullets[j].destroy();
                std::cout << "Kolizja" << std::endl;
            }
        }
    }
    
    if (backgroundPos <= -2048)
    {
        backgroundPos = 0;
    }
    else
    {
        backgroundPos -= 3;
    }
    backgroundSprite.setPosition(backgroundPos, 0.f);

    //framerateTime = framerateClock.getElapsedTime();
    //std::cout << 1.f/framerateTime.asSeconds() << std::endl;
    //framerateClock.restart();

    window.clear();
    window.draw(backgroundSprite);
    if (!meteors.empty())
    {
        for (size_t i = 0; i < meteors.size(); i++)
        {
            window.draw(meteors[i]);
        }
        
    }
    if(!bullets.empty())
    {
        for(int i=0; i<bullets.size(); i++)
        {
            window.draw(bullets[i]);
        }
    }
    window.draw(player1);
    window.draw(player2);
    window.display();
}

void Client::room_list()
{
    sf::Vector2f mouse = sf::Vector2f(sf::Mouse::getPosition(window));

    button_2.setTextureRect(button);
    button_2.setPosition(window.getSize().x/2, window.getSize().y*0.70);
    text_2.setPosition(window.getSize().x/2, window.getSize().y*0.69);
    text_2.setFillColor(sf::Color::Black);

    if (button_2.getGlobalBounds().contains(mouse))
    {
        text_2.setFillColor(sf::Color::White);
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && button_2.getGlobalBounds().contains(mouse))
    {
        button_2.setTextureRect(press_button);
        float button_move = button_2.getLocalBounds().height * 0.20;
        button_2.setPosition(button_2.getPosition().x, button_2.getPosition().y + button_move );
        text_2.setPosition(text_2.getPosition().x, text_2.getPosition().y + button_move);
    }


    if (clock.getElapsedTime().asSeconds() > 2)
    {
        sf::Packet packet;
        int order = 4;
        packet << order;
        if (socket.send(packet, serverAdress, serverPort) != sf::Socket::Done)
        {
            std::cout << "Error nie wyslano order=4" << std::endl;
        }
        packet.clear();
        if (socket.receive(packet, serverAdress, serverPort) != sf::Socket::Done)
        {
            std::cout << "Error nie odebrano listy pokoi" << std::endl;
        }
        
        int size;
        freeRoom.clear();
        freeRoomList.clear();
        packet >> size;
        std::cout << "Ilosc pokoi: " << size << std::endl;
        for (size_t i = 0; i < size; i++)
        {
            int x;
            std::string string;
            packet >> x >> string;
            freeRoom.push_back(x);
            sf::Text text;
            text.setFont(font);
            text.setFillColor(sf::Color::White);
            string = std::to_string(x) + ". " + string;
            text.setString(string);
            text.setOutlineThickness(3);
            text.setOutlineColor(sf::Color::Black);
            text.setOrigin(text.getLocalBounds().width/2, text.getLocalBounds().height/2);
            freeRoomList.push_back(text);
        }
        
        clock.restart();

        if (size == 0)
        {
            std::cout << "Brak wolnych pokoi" << std::endl;
        }
    }
    
    for (size_t i = 0; i < freeRoomList.size(); i++)
    {
        if (freeRoomList[i].getGlobalBounds().contains(mouse))
        {
            freeRoomList[i].setFillColor(sf::Color::Black);
            freeRoomList[i].setOutlineColor(sf::Color::White);
        }
        else
        {
            freeRoomList[i].setFillColor(sf::Color::White);
            freeRoomList[i].setOutlineColor(sf::Color::Black);
        }
        
    }
    
    if (freeRoomList.size() == 0)
    {
        freeRoomList.push_back(sf::Text("No free rooms available", font));
        freeRoomList[0].setOrigin(freeRoomList[0].getLocalBounds().width/2, freeRoomList[0].getLocalBounds().height/2);
        freeRoomList[0].setPosition(window.getSize().x/2, window.getSize().y*0.10);
    }
    else
    {
        // ułożenie tekstów pokoi maksymalnie dziesięciu
        if (freeRoomList.size() < 10)
        {
            for (size_t i = 0; i < freeRoomList.size(); i++)
            {
                freeRoomList[i].setPosition(window.getSize().x/2, window.getSize().y*0.01*(i*5+10));
            }
        }
        else
        {
            for (size_t i = 0; i < 10; i++)
            {
                freeRoomList[i].setPosition(window.getSize().x/2, window.getSize().y*0.01*(i*5+10));
            }
        }
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
            if (freeRoomList.size() < 10)
            {
                for (size_t i = 0; i < freeRoomList.size(); i++)
                {
                    if (freeRoomList[i].getGlobalBounds().contains(mouse))
                    {
                        sf::Packet packet;
                        int pokoj = freeRoom[i];
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
                }
            }
            else
            {
                for (size_t i = 0; i < 10; i++)
                {
                    if (freeRoomList[i].getGlobalBounds().contains(mouse))
                    {
                        sf::Packet packet;
                        int pokoj = freeRoom[i];
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
                }
            }

            if (button_2.getGlobalBounds().contains(mouse))
            {
                text_2.setString("Join the game");
                text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
                state = MENU_2;
            }
            
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

    backgroundSprite.setPosition((-mouse.x+window.getSize().x/2)/5 - 1000,(-mouse.y+window.getSize().y/2)/5 - 1000);
    menu_bckground_sprite.setPosition((-mouse.x+window.getSize().x/2)/15,(-mouse.y+window.getSize().y/2)/15);
    menu_bckground_sprite2.setPosition((-mouse.x+window.getSize().x/2)/10,(-mouse.y+window.getSize().y/2)/10);


    //drawing
    window.clear();
    window.draw(backgroundSprite);
    window.draw(menu_bckground_sprite2);
    window.draw(menu_bckground_sprite);
    window.draw(button_2);
    window.draw(text_2);

    if (freeRoomList.size() < 10)
    {
        for (size_t i = 0; i < freeRoomList.size(); i++)
        {
            window.draw(freeRoomList[i]);
        }
    }
    else
    {
        for (size_t i = 0; i < 10; i++)
        {
            window.draw(freeRoomList[i]);
        }
    }
    
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
        packet << p1x << p1y << shootedInActualLoop;
        shootedInActualLoop = false;
        if(socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
        {
            //std::cout << "wyslano x:" << player1.getPosition().x << " y:" << player1.getPosition().y << std::endl;
        }
        packet.clear();
        if (selector.wait(sf::seconds(1.f)))
        {
            if (socket.receive(packet, serverAdress, serverPort) == sf::Socket::Done)
            {
                //odebranie odpowiedzi serwera z danymi obiektów
                sf::Vector2f pos;
                bool player2Shooted;
                int meteorsNumber;
                std::vector<sf::Vector2f> meteorsPos;
                std::vector<bool> meteorsDestroyed;
                
                packet >> pos.x >> pos.y >> player2Shooted >> meteorsNumber;
                if (meteorsNumber > 0)
                {
                    for (size_t i = 0; i < meteorsNumber; i++)
                    {
                        float posx;
                        float posy;
                        bool destroyed;
                        packet >> posx >> posy >> destroyed;
                        meteorsPos.push_back(sf::Vector2f(posx, posy));
                        meteorsDestroyed.push_back(destroyed);
                    }
                }
                
                
                if (player2Shooted) // spawn pocisku
                {
                    bullets.push_back(Laser(player2.getPosition(), 0, greenBulletTex));
                }
                
                if (meteorsPos.size() > meteors.size())   // spawn meteoru
                {
                    int count = meteorsPos.size() - meteors.size();
                    for (size_t i = 0; i < count; i++)
                    {
                        meteors.push_back(Meteor(meteorsPos[meteorsPos.size() - count + i], meteorTex1));
                    }
                }

                for (size_t i = 0; i < meteorsPos.size(); i++)
                {
                    meteors[i].setPosition(meteorsPos[i]);
                    if (meteorsDestroyed[i])
                    {
                        meteors[i].destroy();
                    }
                    
                }
                
                
                player2.setPosition(pos);
            }
        }
        
    }
    else
    {
        sf::Packet packet;
        float p2x = player2.getPosition().x;
        float p2y = player2.getPosition().y;
        packet << p2x << p2y << shootedInActualLoop;
        shootedInActualLoop = false;
        if(socket.send(packet, serverAdress, serverPort) == sf::Socket::Done)
        {
            //std::cout << "wyslano x:" << player2.getPosition().x << " y:" << player2.getPosition().y << std::endl;
        }

        if (selector.wait(sf::seconds(1.f)))
        {
            if (socket.receive(packet, serverAdress, serverPort) == sf::Socket::Done)
            {
                //odebranie odpowiedzi serwera z danymi obiektów
                sf::Vector2f pos;
                bool player1Shooted;
                packet >> pos.x >> pos.y >> player1Shooted;
                if (player1Shooted) // spawn pocisku
                {
                    bullets.push_back(Laser(player1.getPosition(), 0, blueBulletTex));
                }
                
                player1.setPosition(pos);
            }
        }
    }
    
    communicationThreadActive = false;
}