#include "stdafx.h"
#include "GameContentManager.h"

bool GameContentManager::loadContent()
{
	if (!pokeballTexture.loadFromFile("Assets\\Sprites\\Pokeball.png"))
	{
		return false;
	}

	if (!bulbasaurTexture.loadFromFile("Assets\\Sprites\\Bulbasaur.png"))
	{
		return false;
	}

	//SFML supports the audio file formats WAV, OGG/Vorbis and FLAC. Due to licensing issues MP3 is not supported.
	if (!bulbasaurSoundBuffer.loadFromFile("Assets\\Sounds\\Bulbasaur.ogg"))
	{
		return false;
	}

	if (!font.loadFromFile("Assets\\Fonts\\segoepr.ttf"))
	{
		return false;
	}

	return true;
}

/// <summary>
/// ATTENTION: Seul moment o� le type de retour peut-�tre constant et o� �a peut avoir une importance.
/// Quand on ne retourne pas une r�f�rence, le retour est copi�, alors que ce soit constant ou non n'a aucune importance.
/// 
/// Sauf que en mettant la m�thode const (le const au bout de la signature), �a la fait en sorte que l'objet ne peut �tre modifi� par cette m�thode
/// La r�f�rence revoy�e ne peut donc pas elle non plus permettre de modifier l'objet.
/// 
/// Une r�f�rence const (le const au d�but de la signature) est une r�f�rence inalt�rable.  Le code qui utilise cette r�f�rence
/// Peut seulement lire l'objet r�f�r�, pas le modifier.
/// 
/// Or le sprite veut justement une r�f�rence constante, il a le droit de lire la texture, mais jamais de la modifier.
/// (M�me chose pour les autres classes utilisatrices de ressorces)
/// 
/// LE CONTENT MANAGER S'ASSURE DONC QUE NOS RESSOURCES RESTENT INT�GRES
/// </summary>
const sf::Texture& GameContentManager::getBulbasaurTexture() const
{
	return bulbasaurTexture;
}

const sf::Texture& GameContentManager::getPokeballTexture() const
{
	return pokeballTexture;
}

const sf::SoundBuffer& GameContentManager::getBulbasaurSoundBuffer() const
{
	return bulbasaurSoundBuffer;
}

const sf::Font& GameContentManager::getFont() const
{
	return font;
}

GameContentManager::GameContentManager()
: ContentManager()
{
}

