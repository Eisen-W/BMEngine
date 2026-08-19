#pragma once

#include <string>
#include <unordered_map>
#include <unordered_set>

class IScreen{
    public:
    virtual ~IScreen() = default;
    virtual void Init() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;

    std::string nextScreen;
    bool LazyInit = false;
};

class ScreenManager{
    public:
    void add(const std::string& id, IScreen* screen);
    void switchTo(const std::string& id);

    void InitAll();
    void Update();
    void Draw();

    private:
    std::unordered_map<std::string, IScreen*> m_screens;
    IScreen* m_current = nullptr;

    //for lazy loading
    std::unordered_set<std::string> m_initialized;
};