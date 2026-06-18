#pragma once

#include "raylib.h"
#include <string>
#include <unordered_map>

class FacesetManager{
    public:
    void registerFace(const std::string& name, Rectangle rect);
    bool getFace(const std::string& name, Rectangle& out) const;
    Texture2D texture;

    private:
    std::unordered_map<std::string, Rectangle> faces;
};