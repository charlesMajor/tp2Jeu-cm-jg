#include "stdafx.h"
#include "TitleScene.h"
#include "game.h"
#include "TitleContentManager.h"
#include "SceneResult.h"
#include <iostream>

TitleScene::TitleScene()
    : Scene(SceneType::TITLE_SCENE)
{
}

TitleScene::~TitleScene()
{
}

SceneType TitleScene::update()
{
    SceneType retval = getSceneType();

    if (this->shouldStartGame)
    {
        this->shouldStartGame = false;
        retval = SceneType::GAME_SCENE;
    }

    return retval;
}

void TitleScene::pause()
{
    this->titleMusic.stop();
}

void TitleScene::unPause()
{
    this->titleMusic.play();
}

void TitleScene::draw(sf::RenderWindow& window) const
{
    window.draw(background);
    window.draw(logo);
    window.draw(startGameText);
}

bool TitleScene::uninit()
{
    return true;
}

bool TitleScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }

    background.setTexture(contentManager.getBackground());

    logo.setTexture(contentManager.getLogo());
    logo.setPosition(165, 150);

    startGameText.setString("Press any key to start");
    startGameText.setFont(contentManager.getFont());
    startGameText.setCharacterSize(30);
    startGameText.setOutlineColor(sf::Color::White);
    startGameText.setPosition(190, 500);

    if (!titleMusic.openFromFile("Assets\\Sounds\\menuMusic.ogg"))
    {
        return false;
    }
    titleMusic.setLoop(true);
    titleMusic.play();

    return true;
}

bool TitleScene::handleEvents(sf::RenderWindow& window)
{
    bool retval = false;
    sf::Event event;
    while (window.pollEvent(event))
    {
        //x sur la fenêtre
        if (event.type == sf::Event::Closed)
        {
            window.close();
            retval = true;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left || event.mouseButton.button == sf::Mouse::Right)
            {
                this->result.titleSceneResult.isInvincible = true;
                this->shouldStartGame = true;
            }            
        }
        if (event.type == sf::Event::KeyPressed)
        {
            this->result.titleSceneResult.isInvincible = false;
            this->shouldStartGame = true;
        }
    }

    return retval;
}