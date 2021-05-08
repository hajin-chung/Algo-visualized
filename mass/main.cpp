#include <SFML/Graphics.hpp>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "massive bodies!"

#define PLANET_N 2
#define PLANET_R 10

void main_loop();
void init();
void update(sf::Time elapsed);
void render();
float normalized_random(float start, float end);
float dist(sf::Vector2f p1, sf::Vector2f p2);

sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), WINDOW_TITLE);

typedef struct {
    float mass;
    int pinned;
    sf::Vector2f s;
    sf::Vector2f v;
    sf::Vector2f a;
} Planet;

Planet planets[PLANET_N];
Planet tmp_planets[PLANET_N];

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
    srand(time(NULL));
    for(int i=0 ; i<PLANET_N ; i++)
    {
        planets[i].mass = 100000;
        planets[i].s.x = normalized_random(0, SCREEN_WIDTH);
        planets[i].s.y = normalized_random(0, SCREEN_HEIGHT);
        planets[i].v = {0, 0};
        planets[i].a = {0, 0};
        planets[i].pinned = 0;
    }
    // planets[PLANET_N-1].s = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    // planets[PLANET_N-1].mass = 700000;
    // planets[PLANET_N-1].pinned = 1;

    memcpy(&tmp_planets, &planets, sizeof(Planet) * PLANET_N);
}

void update(sf::Time elapsed)
{
    // update
    //
    // 1) get sum of force from other planets
    // 2) update a (=F/m)
    // 3) update v (=a*t)
    // 4) update s (=v*t)
    // 5) commit update (tmp -> planets)

    sf::Vector2f f;
    float angle;
    float tf;
    float dt = elapsed.asSeconds();
    float ds;

    for(int i=0 ; i<PLANET_N ; i++)
    {
        f = {0, 0};
        for(int j=0 ; j<PLANET_N ; j++)
            if(i!=j)
            {
                ds = dist(planets[i].s, planets[j].s);
                if(ds > 10)
                {
                    tf = planets[i].mass * planets[j].mass / (ds * ds); 
                    f.y += tf * (planets[j].s.y - planets[i].s.y) / ds;
                    f.x += tf * (planets[j].s.x - planets[i].s.x) / ds;
                }
            }

        if(planets[i].pinned)
            continue;
        tmp_planets[i].mass = planets[i].mass;
        tmp_planets[i].pinned = planets[i].pinned;
        tmp_planets[i].a = f / planets[i].mass;
        tmp_planets[i].v = planets[i].v + tmp_planets[i].a * dt;
        tmp_planets[i].s = planets[i].s + tmp_planets[i].v * dt;
    }

    for(int i=0 ; i<PLANET_N ; i++) memcpy(&planets[i], &tmp_planets[i], sizeof(Planet));
}

void render()
{
    // render

    window.clear();

    for(int i=0 ; i<PLANET_N ; i++)
    {
        sf::CircleShape circle(PLANET_R);
        circle.setPosition(planets[i].s.x, planets[i].s.y);
        circle.setFillColor(sf::Color(0, 255, 0));
        window.draw(circle);
    }

    window.display();
}

float normalized_random(float start, float end)
{
    return (float)rand() / RAND_MAX * (end - start) + start;
}

float dist(sf::Vector2f p1, sf::Vector2f p2)
{
    return (float)sqrt(powf(p1.y - p2.y, 2) + powf(p1.x - p2.x, 2));
}

