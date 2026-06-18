#include "engine_utils.hpp"
#include "constants.hpp"
#include "dialogue.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "raylib.h"

bool EngineUtils::directionMatch(InteractDirection interactDir, Direction playerDir)
{
    if(interactDir == InteractDirection::ANY) return true;
    switch(playerDir)
    {
        case Direction::UP:     return interactDir == InteractDirection::UP;
        case Direction::DOWN:   return interactDir == InteractDirection::DOWN;
        case Direction::LEFT:   return interactDir == InteractDirection::LEFT;
        case Direction::RIGHT:  return interactDir == InteractDirection::RIGHT;
    }
    return false;
}

void EngineUtils::checkInteractDialogue(Rectangle playerRec, Direction playerDir)
{
    for(auto& data : EWE.loader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::INTERACT) continue;
        for(int i = 0; i < (int)data.rects.size(); i++)
        {
            if(data.once && EWE.loader.hasFiredRect(data.id, i)) continue;
            if(!directionMatch(data.rects[i].dir, playerDir))
            if(CheckCollisionRecs(playerRec, data.rects[i].rect))
            {
                EWE.loader.startDialogue(data.id, i);
                const DialogueData* current = EWE.loader.currentDialogue();
                if(current)
                {
                    Rectangle faceRect;
                    bool hasFace = !current->sprite.empty() && EWE.FSM.getFace(current->sprite, faceRect);
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker, hasFace, EWE.FSM.texture, faceRect);
                    gamestate = GameState::MESSAGE;
                }
                return;
            }
        }
        
    }
}

void EngineUtils::checkAutoDialogue(Rectangle playerRec)
{
    for(auto& data : EWE.loader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::AUTO) continue;
        for(int i = 0; i < (int)data.rects.size(); i++)
        {
            if(data.once && EWE.loader.hasFiredRect(data.id, i)) continue;
            if(CheckCollisionRecs(playerRec, data.rects[i].rect))
            {
                EWE.loader.startDialogue(data.id, i);
                const DialogueData* current = EWE.loader.currentDialogue();
                if(current)
                {
                    Rectangle faceRect;
                    bool hasFace = !current->sprite.empty() && EWE.FSM.getFace(current->sprite, faceRect);
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker, hasFace, EWE.FSM.texture, faceRect);
                    gamestate = GameState::MESSAGE;

                }
                return;
            }
        }
        
    }
}