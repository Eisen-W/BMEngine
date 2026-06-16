#include "engine_utils.hpp"
#include "constants.hpp"
#include "dialogue.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "raylib.h"

void EngineUtils::checkInteractDialogue(Rectangle playerRec, Vector2 facingPoint)
{
    for(auto& data : EWE.loader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::INTERACT) continue;
        for(int i = 0; i < (int)data.rects.size(); i++)
        {
            if(data.once && EWE.loader.hasFiredRect(data.id, i)) continue;
            if(CheckCollisionPointRec(facingPoint, data.rects[i]))
            {
                EWE.loader.startDialogue(data.id, i);
                const DialogueData* current = EWE.loader.currentDialogue();
                if(current)
                {
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker);
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
            if(CheckCollisionRecs(playerRec, data.rects[i]))
            {
                EWE.loader.startDialogue(data.id, i);
                const DialogueData* current = EWE.loader.currentDialogue();
                if(current)
                {
                    EWE.MB.Start(EWE.loader.buildRaw(*current), current->speaker);
                    gamestate = GameState::MESSAGE;

                }
                return;
            }
        }
        
    }
}