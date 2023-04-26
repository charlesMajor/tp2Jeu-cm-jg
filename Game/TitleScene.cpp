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

    if (this->buttonClicked)
    {
        this->buttonClicked = false;
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
    window.draw(titleSprite);
    window.draw(longGameText);
    window.draw(shortGameText);
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

    titleSprite.setTexture(contentManager.getTitleTexture());
    titleSprite.setPosition(350, 150);

    longGameText.setString("Cliquez-gauche ou appuyez sur Entrée pour jouer une partie courte");
    longGameText.setFont(contentManager.getFont());
    longGameText.setCharacterSize(30);
    longGameText.setOutlineColor(sf::Color::White);
    longGameText.setPosition(100, Game::WORLD_HEIGHT - 100);

    shortGameText.setString("Cliquez-droit ou appuyez sur Spacebar pour jouer une partie longue");
    shortGameText.setFont(contentManager.getFont());
    shortGameText.setCharacterSize(30);
    shortGameText.setOutlineColor(sf::Color::White);
    shortGameText.setPosition(100, Game::WORLD_HEIGHT - 50);

    if (!titleMusic.openFromFile("Assets\\Music\\TvTheme.ogg"))
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
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                this->result.titleSceneResult.isLongGame = false;
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                this->result.titleSceneResult.isLongGame = true;
            }
            // ppoulin
            // Tu ne dois pas démarrer la partie si n'importe quel bouton est appuyé
            this->buttonClicked = true;
        }
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Key::Enter)
            {
                this->result.titleSceneResult.isLongGame = false;
            }
               
            if (event.key.code == sf::Keyboard::Key::Space)
            {
                this->result.titleSceneResult.isLongGame = true;
            }
            // ppoulin
            // Tu ne dois pas démarrer la partie si n'importe quelle touche est appuyée
            this->buttonClicked = true;
        }
    }

    return retval;
}
