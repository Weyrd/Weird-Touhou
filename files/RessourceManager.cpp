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


void RessourceManager::clear() {
}

