#include "stdafx.h"
#include "EndGameScene.h"
#include "game.h"
#include "EndGameContentManager.h"
#include <iostream>
#include <fstream>

const int EndGameScene::AMOUNT_IN_LEADERBOARD = 5;

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

    changeNomTextState = std::max(0, changeNomTextState - 1);
    if (changeNomTextState == 0)
    {
        if (drawNomText)
        {
            drawNomText = false;
        }
        else
        {
            drawNomText = true;
        }
        changeNomTextState = 30;
    }

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
    window.draw(gameOverText);
    window.draw(leaderboardText);
    window.draw(backToTitleText);
    if (drawNomText)
    {
        window.draw(nomText);
    }
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

    playerScore = this->result.gameSceneResult.score;

    gameOverText.setString("GAME OVER");
    gameOverText.setFont(contentManager.getFont());
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineColor(sf::Color::White);
    gameOverText.setPosition(200, 50);

    leaderboardText.setString("LEADERBOARD");
    leaderboardText.setFont(contentManager.getFont());
    leaderboardText.setCharacterSize(35);
    leaderboardText.setOutlineColor(sf::Color::White);
    leaderboardText.setPosition(225, 150);

    backToTitleText.setString("Appuyez sur Esc pour retourner au titre");
    backToTitleText.setFont(contentManager.getFont());
    backToTitleText.setCharacterSize(25);
    backToTitleText.setOutlineColor(sf::Color::White);
    backToTitleText.setPosition(100, Game::WORLD_HEIGHT - 100);

    nomText.setString("Entrez un nom à trois lettres");
    nomText.setFont(contentManager.getFont());
    nomText.setCharacterSize(25);
    nomText.setOutlineColor(sf::Color::White);
    nomText.setPosition(190, 250);

    if (!endMusic.openFromFile("Assets\\Music\\GameTheme.ogg"))
    {
        return false;
    }
    endMusic.setLoop(true);
    endMusic.play();

    //std::cout << filePath << std::endl;

    /*EndGameScene::baseTable[0].score = 10000;
    EndGameScene::baseTable[0].name[0] = 'J';
    EndGameScene::baseTable[0].name[1] = 'A';
    EndGameScene::baseTable[0].name[2] = 'M';*/
    //std::string name0 = "JAM";
    //sprintf_s(baseTable[0].name, "%s", name0.c_str());
    //for (int j = 0; j < name0.length(); j++)
      //  baseTable[0].name[j] = name0[j];

    /*EndGameScene::baseTable[1].score = 2100;
    EndGameScene::baseTable[1].name[0] = 'P';
    EndGameScene::baseTable[1].name[1] = 'O';
    EndGameScene::baseTable[1].name[2] = 'G';*/
    //std::string name1 = "POG";
    //sprintf_s(baseTable[1].name, "%s", name1.c_str());
    //for (int j = 0; j < name0.length(); j++)
      //  baseTable[1].name[j] = name0[j];

    /*EndGameScene::baseTable[2].score = 1050;
    EndGameScene::baseTable[2].name[0] = 'C';
    EndGameScene::baseTable[2].name[1] = 'H';
    EndGameScene::baseTable[2].name[2] = 'A';*/
    //std::string name2 = "CHA";
    //sprintf_s(baseTable[2].name, "%s", name2.c_str());
    //for (int j = 0; j < name0.length(); j++)
      //  baseTable[2].name[j] = name0[j];

    /*EndGameScene::baseTable[3].score = 550;
    EndGameScene::baseTable[3].name[0] = 'E';
    EndGameScene::baseTable[3].name[1] = 'L';
    EndGameScene::baseTable[3].name[2] = 'O';*/
    //std::string name3 = "ELO";
    //sprintf_s(baseTable[3].name, "%s", name3.c_str());
    //for (int j = 0; j < name0.length(); j++)
      //  baseTable[3].name[j] = name0[j];

    /*EndGameScene::baseTable[4].score = 100;
    EndGameScene::baseTable[4].name[0] = 'D';
    EndGameScene::baseTable[4].name[1] = 'I';
    EndGameScene::baseTable[4].name[2] = 'F';*/
    //std::string name4 = "DIF";
    //sprintf_s(baseTable[4].name, "%s", name4.c_str());
    //for (int j = 0; j < name0.length(); j++)
      //  baseTable[4].name[j] = name0[j];

    //std::cout << filePath << std::endl;

    //serializeTab();
    unserializeTab();
    
    std::cout << playerScore << std::endl;

    for (int i = 0; i < AMOUNT_IN_LEADERBOARD; i++)
    {
        std::cout << newTable[i].name << std::endl;
        std::cout << newTable[i].score << std::endl;

        if (newTable[i].score > )
    }

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

void EndGameScene::serializeTab()
{
    std::ofstream ofs("score.bin", std::ios::binary);
    ofs.write((char*)&baseTable, (sizeof(Score) * 5));
    ofs.close();
}

bool EndGameScene::unserializeTab()
{
    std::ifstream ifs("score.bin", std::ios::binary);
    if (!ifs)
        return false;
    ifs.read((char*)&newTable, (sizeof(Score) * 5));
    ifs.close();
}

void EndGameScene::replaceIfBetter()
{

}