#include "engine_utils.hpp"
#include "constants.hpp"
#include "dialogue.hpp"
#include "engine.hpp"
#include "engine_ast.hpp"
#include "raylib.h"

void EngineUtils::checkInteractDialogue(Rectangle playerRec)
{
    for(auto& data : EWE.loader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::INTERACT) continue;
        if(CheckCollisionRecs(playerRec, data.rect))
        {
            EWE.loader.startDialogue(data.id);
            const DialogueData* current = EWE.loader.currentDialogue();
            if(current)
            {
                EWE.MB.Start(EWE.loader.buildRaw(*current));
                gamestate = GameState::MESSAGE;
            }
            return;
        }
    }
}

void EngineUtils::checkAutoDialogue(Rectangle playerRec)
{
    for(auto& data : EWE.loader.getDialogueBlocks())
    {
        if(data.trigger != DialogueTrigger::AUTO) continue;
        if(CheckCollisionRecs(playerRec, data.rect))
        {
            EWE.loader.startDialogue(data.id);
            const DialogueData* current = EWE.loader.currentDialogue();
            if(current)
            {
                EWE.MB.Start(EWE.loader.buildRaw(*current));
                gamestate = GameState::MESSAGE;
                
            }
            return;
        }
    }
}