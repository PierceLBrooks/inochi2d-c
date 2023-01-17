
#include "inochi2d.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/ContextSettings.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Clock.hpp>
#include <iostream>
#include <string>

sf::Clock* timer = nullptr;

double getTime()
{
    if (timer == nullptr) {
        timer = new sf::Clock();
        return 0.0;
    }
    return static_cast<double>(timer->restart().asSeconds());
}

int main(int argc, char** argv)
{
    float width = 1024.0f;
    float height = 1024.0f;
    std::string puppet = "";
    InPuppet* pup = nullptr;
    sf::Sprite* puppetSprite = nullptr;
    sf::RenderTexture* puppetTexture = nullptr;
    sf::RenderWindow* window = new sf::RenderWindow();
    window->create(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)), "Inochi2D");
    window->setFramerateLimit(60);
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window->close();
                break;
            }
        }
        if (!window->isOpen()) {
            break;
        }
        if (puppetTexture == nullptr) {
            if (argc > 1) {
                puppet += std::string(argv[1]);
                std::cout << puppet << std::endl;
                puppetTexture->create(window->getSize().x, window->getSize().y, sf::ContextSettings(0, 1));
                puppetTexture->setActive(true);
                inInit([](){return getTime();});
                inViewportSet(width, height);
                inViewportGet(&width, &height);
                std::cout << width << 'x' << height << std::endl;
                inCameraSetZoom(inCameraGetCurrent(), 0.5f);
                pup = inPuppetLoad(puppet.c_str());
                continue;
            }
        } else {
            inUpdate();
#ifdef INOCHI2D_GLYES
            inSceneBegin();
            if (pup != nullptr) {
                inPuppetUpdate(pup);
                inPuppetDraw(pup);
            }
            inSceneEnd();
            inSceneDraw(0, 0, width, height);
#endif
            if (puppetSprite == nullptr) {
                puppetSprite = new sf::Sprite(puppetTexture->getTexture());
                puppetSprite->setPosition(sf::Vector2f(window->getSize())*0.5f);
                puppetSprite->setOrigin(sf::Vector2f(puppetSprite->getTexture()->getSize())*0.5f);
            }
        }
        window->clear(sf::Color::Black);
        if (puppetSprite != nullptr) {
            puppetTexture->display();
            window->setActive(true);
            window->resetGLStates();
            window->draw(*puppetSprite);
        }
        window->display();
    }
    if (pup != nullptr) {
        //inDestroyPuppet(pup);
    }
    delete puppetSprite;
    delete puppetTexture;
    delete window;
    return 0;
}

