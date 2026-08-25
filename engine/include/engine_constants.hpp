#pragma once
#include <string>
#include <vector>

// DO NOT TOUCH UNLESS YOU ABSOLUTELY HAVE TO ===========
using TileLayer = std::vector<std::vector<int>>;
using TMap = std::vector<TileLayer>;
using FilePaths = std::vector<std::string>;
// ======================================================

enum struct Direction { UP, DOWN, LEFT, RIGHT };