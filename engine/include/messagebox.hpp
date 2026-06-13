#pragma once
#include "raylib.h"
#include <string>
#include <vector>

constexpr Rectangle MSG_BOX = {16, 340, 608, 124};
constexpr int MSG_PADDING = 8;
constexpr int MSG_SPACING = 4;
constexpr int MSG_FONTSIZE = 16;
enum class messageState { TYPING, FULL, WAITING, DONE };

class MessageBox
{
    public:
    void Start(const std::string& raw, const std::string& speakerName);
    void Update(float dt);
    void Draw();
    bool isActive() const { return active; }

    private:

    Font defaultFont = {0,0,0,0};

    void LoadPage(int index);
    void splitWords(const std::string& page);

    std::vector<std::string> pages;
    std::vector<std::string> words;
    std::vector<std::string> lines;

    std::string speaker;
    std::string currentLine;
    std::string displayed;
    int currentPage = 0;
    int currentWord = 0;

    float wordTimer = 0.f;
    const float WORD_DELAY = 0.08f;

    int waitFrames = 0;
    const int WAIT_FRAMES = 10;

    messageState msgState = messageState::DONE;
    bool active = false;

    int boxWdith = MSG_BOX.width - MSG_PADDING * 2;
};