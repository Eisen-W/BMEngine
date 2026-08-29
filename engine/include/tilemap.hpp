#pragma once
#include "constants.hpp"
#include "engine_constants.hpp"
#include <map>
#include <raylib.h>
#include <string>
#include <vector>

struct MapEntry{
    TMap data;
};


struct MapLoad{
    MapType id;
    std::string path;
    Layer layer;
};

struct TileInstance{
    Rectangle src;
    Vector2 pos;
};

class Tilemap{
    public:
    // Old Load function removed
    void LoadFiles(std::vector<MapLoad> files, std::string TsPath, int width, int height);
    void Draw();
    void buildDrawCache();

    //HELPERS
    TMap& getMap(const MapType id);

    void destroyTile(int x, int y, Layer layer, MapType mtype = MapType::COLLISION);
    void setTile(int x, int y, int spriteVal, Layer layer, MapType mtype);
    void updateCache(int x, int y, Layer layer, MapType mtype);

    int getMapWidth() const { return mapWidth; }
    int getMapHeight() const { return mapHeight; }

    std::map<MapType, MapEntry> maps;
    std::map<Layer, std::vector<TileInstance>> drawCache;


    std::map<Layer, TMap> drawableLayers;

    private:
    std::string tilesetPath;

    int mapWidth = 0;
    int mapHeight = 0;
    int tilesPerRow = 0;
};