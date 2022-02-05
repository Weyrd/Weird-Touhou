#include "RessourceManager.h"
using namespace sf;
using namespace std;

void RessourceManager::loadTexture(const std::string& name, const std::string& filename)
{
	/* Load the texture */
	sf::Texture tex;
	tex.loadFromFile(filename);
	tex.setSmooth(true);
	/* Add it to the list of textures */
	this->textures[name] = tex;

	return;
}

sf::Texture& RessourceManager::getRefTex(const std::string& texture)
{
	return this->textures.at(texture);
}


/* Fonts */
void RessourceManager::loadFont(const std::string& name, const std::string& filename)
{
	sf::Font font;
	font.loadFromFile(filename);

	this->fonts[name] = font;

	return;
}

sf::Font& RessourceManager::getRefFont(const std::string& font)
{
	return this->fonts.at(font);
}


/* SoundBuffer */
void RessourceManager::loadSoundBuffer(const std::string& name, const std::string& filename)
{
	sf::SoundBuffer soundBuffer;
	soundBuffer.loadFromFile(filename);

	this->soundBuffer[name] = soundBuffer;

	return;
}

sf::SoundBuffer& RessourceManager::getRefSoundBuffer(const std::string& soundBuffer)
{
	return this->soundBuffer.at(soundBuffer);
}

void RessourceManager::clear() {
}

