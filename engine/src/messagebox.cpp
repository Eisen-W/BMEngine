#include "messagebox.hpp"
#include "constants.hpp"
#include "globalfont.hpp"
#include "input_manager.hpp"
#include "raylib.h"
#include "engine.hpp"
#include "renderer.hpp"
#include <string>
#include <vector>

/** @see Start
    @see loadPage
    @see splitWords
    @see Update
    @see Draw
*/

void TextBox::Start(const std::vector<std::vector<ColoredWord>>& inPages, 
                const std::string& speakerName, 
                bool hasFace_, Texture2D faceTex_, Rectangle faceRect_,
                TextBoxConfig cfg_, OptionsConfig optCfg_
)
{
    defaultFont = GlobalFont::EngineFont(BME.AM);
    speaker = "";
    pages_colored = inPages;
    currentPage = 0;

    speaker = speakerName;
    hasFace = hasFace_;
    faceTexture = faceTex_;
    faceRect = faceRect_;
    
    cfg = cfg_;
    optCfg = optCfg_;

    if(pages_colored.empty()) return;

    active = true;
    LoadPage(0);
}


void TextBox::LoadPage(int index)
{
    currentPage = index;
    words = pages_colored[index];
    currentWord = 0;
    lines.clear();
    currentLineWords.clear();
    waitFrames = 0;
    msgState = messageState::TYPING;
    
    if(!words.empty())
    {
        currentLineWords = {words[0]};
        currentWord = 1;
    }
    wordTimer = WORD_DELAY;
}

void TextBox::Update(float dt)
{
    if(!active) return;
    
    if(msgState == messageState::TYPING)
    {
        wordTimer -= dt;
        if(wordTimer <= 0.f)
        {
            if(currentWord < (int)words.size())
            {
                std::string lineText;
                for(auto& w : currentLineWords) lineText += w.text + " ";
                std::string testText = lineText + words[currentWord].text;

                //std::string test = currentLine.empty() ? words[currentWord] : currentLine + " " + words[currentWord];
                
                Vector2 measured = MeasureTextEx(defaultFont, testText.c_str(),cfg.fontSize, cfg.spacing);
                if(measured.x > boxWdith)
                {
                    lines.push_back(currentLineWords);
                    currentLineWords = {words[currentWord]};
                }
                else  
                {
                    currentLineWords.push_back(words[currentWord]);
                }
                currentWord++;
                wordTimer = WORD_DELAY;
            }
            else  
            {
                lines.push_back(currentLineWords);
                msgState = messageState::FULL;
                waitFrames = 0;
            }
        }

        if(Input::pressA())
        {
            //skip to full text
            //currentLine.clear();
            lines.clear();
            while(currentWord < (int)words.size())
            {
                std::string lineText;
                for(auto& w : currentLineWords) lineText += w.text + " ";
                std::string testText = lineText + words[currentWord].text;

                Vector2 measured = MeasureTextEx(defaultFont, testText.c_str(),cfg.fontSize, cfg.spacing);
                if(measured.x > boxWdith)
                {
                    lines.push_back(currentLineWords);
                    currentLineWords = {words[currentWord]};
                }
                else  
                {
                    currentLineWords.push_back(words[currentWord]);
                }
                currentWord++;
            }
            lines.push_back(currentLineWords);
            msgState = messageState::FULL;
            waitFrames = 0;
        }
    }
    else if(msgState == messageState::FULL)
    {
        waitFrames++;
        if(waitFrames >= WAIT_FRAMES) msgState = messageState::WAITING;
    }
    else if(msgState == messageState::WAITING)
    {
        // option nav
        if(hasOptions)
        {
            if(Input::pressDown()) selectedOption = (selectedOption + 1) % optionTexts.size();
            if(Input::pressUp())   selectedOption = (selectedOption - 1 + (int)optionTexts.size()) % (int)optionTexts.size();
            if(Input::pressA())
            {
                active = false;
                msgState = messageState::DONE;
            }
        }
        else if(Input::pressA())
        {
            if(currentPage + 1 < (int)pages_colored.size())
            {
                LoadPage(currentPage + 1);
            }
            else
            {
                active = false;
                msgState = messageState::DONE;
            }
        }
    }
}

