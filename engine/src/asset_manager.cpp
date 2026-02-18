#include "asset_manager.hpp"

Texture2D& assetManager::getTexture(const std::string& path)
{
    if(textures.find(path) == textures.end())
    {
        textures[path] = LoadTexture(path.c_str());
        SetTextureFilter(textures[path], TEXTURE_FILTER_POINT);
    }
    return textures[path];
}

Font& assetManager::getFont(const std::string& path)
{
    if(fonts.find(path) == fonts.end())
    {
        fonts[path] = LoadFont(path.c_str());
        //fonts[path] = LoadFontEx(path.c_str(), 32, NULL, 0);
        SetTextureFilter(fonts[path].texture, TEXTURE_FILTER_POINT);
    }
    return fonts[path];
}

void assetManager::unloadAssets()
{
    for(auto& pair : textures) UnloadTexture(pair.second);
    textures.clear();
    for(auto& pair : fonts) UnloadFont(pair.second);
    fonts.clear();
    unloaded = true;
}

assetManager::~assetManager()
{
    printf("AM destructor called\n");
    if(!unloaded) unloadAssets();
    printf("after AM destructor\n");

}