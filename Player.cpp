#include "Player.hpp"

Player::Player(b2World& world, float x, float y, sf::Texture& texture)
    : GameObject(world, x, y, texture, 0.1, b2_dynamicBody)
{

}

