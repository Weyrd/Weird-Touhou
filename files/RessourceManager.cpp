#include "RessourceManager.h"


/* --- TEXTURE --- */
void RessourceManager::loadTexture(const std::string& name, const std::string& filename) {
	if (this->soundBuffer.count(filename) == 0) {
		sf::Texture tex;
		tex.loadFromFile(filename);
		tex.setSmooth(true);
		this->textures[name] = tex;
	} return;
}

sf::Texture& RessourceManager::getRefTex(const std::string& texture) {
	return this->textures.at(texture);
}


/* --- FONT --- */
void RessourceManager::loadFont(const std::string& name, const std::string& filename) {
	if(this->fonts.count(filename) == 0) {
		sf::Font font;
		font.loadFromFile(filename);
		this->fonts[name] = font; 
	} return;
}

sf::Font& RessourceManager::getRefFont(const std::string& font){
	return this->fonts.at(font);
}




/* --- SOUND BUFFER ---  */
void RessourceManager::loadSoundBuffer(const std::string& name, const std::string& filename) {
	if (this->soundBuffer.count(filename) == 0) {
		sf::SoundBuffer soundBuffer;
		soundBuffer.loadFromFile(filename);
		this->soundBuffer[name] = soundBuffer;
	} return;
}

sf::SoundBuffer& RessourceManager::getRefSoundBuffer(const std::string& soundBuffer) {
	return this->soundBuffer.at(soundBuffer);
}


void RessourceManager::clear() {
}

