#include<SFML/Graphics.hpp>
#pragma once
using namespace sf;

class Option
{
public:
	Option();
	~Option();
	void display();

private:
    RenderWindow window;
	Font font;
    Text text;
};
