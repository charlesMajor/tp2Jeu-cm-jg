#include "stdafx.h"
#include "EndGameScene.h"
#include "game.h"
#include "EndGameContentManager.h"

EndGameScene::EndGameScene()
    : Scene(SceneType::GAME_SCENE)
{
}

EndGameScene::~EndGameScene()
{

}

SceneType EndGameScene::update()
{
    SceneType retval = getSceneType();

    if (this->backToTitle)
    {
        retval = SceneType::NONE;
    }

    return retval;
}

void EndGameScene::pause()
{
    this->endMusic.stop();
}

void EndGameScene::unPause()
{

}

void EndGameScene::draw(sf::RenderWindow& window) const
{
    window.draw(endSprite);
    window.draw(gameOverText);
    window.draw(backToTitleText);
}

bool EndGameScene::uninit()
{
    return true;
}

bool EndGameScene::init()
{
    if (contentManager.loadContent() == false)
    {
        return false;
    }

    endSprite.setTexture(contentManager.getEndTexture());
    endSprite.setPosition(525, 250);

    gameOverText.setString("Partie Terminée - score: " + std::to_string(this->result.gameSceneResult.score));
    gameOverText.setFont(contentManager.getFont());
    gameOverText.setCharacterSize(45);
    gameOverText.setOutlineColor(sf::Color::White);
    gameOverText.setPosition(325, Game::WORLD_HEIGHT - 200);

    backToTitleText.setString("Appuyez sur Entrée pour retourner au titre");
    backToTitleText.setFont(contentManager.getFont());
    backToTitleText.setCharacterSize(45);
    backToTitleText.setOutlineColor(sf::Color::White);
    backToTitleText.setPosition(150, Game::WORLD_HEIGHT - 100);

    if (!endMusic.openFromFile("Assets\\Music\\GameTheme.ogg"))
    {
        return false;
    }
    endMusic.setLoop(true);
    endMusic.play();


    return true;
}

bool EndGameScene::handleEvents(sf::RenderWindow& window)
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
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Key::Enter)
            {
                this->backToTitle = true;
            }
        }
    }

    return retval;
}
