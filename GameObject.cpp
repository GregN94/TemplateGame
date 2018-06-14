#include "GameObject.hpp"

GameObject::GameObject(b2World& world, float x, float y, sf::Texture& texture, float scale, b2BodyType type)
{
    graphicBody.setTexture(texture);
    graphicBody.setOrigin(graphicBody.getTextureRect().width / 2, graphicBody.getTextureRect().height / 2);
    graphicBody.setPosition(x, y);
    graphicBody.setScale(scale, scale);
    b2BodyDef body;
    body.position = b2Vec2(x / SCALE, y / SCALE);
    body.type = type;
    physicalBody = world.CreateBody(&body);
    Shape.SetAsBox(graphicBody.getTextureRect().width  * scale / (2 * SCALE), graphicBody.getTextureRect().height * scale / (2 * SCALE));
    b2FixtureDef FixtureDef;
    FixtureDef.density = 1.f;
    FixtureDef.friction = 0.7f;
    FixtureDef.shape = &Shape;
    physicalBody->CreateFixture(&FixtureDef);

    graphicBody.setRotation(physicalBody->GetAngle() * 180/b2_pi);
}

void GameObject::update()
{
    graphicBody.setPosition(physicalBody->GetPosition().x * SCALE, physicalBody->GetPosition().y * SCALE);
    graphicBody.setRotation(180/b2_pi * physicalBody->GetAngle());
}

sf::Sprite GameObject::getBody()
{
    return graphicBody;
}

void GameObjects::update()
{
    for (auto object : objectList) {
        object->update();
    }
}

void GameObjects::draw(sf::RenderWindow& window)
{
    for (auto object : objectList) {
        window.draw(object->getBody());
    }
}

void GameObjects::add(GameObject newGameObject)
{
    objectList.push_back(std::make_shared<GameObject>(newGameObject));
}
