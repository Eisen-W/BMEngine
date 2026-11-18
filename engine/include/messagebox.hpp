#pragma once
#include "mad_data.hpp"
#include "raylib.h"
#include "renderer.hpp"
#include <string>
#include <vector>

enum class messageState { TYPING, FULL, WAITING, DONE };

struct NineSlice
{
    Texture2D texture;
    NPatchInfo npatch;
    bool active = false;
};

struct TextBoxConfig
{  
    Rectangle box = {16, 340, 608, 124};
    int padding = 8;
    int spacing = 2;
    int fontSize = 20;
    int waitFrames = 10;
    float wordDelay = 0.08f;

    Color defaultColor = WHITE;
    Color borderColor = WHITE;
    Color bgColor = BLACK;
    Color promptColor = WHITE;

    NineSlice slice;
};

struct OptionsConfig
{
    Color defaultColor = WHITE;
    Color selectedColor = YELLOW;
};

struct ColoredWord{
    std::string text;
    Color color;
};

class TextBox
{
    public:
    void Start(const std::vector<std::vector<ColoredWord>>& inPages, 
                const std::string& speakerName, 
                bool hasFace_ = false, Texture2D faceTex_ = {}, Rectangle faceRect_ = {},
                TextBoxConfig cfg_ = {}, OptionsConfig optCfg_ = {}
    );
    void Update(float dt);
    void Draw(Renderer& r);
    void HandleTB();
    bool isActive() const { return active; }

    // OPTIONS
    void setOptions(const std::vector<DialogueOption>& opts);
    int getSelectedNext() const;

    private:

    TextBoxConfig cfg;
    OptionsConfig optCfg;
    
    Font defaultFont = {0,0,0,0};

    void LoadPage(int index);
    void splitWords(const std::string& page);

    std::vector<std::vector<ColoredWord>> pages_colored;
    std::vector<ColoredWord> words;
    std::vector<ColoredWord> currentLineWords;
    std::vector<std::vector<ColoredWord>> lines;

    std::string speaker;
    int currentPage = 0;
    int currentWord = 0;

    float wordTimer = 0.f;
    const float WORD_DELAY = 0.08f;

    int waitFrames = 0;
    const int WAIT_FRAMES = 10;

    messageState msgState = messageState::DONE;
    bool active = false;

    int boxWdith = cfg.box.width - cfg.padding * 2;

    // faceset
    bool hasFace = false;
    Texture2D faceTexture;
    Rectangle faceRect;

    // options
    std::vector<std::string> optionTexts;
    std::vector<int> optionNexts;
    int selectedOption = 0;
    bool hasOptions = false;

    
};