void TextBox::Draw(Renderer& r)
{
    if(!active) return;

    r.Submit(Layer::UI,
        [&]()
        {
            //box
            if(cfg.slice.active)
            {
                DrawTextureNPatch(cfg.slice.texture, cfg.slice.npatch, cfg.box, {0,0}, 0, WHITE);
            }
            else 
            {
                DrawRectangleRec(cfg.box, BLACK);
                DrawRectangleLinesEx(cfg.box, 2,WHITE);
            }
        
            //face
            int textOffsetX = cfg.padding;
            if(hasFace)
            {
                DrawTexturePro(faceTexture, faceRect, 
                                {cfg.box.x + cfg.padding, cfg.box.y + cfg.padding, faceRect.width, faceRect.height},
                                {0,0}, 0, WHITE);
                textOffsetX = cfg.padding + (int)faceRect.width + cfg.padding;
            }
        
            //speaker
            DrawTextEx(defaultFont, speaker.c_str(), {cfg.box.x + textOffsetX, cfg.box.y + cfg.padding},
                        cfg.fontSize, cfg.spacing, WHITE);
        
            auto drawColoredLine = 
                [&](const std::vector<ColoredWord>& lineWords, float x, float y)
                {
                    float offsetX = x;
                    for(int i = 0; i < (int)lineWords.size(); i++)
                    {
                        DrawTextEx(defaultFont, lineWords[i].text.c_str(), 
                        {offsetX, y}, cfg.fontSize, 
                        cfg.spacing, lineWords[i].color);

                        std::string measured = lineWords[i].text + 
                            (i < (int)lineWords.size() - 1 ? " " : " "
                        );

                        offsetX += MeasureTextEx(defaultFont, measured.c_str(), 
                            cfg.fontSize, cfg.spacing).x;
                    }
                };

            //message
            for(int i = 0; i < (int)lines.size(); i++)
            {
                float y = cfg.box.y + cfg.padding + (cfg.fontSize + 4) + i * (cfg.fontSize + 4);
                drawColoredLine(lines[i], cfg.box.x + textOffsetX, y);
            }
            
            if(msgState == messageState::TYPING && !currentLineWords.empty())
            {
                float y = cfg.box.y + cfg.padding + (cfg.fontSize + 4) + (int)lines.size() * (cfg.fontSize + 4);
                drawColoredLine(currentLineWords, cfg.box.x + textOffsetX, y);
            }
        
            //prompt
            if(msgState == messageState::WAITING)
            {
                if(hasOptions)
                {
                    for(int i = 0; i < (int)optionTexts.size(); i++)
                    {
                        Color col = (i == selectedOption) ? YELLOW : WHITE;
                        DrawTextEx(defaultFont, optionTexts[i].c_str(), 
                        {cfg.box.x + textOffsetX, 
                        cfg.box.y + cfg.box.height - cfg.padding - (optionTexts.size() - i) * (cfg.fontSize + 4)},
                        cfg.fontSize, cfg.spacing, col);
                    }
                }
                DrawTextEx(defaultFont, "[A]",
                            {cfg.box.x + cfg.box.width - 40, cfg.box.y + cfg.box.height - cfg.fontSize - cfg.padding},
                            cfg.fontSize , cfg.spacing, WHITE);
            }
        }
    );
}

void TextBox::HandleTB()
{
    if(!isActive())
    {
        int chosen = hasOptions ? getSelectedNext() : -1;
        BME.madloader.advanceDialogue(chosen);

        const DialogueData* next = BME.madloader.currentDialogue();
        if(next)
        {
            BME.EUtils.startMessageBox(*next);
        }
        else
        {
            gamestate = GameState::PLAY;
        }
    }
}

void TextBox::setOptions(const std::vector<DialogueOption>& opts)
{
    optionTexts.clear();
    optionNexts.clear();

    for(auto& o : opts)
    {
        optionTexts.push_back(o.text);
        optionNexts.push_back(o.next);
    }
    hasOptions = !optionTexts.empty();
    selectedOption = 0;
}

int TextBox::getSelectedNext() const
{
    if(optionNexts.empty()) return 0;
    return optionNexts[selectedOption];
}