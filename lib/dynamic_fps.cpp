#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "SFML works!"

void main_loop();
void init();
void update(sf::Time elapsed);
void render();

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);

int main() 
{
    main_loop();
    return 0;
}

void main_loop()
{
    sf::Clock clock;

    init();
    while (window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        render();
        update(elapsed);
    }
}

void init()
{
    // init
}

void update(sf::Time elapsed)
{
    // update
}

void render()
{
    // render
}

