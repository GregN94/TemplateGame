#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject.hpp"
#include "Player.hpp"

int main()
{
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Test");
    b2Vec2 Gravity(0.f, 9.8f);
    b2World World(Gravity, false);

    sf::Texture GroundTexture;
    sf::Texture BoxTexture;
    GroundTexture.loadFromFile("/home/grzegorz/Projects/template/template_project/ground.png");
    BoxTexture.loadFromFile("/home/grzegorz/Projects/template/template_project/human.png");

    GameObjects gameObjects;
    GameObject ground(World, SCREEN_WIDTH / 2, SCREEN_HEIGHT + GroundTexture.getSize().y / 2 - 20, GroundTexture, 1, b2_staticBody);
    gameObjects.add(ground);

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            int MouseX = sf::Mouse::getPosition(window).x;
            int MouseY = sf::Mouse::getPosition(window).y;
            gameObjects.add(Player(World, MouseX, MouseY, BoxTexture));
        }
        gameObjects.update();
        gameObjects.draw(window);
        window.display();

        World.Step(1/60.f, 8, 3);

    }
    return 0;
}
