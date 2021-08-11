#include <iostream>
#include "menu.h"
#include "Game.h"
#include "option.h"


Menu::Menu(float width, float height)
{
    

    if(!font.loadFromFile("Debrosee-ALPnL.ttf"))
    {
        //handle error
    }
    menu[0].setFont(font);
    menu[0].setFillColor(sf::Color::Green);
    menu[0].setString("Play");
    menu[0].setPosition(sf::Vector2f(width/4,(height+50)/(MAX_NUMBER_OF_ITEMS+1)*1));


    menu[1].setFont(font);
    menu[1].setFillColor(sf::Color::White);

    menu[1].setString("HELP");
    menu[1].setPosition(sf::Vector2f(width/4,(height+50)/(MAX_NUMBER_OF_ITEMS+1)*2));

    menu[2].setFont(font);
    menu[2].setFillColor(sf::Color::White);
    menu[2].setString("Exit");
    menu[2].setPosition(sf::Vector2f(width/4,(height+50)/(MAX_NUMBER_OF_ITEMS+1)*3));    

    selectedItemIndex = 0;
}

Menu::~Menu()
{

}

void Menu::draw(sf::RenderWindow &window)
{
    for(int i=0;i<MAX_NUMBER_OF_ITEMS;i++)
    {
        window.draw(menu[i]);    
    }
}

void Menu::MoveUp()
{
    if(selectedItemIndex-1>=0)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex --;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::MoveDown()
{
    if(selectedItemIndex+1<MAX_NUMBER_OF_ITEMS)
    {
        menu[selectedItemIndex].setFillColor(sf::Color::White);
        selectedItemIndex ++;
        menu[selectedItemIndex].setFillColor(sf::Color::Green);
    }
}

void Menu::run()
{
    sf::RenderWindow window(sf::VideoMode(1080,720),"Menu");
    Menu menu(1080,720);

    sf::Texture texture;
    texture.loadFromFile("background1.png");
    sf::Sprite sprite;
    sprite.setTexture(texture);

    while(window.isOpen())
    {
        sf::Event event;
        
        
   
        while (window.pollEvent(event))
        {
            
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Up:
                            menu.MoveUp();
                            break;
                        case sf:: Keyboard::Down:
                            menu.MoveDown();
                            break;
                        case sf::Keyboard::Return:
                            switch (menu.GetPressedItem())
                            {
                            case 0:
                            {
                                Game game;
                                window.close();
                                game.run();
                                break;
                            }
                            case 1:
                            {
                                Option option;
                                window.close();
                                option.display();
                                break;
                            }
                            case 2:
                                window.close();
                                break;
                            }
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        window.clear();
        window.draw(sprite);
        menu.draw(window);
        window.display();
    }
}