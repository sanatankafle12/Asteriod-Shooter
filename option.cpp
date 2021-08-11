#include "option.h"
#include "menu.h"

Menu menu1(1080,720);

Option::Option() :window(VideoMode(1080, 720), "Option")
{
    if(!font.loadFromFile("arial.ttf"))
    {
        //handle error
    }
    text.setFont(font);
    text.setFillColor(sf::Color::Green);
    text.setString("Hit Enter or BackSpace to return to Menu");
    text.setPosition(sf::Vector2f(100,600));


}

Option::~Option()
{
}

void Option::display()
{


	while (window.isOpen())
	{

        sf::Texture texture;
        texture.loadFromFile("optionbackground.png");
        sf::Sprite sprite;
        sprite.setTexture(texture);

		sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::KeyReleased:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::BackSpace:
                            window.close();
                            menu1.run();
                            break;
                        case sf::Keyboard::Return:
                            window.close();
                            menu1.run();
                            break;
                    }
                    break;
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear();
        window.draw(sprite);
        window.draw(text);
        window.display();
	}
}
