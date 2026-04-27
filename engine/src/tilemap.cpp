#include "tilemap.hpp"
#include "constants.hpp"

#include "engine.hpp"

//-----------------------------
void Tilemap::Load(const char *collisionFile, const char *visualFile,
                   const char *objectFile, const char *TsPath, int width,
                   int height) {
  mapWidth = width;
  mapHeight = height;
  tilesetPath = TsPath;
  Texture2D &tileset = EWE.AM.getTexture(tilesetPath);
  tilesPerRow = tileset.width / TILE_SIZE;

  //---------COLLISION MAP----------------
  FILE *col = fopen(collisionFile, "r");
  if (!col) {
    printf("failed to load collision map: %s\n", collisionFile);
    return;
  }

  collisionMap.resize(mapHeight, std::vector<int>(mapWidth));
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      fscanf(col, "%d,", &collisionMap[y][x]);
    }
  }

  fclose(col);

  //---------VISUAL MAP----------------
  FILE *vis = fopen(visualFile, "r");
  if (!vis) {
    printf("failed to load visual map: %s\n", visualFile);
    return;
  }

  visualMap.resize(mapHeight, std::vector<int>(mapWidth));
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      fscanf(vis, "%d,", &visualMap[y][x]);
    }
  }
  fclose(vis);

  //----------OBJECT MAP---------------
  FILE *obj = fopen(objectFile, "r");
  if (!obj) {
    printf("failed to load object map: %s\n", objectFile);
    return;
  }
  objectMap.resize(mapHeight, std::vector<int>(mapWidth));
  for (int y = 0; y < mapHeight; y++) {
    for (int x = 0; x < mapWidth; x++) {
      fscanf(obj, "%d,", &objectMap[y][x]);
    }
  }
  fclose(obj);

}

//-------------------------------
void Tilemap::Draw() {
  Texture2D &tilesetTexture = EWE.AM.getTexture(tilesetPath);
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