#include "asset_manager.hpp"
#include "raylib.h"

Texture2D& AssetManager::getTexture(const std::string& path)
{
    if(textures.find(path) == textures.end())
    {
        textures[path] = LoadTexture(path.c_str());
        SetTextureFilter(textures[path], TEXTURE_FILTER_POINT);
    }
    return textures[path];
}

Font& AssetManager::getFont(const std::string& path)
{
    if(fonts.find(path) == fonts.end())
    {
        fonts[path] = LoadFont(path.c_str());
        //fonts[path] = LoadFontEx(path.c_str(), 32, NULL, 0);
        SetTextureFilter(fonts[path].texture, TEXTURE_FILTER_POINT);
    }
    return fonts[path];
}

Font& AssetManager::getFontEx(const std::string& path, int FontSize, std::vector<int> codepoints)
{
    if(fonts.find(path) == fonts.end())
    {
        fonts[path] = LoadFontEx(path.c_str(), FontSize, codepoints.data(), codepoints.size());
        SetTextureFilter(fonts[path].texture, TEXTURE_FILTER_POINT);
    }
    return fonts[path];
}

Sound& AssetManager::getSound(const std::string& path)
{
    if(sounds.find(path) == sounds.end())
    {
        sounds[path] = LoadSound(path.c_str());
    }
    return sounds[path];
}

Music& AssetManager::getMusic(const std::string &path)
{
    if(music.find(path) == music.end())
    {
        music[path] = LoadMusicStream(path.c_str());
    }
    return music[path];
    // use "UpdateMusicStream(music_path)" in update function load next bytes
}

Model& AssetManager::getModel(const std::string& path)
{
    if(model.find(path) == model.end())
    {
        model[path] = LoadModel(path.c_str());
    }
    return model[path];
}

void AssetManager::unloadAssets()
{
    for(auto& pair : textures) UnloadTexture(pair.second);
    textures.clear();
    for(auto& pair : fonts) UnloadFont(pair.second);
    fonts.clear();
    for(auto& pair : sounds) UnloadSound(pair.second);
    sounds.clear();
    for(auto& pair : model) UnloadModel(pair.second);
    model.clear();
    unloaded = true;
}

AssetManager::~AssetManager()
{
    printf("AM destructor called\n");
    if(!unloaded) unloadAssets();
    printf("after AM destructor\n");

}