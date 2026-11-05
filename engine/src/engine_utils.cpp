#include "engine_utils.hpp"
#include "constants.hpp"
#include "mad_data.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "messagebox.hpp"
#include "raylib.h"
#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

// PRIVATE =======================================================================
bool EngineUtils::directionMatch(InteractDirection interactDir, Direction PDir)
{
    if(interactDir == InteractDirection::ANY) return true;
    switch(PDir)
    {
        case Direction::UP:     return interactDir == InteractDirection::UP;
        case Direction::DOWN:   return interactDir == InteractDirection::DOWN;
        case Direction::LEFT:   return interactDir == InteractDirection::LEFT;
        case Direction::RIGHT:  return interactDir == InteractDirection::RIGHT;
    }
    return false;
}

Color EngineUtils::resolveColor(const std::string& name) const
{
    auto it = colorMap.find(name);
    return it != colorMap.end() ? it->second : WHITE; 
    // default = white
}
// ================================================================================


void EngineUtils::startMessageBox(const DialogueData& data)
{
    Rectangle faceRect;
    bool hasFace = !data.sprite.empty() && BME.FaceSM.getFace(data.sprite, faceRect);

    std::string raw = resolveTokens(BME.madloader.buildRaw(data));
    std::string speaker = resolveTokens(data.speaker);

    // split pages first =========
    std::vector<std::vector<ColoredWord>> pages;
    std::istringstream ss(raw);
    std::string pageStr;
    while(std::getline(ss, pageStr, '|'))
    {
        if(!pageStr.empty()) pages.push_back(parseColoredString(pageStr));
    }
    // ===========================

    BME.TB.Start(pages, speaker, hasFace, BME.FaceSM.texture, faceRect);
    BME.TB.setOptions(data.options);
    gamestate = GameState::MESSAGE;
}

void EngineUtils::checkInteractDialogue(Rectangle playerRec, Direction playerDir)
{
    
    for(auto& data : BME.madloader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::INTERACT) continue;
        for(int i = 0; i < (int)data.rects.size(); i++)
        {
            if(data.once && BME.madloader.hasFiredRect(data.id, i)) continue;
            if(!directionMatch(data.rects[i].dir, playerDir)) continue;
            if(CheckCollisionRecs(playerRec, data.rects[i].rect))
            {
                BME.madloader.startDialogue(data.id, i);
                const DialogueData* current = BME.madloader.currentDialogue();
                if(current)
                {
                    startMessageBox(*current);
                }
                return;
            }
        }
        
    }
}

void EngineUtils::checkAutoDialogue(Rectangle playerRec)
{
    for(auto& data : BME.madloader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::AUTO) continue;
        for(int i = 0; i < (int)data.rects.size(); i++)
        {
            if(data.once && BME.madloader.hasFiredRect(data.id, i)) continue;
            if(CheckCollisionRecs(playerRec, data.rects[i].rect))
            {
                BME.madloader.startDialogue(data.id, i);
                const DialogueData* current = BME.madloader.currentDialogue();
                if(current)
                {
                    startMessageBox(*current);
                }
                return;
            }
        }
        
    }
}

// SUBSTITUTE STRING
void EngineUtils::madSetString(const std::string& key, const std::string& value)
{
    tokens[key] = value;
}

std::string EngineUtils::resolveTokens(const std::string& raw) const
{
    std::string result = raw;

    for(auto& pair : tokens)
    {
        std::string tag = "<" + pair.first + ">";
        size_t pos = 0;

        while((pos = result.find(tag, pos)) != std::string::npos)
        {
            result.replace(pos, tag.size(), pair.second);
            pos += pair.second.size();
        }
    }
    return result;
}

// COLORED WORDS
std::vector<ColoredWord> EngineUtils::parseColoredString(const std::string& raw) const
{
    std::vector<ColoredWord> result;
    Color current = WHITE;
    size_t i = 0;

    while(i < raw.size())
    {
        if(raw[i] == '<')
        {
            size_t end = raw.find('>', i);
            if(end == std::string::npos) break;
    
            std::string tag = raw.substr(i + 1, end - i - 1);
    
            if(tag.substr(0, 3) == "cs:")
            {
                current = resolveColor(tag.substr(3));
                i = end + 1;
            }
            else if(tag == "ce")
            {
                current = WHITE;
                i = end + 1;
            }
            else {
                // not a color tag
                i++;
            }
        }
        else{
            size_t wordEnd = i;
            while(wordEnd < raw.size() && raw[wordEnd] != '<')
            {
                wordEnd++;
            }

            std::string chunk = raw.substr(i, wordEnd - i);

            // split chunk into words
            std::istringstream ss(chunk);
            std::string word;
            while (ss >> word)
            {
                result.push_back({word, current});
            }
            i = wordEnd;
        }
    }
    return result;

}