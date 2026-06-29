#include "save_manager.hpp"
#include <cstdio>

bool SaveManager::openSave(const char* path)
{
    f = fopen(path, "wb");
    return f != nullptr; 
}

bool SaveManager::openLoad(const char* path)
{
    f = fopen(path, "rb");
    return f != nullptr;
}

void SaveManager::close()
{
    if(f) { fclose(f); f = nullptr; }
}

//===============WRITE FUNCTIONS====================

void SaveManager::writeInt(int val) { fwrite(&val, sizeof(int), 1, f); }

void SaveManager::writeFloat(float val) { fwrite(&val, sizeof(float), 1, f); }

void SaveManager::writeBool(bool val) 
{
    int v = val ? 1 : 0; 
    fwrite(&v, sizeof(bool), 1, f);
}

void SaveManager::writeString(const std::string& val)
{
    int len = (int)val.size();
    fwrite(&len, sizeof(int), 1, f);
    fwrite(val.c_str(), 1, len, f);
}

//=================READ FUNCTIONS==================

int SaveManager::readInt()
{
    int val = 0;
    fread(&val, sizeof(int), 1, f);
    return val;
}

float SaveManager::readFloat()
{
    float val = 0;
    fread(&val, sizeof(float), 1, f);
    return val;
}

bool SaveManager::readBool()
{
    int val = 0;
    fread(&val, sizeof(int), 1, f);
    return val != 0;
}

std::string SaveManager::readString()
{
    int len = 0;
    fread(&len, sizeof(int), 1, f);
    std::string val(len, '\0');
    fread(&val[0], 1, len, f);
    return val;
}

bool SaveManager::fileExists(const char* path) const
{
    FILE* test = fopen(path, "rb");
    if(test) { fclose(test); return true; }
    return false;
}