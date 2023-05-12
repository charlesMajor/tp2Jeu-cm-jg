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

    if (needsToEnterName)
    {
        if (currentName.length() < 3)
        {
            nomText.setString("Entrez un nom à trois lettres");
            nomText.setPosition(190, 250);
        }
        else
        {
            nomText.setString("Appuyez sur Enter pour accepter");
            nomText.setPosition(150, 250);
        }
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
        
        if (pressedBackspace)
        {
            if (EndGameScene::currentName.length() > 0)
            {
                std::string oldName = EndGameScene::currentName;
                EndGameScene::currentName = "";
                for (int i = 0; i < oldName.length() - 1; i++)
                {
                    EndGameScene::currentName += oldName[i];
                }
                currentNameText.setString(EndGameScene::currentName);
            }
            pressedBackspace = false;
        }

        if (letterPressed)
        {
            if (currentName.length() < 3)
            {
                currentName += currentLetter;
                currentNameText.setString(currentName);
            }
            letterPressed = false;
        }

        if (pressedEnter)
        {
            if (currentName.length() == 3)
            {
                needsToEnterName = false;
                drawNomText = false;
                
            }
            pressedEnter = false;
        }
        backToTitle = false;
    }
    else if (!needsToEnterName && !listsAreFilled)
    {
        fillLists();
    }
    else if (this->backToTitle)
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
    
    if (drawNomText)
    {
        window.draw(nomText);
    }

    if (needsToEnterName)
    {
        window.draw(currentNameText);
    }
    else
    {
        window.draw(backToTitleText);
    }

    if (listsAreFilled)
    {
        for (sf::Text currentPlayer : bestPlayers)
        {
            window.draw(currentPlayer);
        }

        for (sf::Text currentScore : bestScores)
        {
            window.draw(currentScore);
        }
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

    currentNameText.setFont(contentManager.getFont());
    currentNameText.setCharacterSize(25);
    currentNameText.setOutlineColor(sf::Color::White);
    currentNameText.setPosition(330, 300);

    if (!endMusic.openFromFile("Assets\\Music\\GameTheme.ogg"))
    {
        return false;
    }
    endMusic.setLoop(true);
    endMusic.play();

    unserializeTab();
    
    std::cout << playerScore << std::endl;

    for (int i = 0; i < AMOUNT_IN_LEADERBOARD; i++)
    {
        if (newTable[i].score < playerScore)
        {
            if (placeInLeaderBoard == 6)
            {
                placeInLeaderBoard = i;
                needsToEnterName = true;
                EndGameScene::currentName = "";
                currentNameText.setString(EndGameScene::currentName);
            }
        }
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
            if (event.key.code == sf::Keyboard::Key::Escape)
            {
                this->backToTitle = true;
            }
            else if (event.key.code == sf::Keyboard::Key::Enter)
            {
                this->pressedEnter = true;
            }
            else if (event.key.code == sf::Keyboard::Key::Backspace)
            {
                this->pressedBackspace = true;
            }
            else if (event.key.code == sf::Keyboard::Key::A)
            {
                this->currentLetter = 'A';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::B)
            {
                this->currentLetter = 'B';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::C)
            {
                this->currentLetter = 'C';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::D)
            {
                this->currentLetter = 'D';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::E)
            {
                this->currentLetter = 'E';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::F)
            {
                this->currentLetter = 'F';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::G)
            {
                this->currentLetter = 'G';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::H)
            {
                this->currentLetter = 'H';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::I)
            {
                this->currentLetter = 'I';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::J)
            {
                this->currentLetter = 'J';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::K)
            {
                this->currentLetter = 'K';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::L)
            {
                this->currentLetter = 'L';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::M)
            {
                this->currentLetter = 'M';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::N)
            {
                this->currentLetter = 'N';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::O)
            {
                this->currentLetter = 'O';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::P)
            {
                this->currentLetter = 'P';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::Q)
            {
                this->currentLetter = 'Q';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::R)
            {
                this->currentLetter = 'R';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::S)
            {
                this->currentLetter = 'S';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::T)
            {
                this->currentLetter = 'T';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::U)
            {
                this->currentLetter = 'U';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::V)
            {
                this->currentLetter = 'V';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::W)
            {
                this->currentLetter = 'W';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::X)
            {
                this->currentLetter = 'X';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::Y)
            {
                this->currentLetter = 'Y';
                this->letterPressed = true;
            }
            else if (event.key.code == sf::Keyboard::Key::Z)
            {
                this->currentLetter = 'Z';
                this->letterPressed = true;
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

void EndGameScene::fillLists()
{
    for (int i = 0; i < AMOUNT_IN_LEADERBOARD; i++)
    {
        std::cout << newTable[i].name << std::endl;
        std::cout << newTable[i].score << std::endl;

        if (i < placeInLeaderBoard)
        {
            for (int x = 0; x < 3; x++)
            {
                baseTable[i].name[x] = newTable[i].name[x];
            }
            baseTable[i].score = newTable[i].score;
        }
        if (i == placeInLeaderBoard)
        {
            baseTable[i].name[0] = EndGameScene::currentName[0];
            baseTable[i].name[1] = EndGameScene::currentName[1];
            baseTable[i].name[2] = EndGameScene::currentName[2];
            baseTable[i].score = playerScore;
        }
        else if (i > placeInLeaderBoard)
        {
            for (int x = 0; x < 3; x++)
            {
                baseTable[i].name[x] = newTable[i - 1].name[x];
            }
            baseTable[i].score = newTable[i - 1].score;
        }
    }

    for (int i = 0; i < AMOUNT_IN_LEADERBOARD; i++)
    {
        sf::Text currentPlayer;
        currentPlayer.setString(baseTable[i].name);
        currentPlayer.setFont(contentManager.getFont());
        currentPlayer.setCharacterSize(35);
        currentPlayer.setOutlineColor(sf::Color::White);
        currentPlayer.setPosition(250, i * 40 + 300);
        bestPlayers.push_back(currentPlayer);

        sf::Text currentScore;
        currentScore.setString(std::to_string(baseTable[i].score));
        currentScore.setFont(contentManager.getFont());
        currentScore.setCharacterSize(35);
        currentScore.setOutlineColor(sf::Color::White);
        currentScore.setPosition(400, i * 40 + 300);
        bestScores.push_back(currentScore);
    }
    listsAreFilled = true;

    serializeTab();
}