#include "client.h"

Client::Client()
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
    button_1.setOrigin(button_1.getLocalBounds().width/2, button_1.getLocalBounds().height/2);
    button_2.setOrigin(button_2.getLocalBounds().width/2, button_2.getLocalBounds().height/2);

    text_1.setFont(font);
    text_2.setFont(font);
    text_3.setFont(font);
    text_1.setString("Connect");
    text_2.setString("Exit");
    text_1.setOrigin(text_1.getLocalBounds().width/2, text_1.getLocalBounds().height/2);
    text_2.setOrigin(text_2.getLocalBounds().width/2, text_2.getLocalBounds().height/2);
    text_1.setFillColor(sf::Color::Black);
    text_2.setFillColor(sf::Color::Black);
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
        
        default:
            break;
        }
    }
}

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
            
        }
    }
    

    window.clear();
    window.draw(button_1);
    window.draw(text_1);
    window.draw(button_2);
    window.draw(text_2);
    window.display();
}
