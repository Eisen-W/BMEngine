#pragma once
#include<raylib.h>
#include<vector>
#include<string>

class Tilemap{
    public:
    void Load(const char* collisionFile, const char* visualFile, const char* objectFile, const char* TsPath,  
                int width, int height);
    void Draw();
    void destroyTile(int x, int y);

    void setCollisionTile(int x, int y, int val) { collisionMap[y][x] = val; }
    void setVisualTile(int x, int y, int val) {visualMap[y][x] = val; }
    void setObjectTile(int x, int y, int val) { objectMap[y][x] = val; }

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }

    std::vector<std::vector<int>> collisionMap;
    std::vector<std::vector<int>> visualMap;
    std::vector<std::vector<int>> objectMap;

    private:
    std::string tilesetPath;

    int mapWidth = 0;
    int mapHeight = 0;
    int tilesPerRow = 0;
};