#include "tilemap.hpp"
#include "constants.hpp"

#include "engine.hpp"
#include "engine_constants.hpp"
#include "raylib.h"
#include <vector>

//HELPERS =============================
TMap& Tilemap::getMap(const MapType id)
{
  return maps.at(id).data;
}
//=======================================

void Tilemap::LoadFiles(std::vector<MapLoad> files, std::string TsPath, int width, int height)
{
  mapWidth = width;
  mapHeight = height;
  tilesetPath = TsPath;
  Texture2D &tileset = BME.AM.getTexture(tilesetPath);
  tilesPerRow = tileset.width / TILE_SIZE;
  
  for(auto& file : files)
  {
    FILE *f = fopen(file.path.c_str(), "r");
    if(!f) { printf("failed to open file: %s", file.path.c_str()); return; }
  
    TileLayer tl(mapHeight, std::vector<int>(mapWidth));
    for(int y = 0; y < mapHeight; y++){
      for(int x = 0; x < mapWidth; x++){
        fscanf(f, "%d", &tl[y][x]);
        fgetc(f);
      }
    }

    maps[file.id].data[file.layer] = std::move(tl);
    fclose(f);
  }
  buildDrawCache();
}

//===========================================================================================
void Tilemap::buildDrawCache()
{
  drawCache.clear();

  for(auto& [MapType, entry] : maps)
  {
    for(auto& [layer, tileLayer] : entry.data)
    {
      for(int y = 0; y < mapHeight; y++)
      {
        for(int x = 0; x < mapWidth; x++)
        {
          int id = tileLayer[y][x];
          if(id < 0) continue;

          TileInstance tile;
          tile.src = {(float)((id % tilesPerRow) * TILE_SIZE),
                      (float)((id / tilesPerRow) * TILE_SIZE),
                      (float)TILE_SIZE, (float)TILE_SIZE
                    };
          
          tile.pos = {(float)(x * TILE_SIZE), (float)(y * TILE_SIZE)};
          drawCache[layer].push_back(tile);

        }
      }
    }
  }
}

void Tilemap::Draw() {
  Texture2D &tilesetTexture = BME.AM.getTexture(tilesetPath);
  for(auto& [layer, tiles] : drawCache)
  {
    for(auto& tile : tiles)
    {
      DrawTextureRec(tilesetTexture, tile.src, tile.pos, WHITE);
    }
  }
}

//====================================================================
void Tilemap::destroyTile(int x, int y, Layer layer, MapType mtype)
{
  if(x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {return;}

  auto& layers = getMap(mtype);

  auto it = layers.find(layer);
  if(it == layers.end())
  {
    printf("layer not found for maptype\n");
    return;
  }

  auto& currentLayer = it->second;

  if(currentLayer[y][x] == -1) {return;}
  currentLayer[y][x] = -1;
  buildDrawCache();
}

void Tilemap::setTile(int x, int y, int spriteVal, Layer layer, MapType mtype)
{
  if(x < 0 || y < 0 || x >= mapWidth || y >= mapHeight) {return;}

  auto& layers = getMap(mtype);

  auto it = layers.find(layer);
  if(it == layers.end())
  {
    printf("layer not found for maptype\n");
    return;
  }

  auto& currentLayer = it->second;

  if(currentLayer[y][x] == spriteVal) {return;}
  currentLayer[y][x] = spriteVal;
  buildDrawCache();
}