#pragma once

#include <cstdio>
#include <string>

class SaveManager{
    public:
    bool openSave(const char* path);
    bool openLoad(const char* path);
    void close();

    //write functions
    void writeInt(int val);
    void writeFloat(float val);
    void writeBool(bool val);
    void writeString(const std::string& val);

    //read functions
    int readInt();
    float readFloat();
    bool readBool();
    std::string readString();

    FILE* getFile() const { return f; }

    bool fileExists(const char* path) const;

    private:
    FILE* f = nullptr;
    
};