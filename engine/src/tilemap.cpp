#include "tilemap.hpp"
#include "constants.hpp"

#include "engine.hpp"
#include "engine_constants.hpp"
#include "raylib.h"
#include <vector>

void Tilemap::LoadFiles(FilePaths collisionFiles, FilePaths visualFiles, FilePaths objectFiles,
                    std::string TsPath, int width, int height)
{
  mapWidth = width;
  mapHeight = height;
  tilesetPath = TsPath;
  Texture2D &tileset = BME.AM.getTexture(tilesetPath);
  tilesPerRow = tileset.width / TILE_SIZE;
  std::vector<FilePaths*> PathGroups = {&collisionFiles, &visualFiles, &objectFiles};
  std::vector<TMap*> targets = {&collisionMap, &visualMap, &objectMap};

  for(int i = 0; i < PathGroups.size(); i++)
  {
    auto& group = *PathGroups[i];
    auto& target = *targets[i];
    target.resize(group.size()); // one layer per file

    for(int layer = 0; layer < group.size(); layer++)
    {
      FILE *f = fopen(group[layer].c_str(), "r");
      if(!f) { printf("failed to open file: %s", group[layer].c_str()); return; }

      target[layer].resize(mapHeight, std::vector<int>(mapWidth));
      for(int y = 0; y < mapHeight; y++){
        for(int x = 0; x < mapWidth; x++){
          fscanf(f, "%d", &target[layer][y][x]);
        }
      }
      fclose(f);
    }
  }
}

//-------------------------------
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

//------------------------------------------
void Tilemap::destroyTile(int x, int y) {
  collisionMap[y][x] = -1;
  visualMap[y][x] = -1;
}