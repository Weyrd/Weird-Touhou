#pragma once
#include "Header.h"

using namespace sf;
using namespace std;

class RessourceManager {
private:

    /* Array of textures used */
    std::map<std::string, sf::Texture> textures;
    std::map<std::string, sf::SoundBuffer> soundBuffer;
    std::map<std::string, sf::Font> fonts;

public:

    /* Add a texture from a file */
    void loadTexture(const std::string& name, const std::string& filename);
    void loadSoundBuffer(const std::string& name, const std::string& filename);
    void loadFont(const std::string& name, const std::string& filename);

    /* Translate an id into a reference */
    sf::Texture& getRefTex(const std::string& texture);
    sf::SoundBuffer& getRefSoundBuffer(const std::string& soundBuffer);
    sf::Font& getRefFont(const std::string& font);

    void clear();
    /* Constructor */
    RessourceManager(){ }
};

