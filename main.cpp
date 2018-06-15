#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GameObject.hpp"
#include "Player.hpp"
#include <iostream>

int main()
{
    int SCREEN_WIDTH = 800;
    int SCREEN_HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Test");
    b2Vec2 gravity(0.f, 9.8f);
    b2World world(gravity, false);

    sf::Texture groundTexture;
    sf::Texture playertexture;
    groundTexture.loadFromFile("/home/grzegorz/Projects/template/template_project/ground.png");
    playertexture.loadFromFile("/home/grzegorz/Projects/template/template_project/human.png");

    GameObjects gameObjects;
    GameObject ground(world, SCREEN_WIDTH / 2, SCREEN_HEIGHT + groundTexture.getSize().y / 2 - 20, groundTexture, 1, b2_staticBody);
    gameObjects.add(ground);

    std::shared_ptr<Player>  player = std::make_shared<Player>(world, 200, 100, playertexture);
    gameObjects.add(player);

    while (window.isOpen())
    {
        window.clear(sf::Color::White);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player->moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player->moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (player->graphicBody.getPosition().y + player->graphicBody.getTextureRect().height * 0.05  + 1> ground.graphicBody.getPosition().y - ground.graphicBody.getTextureRect().height / 2)
            {
                player->jump();
//                std::cout << "collide" << std::endl;
            }
        }
//        std::cout << "Player Bottom: " <<player->graphicBody.getPosition().y + player->graphicBody.getTextureRect().height *0.05 <<std::endl;
//         std::cout << "Bottom: " <<ground.graphicBody.getPosition().y - ground.graphicBody.getTextureRect().height / 2 <<std::endl;


        gameObjects.update();
        gameObjects.draw(window);
        window.display();

        world.Step(1/60.f, 8, 3);

    }
    return 0;
}
