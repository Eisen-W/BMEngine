#pragma once
#include "constants.hpp"
#include "engine_constants.hpp"
#include <map>
#include <raylib.h>
#include <string>
#include <vector>

struct MapEntry{
    TMap data;
    Layer drawLayer;
};


struct MapLoad{
    MapType id;
    std::string path;
    Layer layer;
};

class Tilemap{
    public:
    // EXPERIMENTAL ===================================
    void LoadFiles(std::vector<MapLoad> files, std::string TsPath, int width, int height);
    // ================================================
    void Load(const char* collisionFile, const char* visualFile, const char* objectFile, const char* TsPath,  
                int width, int height) {} // Deprecated and removed

    void Draw();

    //UTILITIES
    TMap& getMap(const MapType id);
    void setLayer(const MapType& id, Layer layer);


    void destroyTile(int x, int y, Layer layer, MapType mtype = MapType::COLLISION);

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

    std::map<MapType, MapEntry> maps;

    TMap collisionMap;
    TMap visualMap;
    TMap objectMap; 

    std::map<Layer, TMap> drawableLayers;
    std::vector<TMap> collisionLayers;

    private:
    std::string tilesetPath;

    int mapWidth = 0;
    int mapHeight = 0;
    int tilesPerRow = 0;
};