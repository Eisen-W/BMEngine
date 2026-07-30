#include "engine_utils.hpp"
#include "constants.hpp"
#include "mad_data.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "raylib.h"

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
    bool hasFace = !data.sprite.empty() && BME.FSM.getFace(data.sprite, faceRect);
    BME.TB.Start(BME.madloader.buildRaw(data), data.speaker, hasFace, BME.FSM.texture, faceRect);
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
                    /*
                    Rectangle faceRect;
                    bool hasFace = !current->sprite.empty() && EWE.FSM.getFace(current->sprite, faceRect);
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker, hasFace, EWE.FSM.texture, faceRect);
                    gamestate = GameState::MESSAGE;
                    */
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
                    /*
                    Rectangle faceRect;
                    bool hasFace = !current->sprite.empty() && EWE.FSM.getFace(current->sprite, faceRect);
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker, hasFace, EWE.FSM.texture, faceRect);
                    gamestate = GameState::MESSAGE;
                    */
                }
                return;
            }
        }
        
    }
}