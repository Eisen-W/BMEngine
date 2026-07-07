#pragma once
#include "raylib.h"
#include <string>
#include <vector>

constexpr Rectangle MSG_BOX = {16, 340, 608, 124};
constexpr int MSG_PADDING = 8;
constexpr int MSG_SPACING = 2;
constexpr int MSG_FONTSIZE = 20;
enum class messageState { TYPING, FULL, WAITING, DONE };

class MessageBox
{
    public:
    void Start(const std::string& raw, const std::string& speakerName, bool hasFace_ = false, Texture2D faceTex_ = {}, Rectangle faceRect_ = {});
    void Update(float dt);
    void Draw();
    void HandleMB();
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

    // faceset
    bool hasFace = false;
    Texture2D faceTexture;
    Rectangle faceRect;
};