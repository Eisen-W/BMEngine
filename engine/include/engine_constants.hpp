#pragma once
#include "constants.hpp"
#include <string>
#include <utility>
#include <vector>

// DO NOT TOUCH UNLESS YOU ABSOLUTELY HAVE TO ===========
using TileLayer = std::vector<std::vector<int>>;
using TMap = std::vector<TileLayer>;
using FilePaths = std::vector<std::string>;
using LayeredFilePaths = std::vector<std::pair<std::string, Layer>>;

enum struct MapType{ COLLISION, VISUAL, OBJECT,};
// ======================================================

enum struct Direction { UP, DOWN, LEFT, RIGHT };