#pragma once
#include<raylib.h>
#include<string>
#include<unordered_map>

class assetManager{
private: 
    std::unordered_map<std::string, Texture2D> textures;
    std::unordered_map<std::string, Font> fonts;
    bool unloaded = false;

public: 
    Texture2D& getTexture(const std::string& path);    
    Font& getFont(const std::string& path);
    void unloadAssets();
    ~assetManager();
};