#pragma once
#include<raylib.h>
#include<string>
#include<unordered_map>

class assetManager{
private: 
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> music;
    bool unloaded = false;

public: 
    Texture2D& getTexture(const std::string& path);    
    Font& getFont(const std::string& path);
    Sound& getSound(const std::string& path);
    Music& getMusic(const std::string& path);
    void unloadAssets();
    ~assetManager();
};