#include "tilemap.hpp"
#include "constants.hpp"

#include "engine.hpp"
#include "engine_constants.hpp"
#include "raylib.h"
#include <cstddef>
#include <iterator>
#include <vector>

//UTILITIES =============================
TMap& Tilemap::getMap(const MapType id)
{
  return maps.at(id).data;
}

void Tilemap::setLayer(const MapType& id, Layer layer)
{
  maps.at(id).drawLayer = layer;
}
//=======================================

void Tilemap::LoadFiles(std::vector<MapLoad> files, std::string TsPath, int width, int height)
{
  mapWidth = width;
  mapHeight = height;
  tilesetPath = TsPath;
  Texture2D &tileset = BME.AM.getTexture(tilesetPath);
  tilesPerRow = tileset.width / TILE_SIZE;
  //std::vector<FilePaths*> PathGroups = {&collisionFiles, &visualFiles, &objectFiles};
  //std::vector<TMap*> targets = {&collisionMap, &visualMap, &objectMap};
  
  for(auto& file : files)
  {
    FILE *f = fopen(file.path.c_str(), "r");
    if(!f) { printf("failed to open file: %s", file.path.c_str()); return; }
  
    TileLayer tl(mapHeight, std::vector<int>(mapWidth));
    for(int y = 0; y < mapHeight; y++){
      for(int x = 0; x < mapWidth; x++){
        fscanf(f, "%d", &tl[y][x]);
      }
    }

    maps[file.id].data.push_back(tl);
    maps[file.id].drawLayer = file.layer;
    fclose(f);
  }
}

//===========================================================================================
void Tilemap::Draw() {
  Texture2D &tilesetTexture = BME.AM.getTexture(tilesetPath);
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      int tile = visualMap[y][x];
      // printf("tile value: %d at x:%d y:%d\n", tile, x, y);
      if (tile == -1)
        continue;

      Rectangle src = {(float)(tile % tilesPerRow) * TILE_SIZE,
                       (float)(tile / tilesPerRow) * TILE_SIZE,
                       (float)(TILE_SIZE), (float)(TILE_SIZE)};
      // printf("visualmap hit at x:%d y:%d\n", x, y);
      DrawTextureRec(tilesetTexture, src,
                     {(float)(x * TILE_SIZE), (float)(y * TILE_SIZE)}, WHITE);

      // printf("tile: %d src x: %f src y: %f\n", tile, src.x, src.y);
      //printf("tilesPerRow: %d tileset width: %d\n", tilesPerRow,EWE.AM.getTexture(tilesetPath).width);
    }
  }
}

//====================================================================
/*
void Tilemap::destroyTile(int x, int y) {
  collisionMap[y][x] = -1;
  visualMap[y][x] = -1;
}
*/

void Tilemap::destroyTile(int x, int y, Layer layer, MapType mtype)
{
  if(x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {return;}

  const std::size_t layerIndex = static_cast<std::size_t>(layer);
  auto& layers = getMap(mtype);

  if(layerIndex >= layers.size()) {return;}

  layers[layerIndex][y][x] = -1;
}