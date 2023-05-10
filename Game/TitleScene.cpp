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
    window.draw(startGameCheatText);
    window.draw(escapeText);
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

    logo.setPosition(Game::WORLD_WIDTH / 2 - logo.getLocalBounds().width / 2, 150);

    startGameText.setString("Press any key to start");
    startGameText.setFont(contentManager.getFont());
    startGameText.setCharacterSize(30);
    startGameText.setOutlineColor(sf::Color::White);
    startGameText.setPosition(Game::WORLD_WIDTH / 2 - startGameText.getLocalBounds().width / 2, 500);

    startGameCheatText.setString("Click with the mouse to start with invincibility");
    startGameCheatText.setFont(contentManager.getFont());
    startGameCheatText.setCharacterSize(25);
    startGameCheatText.setOutlineColor(sf::Color::White);
    startGameCheatText.setPosition(Game::WORLD_WIDTH / 2 - startGameCheatText.getLocalBounds().width / 2, 550);

    escapeText.setString("Press Escape to quit");
    escapeText.setFont(contentManager.getFont());
    escapeText.setCharacterSize(30);
    escapeText.setOutlineColor(sf::Color::White);
    escapeText.setPosition(Game::WORLD_WIDTH / 2 - escapeText.getLocalBounds().width / 2, Game::WORLD_HEIGHT - 100);

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
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
            retval = true;
        }
        if (event.type == sf::Event::MouseButtonPressed)
        {
            this->result.titleSceneResult.isInvincible = true;
            this->shouldStartGame = true;
        }
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed)
        {
            this->result.titleSceneResult.isInvincible = false;
            this->shouldStartGame = true;
        }
    }
    return retval;
}