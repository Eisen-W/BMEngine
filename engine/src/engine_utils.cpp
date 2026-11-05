#include "engine_utils.hpp"
#include "constants.hpp"
#include "mad_data.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "raylib.h"
#include <cstddef>
#include <string>

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

void EngineUtils::startMessageBox(const DialogueData& data)
{
    Rectangle faceRect;
    bool hasFace = !data.sprite.empty() && BME.FaceSM.getFace(data.sprite, faceRect);

    std::string raw = resolveTokens(BME.madloader.buildRaw(data));
    std::string speaker = resolveTokens(data.speaker);
    
    BME.TB.Start(raw, speaker, hasFace, BME.FaceSM.texture, faceRect);
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