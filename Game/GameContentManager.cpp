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
/// ATTENTION: Seul moment où le type de retour peut-être constant et où ça peut avoir une importance.
/// Quand on ne retourne pas une référence, le retour est copié, alors que ce soit constant ou non n'a aucune importance.
/// 
/// Sauf que en mettant la méthode const (le const au bout de la signature), ça la fait en sorte que l'objet ne peut être modifié par cette méthode
/// La référence revoyée ne peut donc pas elle non plus permettre de modifier l'objet.
/// 
/// Une référence const (le const au début de la signature) est une référence inaltérable.  Le code qui utilise cette référence
/// Peut seulement lire l'objet référé, pas le modifier.
/// 
/// Or le sprite veut justement une référence constante, il a le droit de lire la texture, mais jamais de la modifier.
/// (Même chose pour les autres classes utilisatrices de ressorces)
/// 
/// LE CONTENT MANAGER S'ASSURE DONC QUE NOS RESSOURCES RESTENT INTÈGRES
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

