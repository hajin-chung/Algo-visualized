#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define BLOCK_N 60
#define FPS 20

void sorting();
void init();
void update(sf::Time elapsed);
void render();

int arr[BLOCK_N], updated[BLOCK_N];
int block_width = SCREEN_WIDTH / BLOCK_N;
int main_idx;
float time_sum;

int auto_replay = 0;

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");

int main() 
{
    sorting();
    return 0;
}

void sorting()
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
    int i;
    srand(time(NULL));

    for(i=0 ; i<BLOCK_N ; i++) arr[i] = rand() % 30 + 1;
    main_idx = 0;
    time_sum = 0;
}

void update(sf::Time elapsed)
{
    int i, tmp;

    time_sum += elapsed.asSeconds();
    if(time_sum < (float) 1 / FPS) return;
    else time_sum = 0;

    if(main_idx < BLOCK_N) 
    {
        memset(updated, 0, sizeof(int)*BLOCK_N);

        for(i=main_idx ; i<BLOCK_N ; i++)
        {
            if(arr[i] < arr[main_idx])
            {
                tmp = arr[i];
                arr[i] = arr[main_idx];
                arr[main_idx] = tmp;
                updated[i] = 1;
            }
        }
    }
    main_idx++;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || (main_idx >= BLOCK_N*2 && auto_replay))
        init();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        window.close();
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        auto_replay = 1 - auto_replay;
}

void render()
{
    int i;
    window.clear(sf::Color(0, 0, 0));
    for(i=0 ; i<BLOCK_N ; i++)
    {
        sf::RectangleShape rectangle(sf::Vector2f(block_width, arr[i]*10));
        rectangle.setPosition((float)i*block_width, SCREEN_HEIGHT - arr[i]*10);
        if(updated[i] || (main_idx >= BLOCK_N && i < main_idx - BLOCK_N)) 
            rectangle.setFillColor(sf::Color(0, 255, 0));
        else
            rectangle.setFillColor(sf::Color(255, 255, 255));

        rectangle.setOutlineThickness(1.f);
        rectangle.setOutlineColor(sf::Color(100, 100, 100));
        window.draw(rectangle);
    }
    window.display();
}

