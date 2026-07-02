#include "messagebox.hpp"
#include "input_manager.hpp"
#include "raylib.h"
#include "engine.hpp"
#include <sstream>
#include <string>

/** @see Start
    @see loadPage
    @see splitWords
    @see Update
    @see Draw
*/

void MessageBox::Start(const std::string& raw, const std::string& speakerName, bool hasFace_, Texture2D faceTex_, Rectangle faceRect_)
{
    defaultFont = EWE.AM.getFont("../assets/pc-9800.ttf");
    speaker = "";
    pages.clear();
    currentPage = 0;

    speaker = speakerName;
    hasFace = hasFace_;
    faceTexture = faceTex_;
    faceRect = faceRect_;

    pages.clear();
    currentPage = 0;

    std::stringstream ss(raw);
    std::string page;
    while(std::getline(ss, page, '|'))
    {
        if(!page.empty()) pages.push_back(page);
    }

    if(pages.empty()) return;

    active = true;
    LoadPage(0);
}


void MessageBox::LoadPage(int index)
{
    currentPage = index;
    currentWord = 0;
    displayed.clear();
    lines.clear();
    currentLine.clear();
    waitFrames = 0;
    msgState = messageState::TYPING;
    splitWords(pages[index]);
    
    
    if(!words.empty())
    {
        currentLine = words[0];
        currentWord = 1;
    }
    wordTimer = WORD_DELAY;
}

void MessageBox::splitWords(const std::string& page)
{
    words.clear();
    std::stringstream ss(page);
    std::string word;

    while(ss >> word)
    {
        words.push_back(word);
    }
}

void MessageBox::Update(float dt)
{
    if(!active) return;
    
    if(msgState == messageState::TYPING)
    {
        wordTimer -= dt;
        if(wordTimer <= 0.f)
        {
            if(currentWord < (int)words.size())
            {
                std::string test = currentLine.empty() ? words[currentWord] : currentLine + " " + words[currentWord];
                Vector2 measured = MeasureTextEx(defaultFont, test.c_str(),MSG_FONTSIZE, MSG_SPACING);
                if(measured.x > boxWdith)
                {
                    lines.push_back(currentLine);
                    currentLine = words[currentWord];
                }
                else  
                {
                    currentLine = test;
                }
                currentWord++;
                wordTimer = WORD_DELAY;
            }
            else  
            {
                lines.push_back(currentLine);
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
                std::string test = currentLine.empty() ? words[currentWord] : currentLine + " " + words[currentWord];
                Vector2 measured = MeasureTextEx(defaultFont, test.c_str(),MSG_FONTSIZE, MSG_SPACING);
                if(measured.x > boxWdith)
                {
                    lines.push_back(currentLine);
                    currentLine = words[currentWord];
                }
                else  
                {
                    currentLine = test;
                }
                currentWord++;
            }
            lines.push_back(currentLine);
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
        if(Input::pressA())
        {
            if(currentPage + 1 < (int)pages.size())
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

void MessageBox::Draw()
{
    if(!active) return;

    
    //box
    DrawRectangleRec(MSG_BOX, BLACK);
    DrawRectangleLinesEx(MSG_BOX, 2,WHITE);

    //face
    int textOffsetX = MSG_PADDING;
    if(hasFace)
    {
        DrawTexturePro(faceTexture, faceRect, 
                        {MSG_BOX.x + MSG_PADDING, MSG_BOX.y + MSG_PADDING, faceRect.width, faceRect.height},
                        {0,0}, 0, WHITE);
        textOffsetX = MSG_PADDING + (int)faceRect.width + MSG_PADDING;
    }

    //speaker
    DrawTextEx(defaultFont, speaker.c_str(), {MSG_BOX.x + textOffsetX, MSG_BOX.y + MSG_PADDING},
                MSG_FONTSIZE, MSG_SPACING, WHITE);

    //message
    for(int i = 0; i < (int)lines.size(); i++)
    {
        DrawTextEx(defaultFont, lines[i].c_str(), 
            {MSG_BOX.x + textOffsetX,MSG_BOX.y + MSG_PADDING + (MSG_FONTSIZE + 4) + i * (MSG_FONTSIZE + 4)},
                    MSG_FONTSIZE, MSG_SPACING, WHITE);
    }
    
    if(msgState == messageState::TYPING && !currentLine.empty())
    {
        DrawTextEx(defaultFont,currentLine.c_str(), 
        {MSG_BOX.x + textOffsetX, MSG_BOX.y + MSG_PADDING + (MSG_FONTSIZE + 4) + (int)lines.size() * (MSG_FONTSIZE + 4)},
                    MSG_FONTSIZE, MSG_SPACING, WHITE);
    }

    //prompt
    if(msgState == messageState::WAITING)
    {
        DrawTextEx(defaultFont, "[A]",
                    {MSG_BOX.x + MSG_BOX.width - 40, MSG_BOX.y + MSG_BOX.height - MSG_FONTSIZE - MSG_PADDING},
                    MSG_FONTSIZE , MSG_SPACING, WHITE);
    }
}

void MessageBox::HandleMB()
{
    if(!isActive())
    {
        EWE.loader.advanceDialogue();
        const DialogueData* next = EWE.loader.currentDialogue();
        if(next)
        {
            EWE.EUtils.startMessageBox(*next);
            /*
            EWE.MB.Start(EWE.loader.buildRaw(*next), next->speaker);
            gamestate = GameState::MESSAGE;
            */
        }
        else
        {
            gamestate = GameState::PLAY;
        }
    }
}