#include "faceset_manager.hpp"

void FacesetManager::registerFace(const std::string& name, Rectangle rect)
{
    faces[name] = rect;
}

bool FacesetManager::getFace(const std::string& name, Rectangle& out) const
{
    auto it = faces.find(name);
    if(it == faces.end()) return false;
    out = it->second;
    return true;
}