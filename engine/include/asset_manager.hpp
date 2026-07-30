#pragma once
#include<raylib.h>
#include<string>
#include<unordered_map>
#include <vector>

class AssetManager{
private: 
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Font> fonts;
    std::unordered_map<std::string, Sound> sounds;
    std::unordered_map<std::string, Music> music;
    std::unordered_map<std::string, Model> model;
    bool unloaded = false;

public: 
    Texture2D& getTexture(const std::string& path);    
    Font& getFont(const std::string& path);
    Font& getFontEx(const std::string& path, int FontSize, std::vector<int> codepoints);
    Sound& getSound(const std::string& path);
    Music& getMusic(const std::string& path);
    Model& getModel(const std::string& path);
    void unloadAssets();
    ~AssetManager();
};