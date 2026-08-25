#pragma once
#include "engine_constants.hpp"
#include<raylib.h>
#include<string>

class Tilemap{
    public:
    // EXPERIMENTAL ===================================
    void LoadFiles(FilePaths collisionFiles, FilePaths visualFiles, FilePaths objectFiles,
                    std::string TsPath, int width, int height);
    // ================================================
    void Load(const char* collisionFile, const char* visualFile, const char* objectFile, const char* TsPath,  
                int width, int height) {} // Deprecated and removed

    void Draw();
    void destroyTile(int x, int y);

    void setCollisionTile(int x, int y, int val) { collisionMap[1][y][x] = val; }
    void setVisualTile(int x, int y, int val) { visualMap[2][y][x] = val; }
    void setObjectTile(int x, int y, int val) { objectMap[3][y][x] = val; }

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }

    /*
    std::vector<std::vector<int>> collisionMap;
    std::vector<std::vector<int>> visualMap;
    std::vector<std::vector<int>> objectMap;
    */

    TMap collisionMap;
    TMap visualMap;
    TMap objectMap; 

    private:
    std::string tilesetPath;

    int mapWidth = 0;
    int mapHeight = 0;
    int tilesPerRow = 0;
};